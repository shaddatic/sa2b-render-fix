/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <samt/core.h>          /* core                                             */
#include <samt/modloader.h>     /* mod loader                                       */
#include <samt/file.h>          /* file exists                                      */
#include <samt/string.h>        /* path string                                      */
#include <samt/memory.h>        /* memcopy                                          */
#include <samt/model.h>         /* v/plistsize                                      */
#include <samt/samdl.h>         /* mt_samdl                                         */

/****** Util ************************************************************************/
#include <samt/util/njbin.h>    /* ninja binary                                     */

/****** Ninja ***********************************************************************/
#include <samt/ninja/ninja.h>   /* ninja                                            */

/****** Game ************************************************************************/
#include <samt/sonic/texture.h> /* texture                                          */

/****** Render Fix ******************************************************************/
#include <rf_core.h>            /* core                                             */
#include <rf_njcnk.h>           /* emulated njcnk draw functions                    */
#include <rf_mdlutil.h>         /* change strip flag                                */
#include <rf_model.h>           /* get object                                       */

/****** Self ************************************************************************/
#include <rf_util.h>            /* self                                             */
#include <rfu_float.h>          /* self, float                                      */
#include <rfu_file.h>           /* self, file                                       */

/************************/
/*  Constants           */
/************************/
/****** Optional Directory **********************************************************/
#define OPTI_DIR                "opti"

/****** String Buffer Length ********************************************************/
#define BUF_LEN                 (0x2000)

/************************/
/*  Source              */
/************************/
/****** Static **********************************************************************/
static bool
PathStartsWith(const char* pcPath, const char* pcTest)
{
    return mtPathSearch(pcPath, pcTest, STR_NOMAX) == 0;
}

static bool
PathIsGame(const char* pcPath)
{
    return PathStartsWith(pcPath, "resource");
}

static bool
PathIsRF(const char* pcPath)
{
    return PathStartsWith(pcPath, mtGetModPath());
}

/****** Texture File Table **********************************************************/
void
RF_SwapTexFileTableIndex(TEX_PVMTABLE* pTexTable, int idx1, int idx2)
{
    TEX_PVMTABLE tmp = pTexTable[idx1];
    pTexTable[idx1] = pTexTable[idx2];
    pTexTable[idx2] = tmp;
}

/****** Calculations ****************************************************************/
void
RFU_LerpPoints(NJS_POINT3* pOutPt, const NJS_POINT3* pPt1, const NJS_POINT3* pPt2, f32 ratioPt1)
{
    const f32 inv_ratio = 1.f - ratioPt1;

    pOutPt->x = (pPt1->x * ratioPt1) + (pPt2->x * inv_ratio);
    pOutPt->y = (pPt1->y * ratioPt1) + (pPt2->y * inv_ratio);
    pOutPt->z = (pPt1->z * ratioPt1) + (pPt2->z * inv_ratio);
}

void
RFU_CalculateScreen(const NJS_POINT3* const pInPos, NJS_POINT2* const pOutPos)
{
    const f32 inv_dist = _nj_screen_.dist / pInPos->z;

    pOutPos->x = -(pInPos->x * _nj_screen_.ax * inv_dist) + 320.f;
    pOutPos->y =  (pInPos->y * _nj_screen_.ay * inv_dist) + 240.f;
}

void
RFU_ProjectScreen(const NJS_POINT3* const pInPos, NJS_POINT2* const pOutPos)
{
    NJS_POINT3 pt3;

    njCalcPoint(NULL, pInPos, &pt3);

    RFU_CalculateScreen(&pt3, pOutPos);
}

bool
RFU_CalcInvertedMatrix(const NJS_MATRIX* m)
{
    if (!m)
        m = _nj_curr_matrix_;

    NJS_VECTOR x1 = { m->m[0][0], m->m[1][0], m->m[2][0] };
    NJS_VECTOR y1 = { m->m[0][1], m->m[1][1], m->m[2][1] };
    NJS_VECTOR z1 = { m->m[0][2], m->m[1][2], m->m[2][2] };

    NJS_VECTOR cz; // cx, cy, cz; // Calculated

    njOuterProduct2(&x1, &y1, &cz);

    const f32 sz1 = njInnerProduct(&cz, &z1);

    return (sz1 < 0.0f);
}

