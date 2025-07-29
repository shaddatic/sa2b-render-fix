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

/****** Ninja ***********************************************************************/
#include <samt/ninja/ninja.h>   /* ninja                                            */

/****** Game ************************************************************************/
#include <samt/sonic/texture.h> /* texture                                          */

/****** Render Fix ******************************************************************/
#include <rf_core.h>            /* core                                             */
#include <rf_njcnk.h>           /* emulated njcnk draw functions                    */
#include <rf_mdlutil.h>         /* change strip flag                                */

/****** Self ************************************************************************/
#include <rf_util.h>            /* self                                             */
#include <rfu_float.h>          /* self, float                                      */
#include <rfu_file.h>           /* self, file                                       */

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
RF_SwapTexFileTableIndex(TEX_PRSTABLE* pTexTable, int idx1, int idx2)
{
    TEX_PRSTABLE tmp = pTexTable[idx1];
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
    c7 pc_path[128]; // base file path

    const size sz_path = ARYLEN(pc_path);

    /** Calculate Source Path **/

    const size sz_fmt = mtStrFormat(pc_path, sz_path, "resource/gd_PC/%s", pcSrcFile);

    if ( sz_fmt >= sz_path )
    {
        RF_DbgWarn("Path buffer overflowed!");
        return FOWN_ERROR;
    }

    /** Get Ownership **/
    
    const size ix_rf = mtGetModIndex();

    if ( ix_rf == -1 ) // old mod loader
    {
        const c7* repl_path = mlGetReplacedFile(pc_path);

        if ( PathIsGame(repl_path) )
        {
            return FOWN_GAME;
        }

        if ( PathIsRF(repl_path) )
        {
            return FOWN_RF;
        }
    }
    else // supports mod index features
    {
        const size ix_file = mlGetFileModIndex(pc_path);

        if ( ix_file == -1 )
        {
            return FOWN_GAME;
        }

        if ( ix_file <= ix_rf )
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
    const size ix_rf = mtGetModIndex();

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
    {
        const eRFU_FOWN fown = RFU_GetFileOwnership(pcGdPath);

        if ( fown > FOWN_RF )
        {
            RF_DbgWarn("File '%s' is not owned by the Game or RF", pcGdPath);
            return false;
        }
    }

    /** Owned by RF, Replace File **/

    c7 pc_path_src[128];
    c7 pc_path_dst[128];

    const size sz_path = ARYLEN(pc_path_src);

    /** Calculate Source Path **/
    {
        const size sz_fmt = mtStrFormat(pc_path_src, sz_path, "resource/gd_PC/%s", pcGdPath);

        if ( sz_fmt >= sz_path )
        {
            RF_DbgWarn("Source path buffer overflowed!");
            return false;
        }
    }
    /** Calculate Destination Path **/
    {
        const size sz_fmt = mtStrFormat(pc_path_dst, sz_path, "%s/optional/%s/%s", mtGetModPath(), pcOptiFolder, pcGdPath);

        if ( sz_fmt >= sz_path )
        {
            RF_DbgWarn("Destination path buffer overflowed!");
            return false;
        }
    }

    /** Replace File **/

    RF_DbgInfo("Replaced file '%s' with '/%s/%s'", pcGdPath, pcOptiFolder, pcGdPath);

    ReplaceFile(pc_path_src, pc_path_dst);

    return true;
}

bool
RFU_ReplaceTexture(const c7* pcTexName, const c7* pcOptiFolder)
{
    c7 pc_src[128];
    c7 pc_dst[128];

    const size sz_path = ARYLEN(pc_src);

    /** Check File Ownership **/
    {
        mtStrFormat(pc_src, sz_path, "resource/gd_PC/%s.PRS", pcTexName);

        const eRFU_FOWN fown = RFU_GetFileOwnership(pc_src);

        if ( fown > FOWN_RF )
        {
            RF_DbgInfo("Texture file '%s.PRS' is not owned by the Game or RF", pcTexName);
            return false;
        }
    }

    /** Owned by RF, Replace File **/

    /** Calculate Source Path **/
    {
        const size sz_fmt = mtStrFormat(pc_src, sz_path, "resource/gd_PC/PRS/%s.pak", pcTexName);

        if ( sz_fmt >= sz_path )
        {
            RF_DbgWarn("Source path buffer overflowed!");
            return false;
        }
    }
    /** Calculate Destination Path **/
    {
        const size sz_fmt = mtStrFormat(pc_dst, sz_path, "%s/optional/%s/PRS/%s.pak", mtGetModPath(), pcOptiFolder, pcTexName);

        if ( sz_fmt >= sz_path )
        {
            RF_DbgWarn("Destination path buffer overflowed!");
            return false;
        }
    }

    /** Replace File **/

    RF_DbgInfo("Replaced texture '%s.PRS' with '/%s/PRS/%s.pak'", pcTexName, pcOptiFolder, pcTexName);

    ReplaceFile(pc_src, pc_dst);

    return true;
}

bool
RFU_ReplacePvr(const c7* pcPvrName, const c7* pcOptiFolder)
{
    c7 pc_src[128];
    c7 pc_dst[128];

    const size sz_path = ARYLEN(pc_src);

    /** Check File Ownership (PRS) **/
    {
        // we check PRS too due to a logic inconsistancy in the
        // Mod Loader's 'ReplaceFile' function

        mtStrFormat(pc_src, sz_path, "resource/gd_PC/%s.PRS", pcPvrName);

        const eRFU_FOWN fown = RFU_GetFileOwnership(pc_src);

        if ( fown > FOWN_RF )
        {
            RF_DbgInfo("Texture file '%s' is not owned by the Game or RF", pc_src);
            return false;
        }
    }
    /** Check File Ownership (PVR) **/
    {
        mtStrFormat(pc_src, sz_path, "resource/gd_PC/%s.GVR", pcPvrName);

        const eRFU_FOWN fown = RFU_GetFileOwnership(pc_src);

        if ( fown > FOWN_RF )
        {
            RF_DbgInfo("Texture file '%s' is not owned by the Game or RF", pc_src);
            return false;
        }
    }

    /** Owned by RF, Replace File **/

    /** Calculate Source Path **/
    {
        // reuse pre-calculated path
    }
    /** Calculate Destination Path **/
    {
        const size sz_fmt = mtStrFormat(pc_dst, sz_path, "%s/optional/%s/PRS/%s.pak", mtGetModPath(), pcOptiFolder, pcPvrName);

        if ( sz_fmt >= sz_path )
        {
            RF_DbgWarn("Destination path buffer overflowed!");
            return false;
        }
    }

    /** Replace File **/

    RF_DbgInfo("Replaced texture '%s.GVR' with '/%s/PRS/%s.pak'", pcPvrName, pcOptiFolder, pcPvrName);

    ReplaceFile(pc_src, pc_dst);

    return true;
}

bool
RFU_ReplacePlayerPrs(const c7* pcPrsName, const c7* pcOptiFolder)
{
    c7 pc_src[128];
    c7 pc_dst[128];

    const size sz_path = ARYLEN(pc_src);

    /** Check for folder based player model files **/
    {
        mtStrFormat(pc_src, sz_path, "resource/gd_PC/%s/%s.ini", pcPrsName, pcPrsName);

        const eRFU_FOWN fown = RFU_GetFileOwnership(pc_src);

        if ( fown > FOWN_RF )
        {
            RF_DbgInfo("Player file '%s' is not owned by the Game or RF", pcPrsName);
            return false;
        }
    }
    /** Check for PRS based player model files **/
    {
        mtStrFormat(pc_src, sz_path, "resource/gd_PC/%s.PRS", pcPrsName, pcPrsName);

        const eRFU_FOWN fown = RFU_GetFileOwnership(pc_src);

        if ( fown > FOWN_RF )
        {
            RF_DbgInfo("Player file '%s' is not owned by the Game or RF", pcPrsName);
            return false;
        }
    }

    mtStrFormat(pc_dst, sz_path, "%s/optional/%s/%s.PRS", mtGetModPath(), pcOptiFolder, pcPrsName);

    /** Replace File **/

    RF_DbgInfo("Replaced player file '%s.PRS' with '/%s/%s.PRS'", pcPrsName, pcOptiFolder, pcPrsName);

    ReplaceFile(pc_src, pc_dst);

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
    c8 upath[256];

    mtStrFormat(upath, ARYLEN(upath), "%s/model/%s.sa2mdl", mtGetModPath(), puSrcFile);

    mt_samdl* const p_samdl = mtSAModelLoad(upath, SAMDL_CHUNK|SAMDL_MODEL);

    if ( !p_samdl )
    {
        return false;
    }

    const bool result = ReplaceChunkModelSub(pDstModel, p_samdl->pChunk->model);

    mtSAModelFree(p_samdl);

    return result;
}

bool
RFU_ReplaceChunkObject(NJS_CNK_OBJECT* pDstObject, const c8* puSrcFile)
{
    c8 upath[256];

    mtStrFormat(upath, ARYLEN(upath), "%s/model/%s.sa2mdl", mtGetModPath(), puSrcFile);

    mt_samdl* const p_samdl = mtSAModelLoad(upath, SAMDL_CHUNK);

    if ( !p_samdl )
    {
        return false;
    }

    const bool result = ReplaceChunkObjectSub(pDstObject, p_samdl->pChunk);

    mtSAModelFree(p_samdl);

    return result;
}

/****** Replace File ****************************************************************************/
void
RFU_DirectReplaceFloat(pint pOpcode, const void* pFlt)
{
    WritePointer(pOpcode+2, pFlt);
}

static f32  FloatList[64];
static size FloatNumber;
static f64  DoubleList[64];
static size DoubleNumber;

static bool
ReplaceFloat(pint pOpcode, f32 val)
{
    const f32*  p_flt = nullptr;
    const size nb_flt = FloatNumber;

    for ( size i = 0; i < nb_flt; ++i )
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
    const f64*  p_dbl = nullptr;
    const size nb_dbl = DoubleNumber;

    for ( size i = 0; i < nb_dbl; ++i )
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
            OutputFormat("Invalid float opcode %i", cmp);
            return false;
        }
    }
}
