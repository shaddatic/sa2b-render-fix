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

/****** Std *************************************************************************/
#include <stdio.h>              /* snprintf                                         */

/****** Self ************************************************************************/
#include <rf_util.h>            /* self                                             */

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
eRFU_FILE_OWNER
RFU_GetFileOwnership(const char* pcPath)
{
    const char* const repl_path = mlGetReplacedFile(pcPath);

    if ( PathIsGame(repl_path) )
        return FOWN_GAME;

    if (PathIsRF(repl_path))
        return FOWN_RF;

    return FOWN_OTHER;
}

/****** Replace File ****************************************************************/
bool
RFU_ReplaceFile(const char* pcPath, const char* pcOptiFolder)
{
    char file_buf[128]; // base file path

    /** Check for path ownership **/
    {
        snprintf(file_buf, ARYLEN(file_buf), "resource/gd_PC/%s", pcPath); // also used for replace path

        const char* const repl_path = mlGetReplacedFile(file_buf);

        /** Check if the file is replaced, or if Render Fix owns the replaced file **/
        if ( !PathIsGame(repl_path) && !PathIsRF(repl_path) )
            return false;
    }

    char opti_buf[256]; // optional file path

    snprintf(opti_buf, ARYLEN(opti_buf), "%s/optional/%s/%s", mtGetModPath(), pcOptiFolder, pcPath);

    if ( !mtFileExists(opti_buf) )
    {
        snprintf(opti_buf, ARYLEN(opti_buf), "/optional/%s/%s", pcOptiFolder, pcPath);

        OutputFormat("RF WARN: (RFU_ReplaceFile) Optional file \"%s\" was not found", opti_buf);

        return false;
    }

    mlReplaceFile(file_buf, opti_buf);

    return true;
}

bool
RFU_ReplaceTexture(const char* pcTexName, const char* pcOptiFolder)
{
    char file_buf[128]; // base file path

    /** Check for texture file ownership **/
    {
        snprintf(file_buf, ARYLEN(file_buf), "resource/gd_PC/%s.PRS", pcTexName);

        const char* const repl_path = mlGetReplacedFile(file_buf);

        /** Check if the file isn't replaced, or if Render Fix owns the replaced file **/
        if ( !PathIsGame(repl_path) && !PathIsRF(repl_path) )
            return false;
    }

    char opti_buf[256]; // optional file path

    /** Make vanilla PAK path **/
    snprintf(file_buf, ARYLEN(file_buf), "resource/gd_PC/PRS/%s.pak", pcTexName);

    /** Make optional folder PAK path **/
    snprintf(opti_buf, ARYLEN(opti_buf), "%s/optional/%s/PRS/%s.pak", mtGetModPath(), pcOptiFolder, pcTexName);

    if ( !mtFileExists(opti_buf) )
    {
        snprintf(opti_buf, ARYLEN(opti_buf), "/optional/%s/PRS/%s.pak", pcOptiFolder, pcTexName);

        OutputFormat("RF WARN: (RFU_ReplaceTexture) Texture PAK file \"%s\" was not found", opti_buf);

        return false;
    }

    mlReplaceFile(file_buf, opti_buf);

    return true;
}

bool
RFU_ReplacePvr(const char* pcPvrName, const char* pcOptiFolder)
{
    char file_buf[128]; // base file path

    /** Check for GVR file ownership **/
    {
        snprintf(file_buf, ARYLEN(file_buf), "resource/gd_PC/%s.GVR", pcPvrName); // also used for replace path

        const char* const repl_path = mlGetReplacedFile(file_buf);

        /** Check if the file isn't replaced, or if Render Fix owns the replaced file **/
        if ( !PathIsGame(repl_path) && !PathIsRF(repl_path) )
            return false;
    }

    char opti_buf[256]; // optional file path

    /** Make optional folder PAK path **/
    snprintf(opti_buf, ARYLEN(opti_buf), "%s/optional/%s/PRS/%s.pak", mtGetModPath(), pcOptiFolder, pcPvrName);

    if ( !mtFileExists(opti_buf) )
    {
        snprintf(opti_buf, ARYLEN(opti_buf), "/optional/%s/PRS/%s.pak", pcOptiFolder, pcPvrName);

        OutputFormat("RF WARN: (RFU_ReplacePvr) Texture PAK file \"%s\" was not found", opti_buf);

        return false;
    }

    mlReplaceFile(file_buf, opti_buf);

    return true;
}

static bool
ReplacePlayerPrsSub(const char* pcPrsName, const char* pcOptiFolder, const char* pcErrText)
{
    char file_buf[128]; // base file path

    /** Check for folder based player model files **/
    {
        snprintf(file_buf, ARYLEN(file_buf), "resource/gd_PC/%s/%s.ini", pcPrsName, pcPrsName);

        const char* const repl_path = mlGetReplacedFile(file_buf);

        /** Check if the file is replaced, or if Render Fix owns the replaced file **/
        if ( !PathIsGame(repl_path) && !PathIsRF(repl_path) )
            return false;
    }

    /** Check for PRS based player model files **/
    {
        snprintf(file_buf, ARYLEN(file_buf), "resource/gd_PC/%s.PRS", pcPrsName); // also used for replace path

        const char* const repl_path = mlGetReplacedFile(file_buf);

        /** Check if the file is replaced, or if Render Fix owns the replaced file **/
        if ( !PathIsGame(repl_path) && !PathIsRF(repl_path) )
            return false;
    }

    char opti_buf[256]; // optional file path

    snprintf(opti_buf, ARYLEN(opti_buf), "%s/optional/%s/%s.PRS", mtGetModPath(), pcOptiFolder, pcPrsName);

    if ( !mtFileExists(opti_buf) )
    {
        snprintf(opti_buf, ARYLEN(opti_buf), "/optional/%s/%s.PRS", pcOptiFolder, pcPrsName);

        OutputFormat(pcErrText, opti_buf);

        return false;
    }

    mlReplaceFile(file_buf, opti_buf);

    return true;
}

bool
RFU_ReplaceMdl(const char* pcMdlName, const char* pcOptiFolder)
{
    return ReplacePlayerPrsSub(pcMdlName, pcOptiFolder, "RF WARN: (RFU_ReplaceMdl) Player model file \"%s\" was not found");
}

bool
RFU_ReplaceMtn(const char* pcMtnName, const char* pcOptiFolder)
{
    return ReplacePlayerPrsSub(pcMtnName, pcOptiFolder, "RF WARN: (RFU_ReplaceMtn) Player motion file \"%s\" was not found");
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
static f32  FloatList[64];
static size FloatNumber;
static f64  DoubleList[64];
static size DoubleNumber;

static bool
ReplaceFloat_(pint pOpcode, poff offset, f32 val)
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

    WritePointer(pOpcode+offset, p_flt);

    return true;
}

static bool
ReplaceDouble(pint pOpcode, poff offset, f64 val)
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

    WritePointer(pOpcode+offset, p_dbl);

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
            return ReplaceFloat_(pOpcode, 2, (f32)val);
        }
        case 0xDC:
        case 0xDD:
        {
            return ReplaceDouble(pOpcode, 2, val);
        }
        default:
        {
            OutputFormat("Invalid float opcode %i", cmp);
            return false;
        }
    }
}