/****** File Ownership **************************************************************/
eRFU_FOWN
RFU_GetFileOwnership(const c7* pcSrcFile)
{
    c7* buf_path = (c7*) &GlobalBuffer[BUF_LEN*4]; // base file path

    const isize sz_path = BUF_LEN;

    /** Calculate Source Path **/

    mtStrFormat(buf_path, BUF_LEN, "resource/gd_PC/%s", pcSrcFile);

    /** Get Ownership **/
    
    if ( mlGetVersion() >= ML_MINVER_FILEMODIX )
    {
        const isize ix_file = mlGetFileModIndex(buf_path);

        if ( ix_file == -1 )
        {
            return FOWN_GAME;
        }

        if ( ix_file <= mtGetModIndex() )
        {
            return FOWN_RF;
        }
    }
    else // old mod loader
    {
        const c7* repl_path = mlGetReplacedFile(buf_path);

        if ( PathIsGame(repl_path) )
        {
            return FOWN_GAME;
        }

        // I'm very aware that this doesn't detect mods potentially above RF
        // Oh well!

        if ( PathIsRF(repl_path) )
        {
            return FOWN_RF;
        }
    }

    return FOWN_OTHER;
}

/****** Replace File ****************************************************************/
static void
ReplaceFile(const c7* pcSrcPath, const c7* pcDstPath)
{
    const isize ix_rf = mtGetModIndex();

    if ( ix_rf == -1 ) // old mod loader
    {
        mlReplaceFile(pcSrcPath, pcDstPath);
    }
    else // supports mod index features
    {
        mlReplaceFileAtIndex(pcSrcPath, pcDstPath, ix_rf);
    }
}

bool
RFU_ReplaceFile(const c7* pcGdPath, const c7* pcOptiFolder)
{
    /** Check File Ownership **/

    if ( RFU_GetFileOwnership(pcGdPath) > FOWN_RF )
    {
        RF_DbgExtra("File '%s' is not owned by the Game or RF", pcGdPath);
        return false;
    }

    /** Owned by RF, Replace File **/

    c7* buf_src = (c7*) &GlobalBuffer[BUF_LEN*0];
    c7* buf_dst = (c7*) &GlobalBuffer[BUF_LEN*1];

    mtStrFormat(buf_src, BUF_LEN, "resource/gd_PC/%s"    , pcGdPath);
    mtStrFormat(buf_dst, BUF_LEN, "%s/" OPTI_DIR "/%s/%s", mtGetModPath(), pcOptiFolder, pcGdPath);

    ReplaceFile(buf_src, buf_dst);

    RF_DbgExtra("Replaced file '%s' with '/%s/%s'", pcGdPath, pcOptiFolder, pcGdPath);
    return true;
}

bool
RFU_ReplaceTexture(const c7* pcTexName, const c7* pcOptiFolder)
{
    c7* buf_src = (c7*) &GlobalBuffer[BUF_LEN*0];
    c7* buf_dst = (c7*) &GlobalBuffer[BUF_LEN*1];

    /** Check File Ownership **/

    mtStrFormat(buf_src, BUF_LEN, "resource/gd_PC/%s.PRS", pcTexName);

    if ( RFU_GetFileOwnership(buf_src) > FOWN_RF )
    {
        RF_DbgExtra("Texture file '%s.PRS' is not owned by the Game or RF", pcTexName);
        return false;
    }

    /** Owned by RF, Replace File **/

    mtStrFormat(buf_src, BUF_LEN, "resource/gd_PC/PRS/%s.pak"    , pcTexName);
    mtStrFormat(buf_dst, BUF_LEN, "%s/" OPTI_DIR "/%s/PRS/%s.pak", mtGetModPath(), pcOptiFolder, pcTexName);

    ReplaceFile(buf_src, buf_dst);

    RF_DbgExtra("Replaced texture '%s.PRS' with '/%s/PRS/%s.pak'", pcTexName, pcOptiFolder, pcTexName);
    return true;
}

bool
RFU_ReplacePvr(const c7* pcPvrName, const c7* pcOptiFolder)
{
    c7* buf_src = (c7*) &GlobalBuffer[BUF_LEN*0];
    c7* buf_dst = (c7*) &GlobalBuffer[BUF_LEN*1];

    /** Check File Ownership (PRS) **/

    // we check PRS too due to a logic inconsistancy in the
    // Mod Loader's 'ReplaceFile' function
    mtStrFormat(buf_src, BUF_LEN, "resource/gd_PC/%s.PRS", pcPvrName);

    if ( RFU_GetFileOwnership(buf_src) > FOWN_RF )
    {
        RF_DbgExtra(RFD_FUNCNAME " Texture file '%s' is not owned by the Game or RF", buf_src);
        return false;
    }

    /** Check File Ownership (PVR) **/

    mtStrFormat(buf_src, BUF_LEN, "resource/gd_PC/%s.GVR", pcPvrName);

    if ( RFU_GetFileOwnership(buf_src) > FOWN_RF )
    {
        RF_DbgExtra(RFD_FUNCNAME " Texture file '%s' is not owned by the Game or RF", buf_src);
        return false;
    }

    /** Owned by RF, Replace File **/

    mtStrFormat(buf_dst, BUF_LEN, "%s/" OPTI_DIR "/%s/PRS/%s.pak", mtGetModPath(), pcOptiFolder, pcPvrName);

    ReplaceFile(buf_src, buf_dst);

    RF_DbgExtra("Replaced texture '%s.GVR' with '/%s/PRS/%s.pak'", pcPvrName, pcOptiFolder, pcPvrName);
    return true;
}

bool
RFU_ReplacePlayerPrs(const c7* pcPrsName, const c7* pcOptiFolder)
{
    c7* buf_src = (c7*) &GlobalBuffer[BUF_LEN*0];
    c7* buf_dst = (c7*) &GlobalBuffer[BUF_LEN*1];

    /** Check for folder based player model files **/

    mtStrFormat(buf_src, BUF_LEN, "resource/gd_PC/%s/%s.ini", pcPrsName, pcPrsName);

    if ( RFU_GetFileOwnership(buf_src) > FOWN_RF )
    {
        RF_DbgExtra(RFD_FUNCNAME " Player file '%s' is not owned by the Game or RF", pcPrsName);
        return false;
    }

    /** Check for PRS based player model files **/

    mtStrFormat(buf_src, BUF_LEN, "resource/gd_PC/%s.PRS", pcPrsName, pcPrsName);

    if ( RFU_GetFileOwnership(buf_src) > FOWN_RF )
    {
        RF_DbgExtra(RFD_FUNCNAME " Player file '%s' is not owned by the Game or RF", pcPrsName);
        return false;
    }

    if ( pcOptiFolder )
    {
        mtStrFormat(buf_dst, BUF_LEN, "%s/" OPTI_DIR "/%s/%s.PRS", mtGetModPath(), pcOptiFolder, pcPrsName);

        /** Replace File **/

        RF_DbgExtra("Replaced player file '%s.PRS' with '/%s/%s.PRS'", pcPrsName, pcOptiFolder, pcPrsName);

        ReplaceFile(buf_src, buf_dst);
    }

    return true;
}

/****** Replace Model ***************************************************************/
static bool
ReplaceChunkModelSub(NJS_CNK_MODEL* pDstModel, const NJS_CNK_MODEL* pSrcModel)
{
    // check vlist and plist sizes

    const size_t sz_dst_vlist = mtCnkVListSize(pDstModel->vlist);
    const size_t sz_src_vlist = mtCnkVListSize(pSrcModel->vlist);

    if ( sz_dst_vlist < sz_src_vlist )
    {
        return false;
    }

    const size_t sz_dst_plist = mtCnkPListSize(pDstModel->plist);
    const size_t sz_src_plist = mtCnkPListSize(pSrcModel->plist);

    if ( sz_dst_plist < sz_src_plist )
    {
        return false;
    }

    // checks passed, copy model

    pDstModel->center = pSrcModel->center;
    pDstModel->r      = pSrcModel->r;

    mtMemCopy(pDstModel->vlist, pSrcModel->vlist, sz_src_vlist);
    mtMemCopy(pDstModel->plist, pSrcModel->plist, sz_src_plist);

    return true;
}

static bool
ReplaceChunkObjectSub(NJS_CNK_OBJECT* pDstObject, const NJS_CNK_OBJECT* pSrcObject)
{
    if ( pDstObject->child )
    {
        if ( ReplaceChunkObjectSub(pDstObject->child, pSrcObject->child) == false )
        {
            return false;
        }
    }

    if ( pDstObject->sibling )
    {
        if ( ReplaceChunkObjectSub(pDstObject->sibling, pSrcObject->sibling) == false )
        {
            return false;
        }
    }

    if ( pDstObject->model )
    {
        if ( ReplaceChunkModelSub(pDstObject->model, pSrcObject->model) == false )
        {
            return false;
        }
    }

    pDstObject->evalflags = pSrcObject->evalflags;

    pDstObject->pos[0] = pSrcObject->pos[0];
    pDstObject->pos[1] = pSrcObject->pos[1];
    pDstObject->pos[2] = pSrcObject->pos[2];

    pDstObject->ang[0] = pSrcObject->ang[0];
    pDstObject->ang[1] = pSrcObject->ang[1];
    pDstObject->ang[2] = pSrcObject->ang[2];

    pDstObject->scl[0] = pSrcObject->scl[0];
    pDstObject->scl[1] = pSrcObject->scl[1];
    pDstObject->scl[2] = pSrcObject->scl[2];

    return true;
}

bool
RFU_ReplaceChunkModel(NJS_CNK_MODEL* pDstModel, const c8* puSrcFile)
{
    NJS_CNK_OBJECT* p_obj = RF_GetCnkObject(puSrcFile);

    if ( !p_obj || !p_obj->model )
    {
        return false;
    }

    const bool result = ReplaceChunkModelSub(pDstModel, p_obj->model);

    mtFree(p_obj);

    return result;
}

bool
RFU_ReplaceChunkObject(NJS_CNK_OBJECT* pDstObject, const c8* puSrcFile)
{
    NJS_CNK_OBJECT* p_obj = RF_GetCnkObject(puSrcFile);

    if ( !p_obj )
    {
        return false;
    }

    const bool result = ReplaceChunkObjectSub(pDstObject, p_obj);

    mtFree(p_obj);

    return result;
}

/****** Replace Float ***************************************************************************/
void
RFU_DirectReplaceFloat(pint pOpcode, const void* pFlt)
{
    WritePointer(pOpcode+2, pFlt);
}

static f32   FloatList[64];
static isize FloatNumber;
static f64   DoubleList[64];
static isize DoubleNumber;

static bool
ReplaceFloat(pint pOpcode, f32 val)
{
    const f32*  p_flt = nullptr;
    const isize nb_flt = FloatNumber;

    for ( isize i = 0; i < nb_flt; ++i )
    {
        if ( FloatList[i] == val )
        {
            p_flt = &FloatList[i];
            break;
        }
    }

    if ( !p_flt )
    {
        if ( FloatNumber >= ARYLEN(FloatList) )
        {
            return false;
        }

        FloatList[nb_flt] = val;

        p_flt = &FloatList[nb_flt];

        FloatNumber = nb_flt + 1;
    }

    RFU_DirectReplaceFloat(pOpcode, p_flt);

    return true;
}

static bool
ReplaceDouble(pint pOpcode, f64 val)
{
    const f64*   p_dbl = nullptr;
    const isize nb_dbl = DoubleNumber;

    for ( isize i = 0; i < nb_dbl; ++i )
    {
        if ( DoubleList[i] == val )
        {
            p_dbl = &DoubleList[i];
            break;
        }
    }

    if ( !p_dbl )
    {
        if ( DoubleNumber >= ARYLEN(DoubleList) )
        {
            return false;
        }

        DoubleList[nb_dbl] = val;

        p_dbl = &DoubleList[nb_dbl];

        DoubleNumber = nb_dbl + 1;
    }

    RFU_DirectReplaceFloat(pOpcode, p_dbl);

    return true;
}

bool
RFU_ReplaceFloat(pint pOpcode, f64 val)
{
    const u8 cmp = *(u8*)pOpcode;

    switch ( cmp )
    {
        case 0xD8:
        case 0xD9:
        {
            return ReplaceFloat(pOpcode, (f32)val);
        }
        case 0xDC:
        case 0xDD:
        {
            return ReplaceDouble(pOpcode, val);
        }
        default:
        {
            RF_DbgWarn(RFD_FUNCNAME " Invalid float opcode %02H", cmp);
            return false;
        }
    }
}

/****** Ninja Binary ****************************************************************************/
void*
RFU_NinjaBinaryRead(const c8* fpath, bool(*fnNameCheck)(u32 name))
{
    mt_njbin* nb = mtNinjaBinaryOpen(fpath);

    u32 cnk_name = '****';
    u32 cnk_size = 0;

    // find the model binary chunk
    for ( ; ; )
    {
        // get chunk. if error, stop
        if ( mtNinjaBinaryChunk(nb, &cnk_name, &cnk_size) < NJBIN_RET_OK )
        {
            break;
        }

        // check chunk name. if matches we found what we want, stop
        if ( fnNameCheck(cnk_name) )
        {
            break;
        }

        // skip to the next chunk. if error or we reach the end, stop
        if ( mtNinjaBinarySkip(nb) != NJBIN_RET_OK )
        {
            break;
        }
    }

    // return ptr
    void* p_object;

    // we found it!
    if ( fnNameCheck(cnk_name) )
    {
        p_object = mtMemAlloc(cnk_size);

        if ( mtNinjaBinaryRead(nb, p_object, NULL, NULL) < NJBIN_RET_OK )
        {
            // there was an error, stop
            mtFree(p_object);
            p_object = nullptr;
        }
    }
    else // some error
    {
        p_object = nullptr;
    }

    mtNinjaBinaryClose(nb);
    return p_object;
}
