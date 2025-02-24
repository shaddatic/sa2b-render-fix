/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <samt/core.h>          /* core                                             */
#include <samt/modloader.h>     /* mod loader                                       */
#include <samt/file.h>          /* file exists                                      */
#include <samt/string.h>        /* path string                                      */

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
    const char* const repl_path = ML_GetReplaceablePath(pcPath);

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

        const char* const repl_path = ML_GetReplaceablePath(file_buf);

        /** Check if the file is replaced, or if Render Fix owns the replaced file **/
        if ( !PathIsGame(repl_path) && !PathIsRF(repl_path) )
            return false;
    }

    char opti_buf[256]; // optional file path

    snprintf(opti_buf, ARYLEN(opti_buf), "%s/optional/%s/%s", mtGetModPath(), pcOptiFolder, pcPath);

    if ( !uFileExists(opti_buf) )
    {
        snprintf(opti_buf, ARYLEN(opti_buf), "/optional/%s/%s", pcOptiFolder, pcPath);

        OutputFormat("RF WARN: (RFU_ReplaceFile) Optional file \"%s\" was not found", opti_buf);

        return false;
    }

    ML_ReplaceFile(file_buf, opti_buf);

    return true;
}

bool
RFU_ReplaceTexture(const char* pcTexName, const char* pcOptiFolder)
{
    char file_buf[128]; // base file path

    /** Check for texture file ownership **/
    {
        snprintf(file_buf, ARYLEN(file_buf), "resource/gd_PC/%s.PRS", pcTexName);

        const char* const repl_path = ML_GetReplaceablePath(file_buf);

        /** Check if the file isn't replaced, or if Render Fix owns the replaced file **/
        if ( !PathIsGame(repl_path) && !PathIsRF(repl_path) )
            return false;
    }

    char opti_buf[256]; // optional file path

    /** Make vanilla PAK path **/
    snprintf(file_buf, ARYLEN(file_buf), "resource/gd_PC/PRS/%s.pak", pcTexName);

    /** Make optional folder PAK path **/
    snprintf(opti_buf, ARYLEN(opti_buf), "%s/optional/%s/PRS/%s.pak", mtGetModPath(), pcOptiFolder, pcTexName);

    if ( !uFileExists(opti_buf) )
    {
        snprintf(opti_buf, ARYLEN(opti_buf), "/optional/%s/PRS/%s.pak", pcOptiFolder, pcTexName);

        OutputFormat("RF WARN: (RFU_ReplaceTexture) Texture PAK file \"%s\" was not found", opti_buf);

        return false;
    }

    ML_ReplaceFile(file_buf, opti_buf);

    return true;
}

bool
RFU_ReplacePvr(const char* pcPvrName, const char* pcOptiFolder)
{
    char file_buf[128]; // base file path

    /** Check for GVR file ownership **/
    {
        snprintf(file_buf, ARYLEN(file_buf), "resource/gd_PC/%s.GVR", pcPvrName); // also used for replace path

        const char* const repl_path = ML_GetReplaceablePath(file_buf);

        /** Check if the file isn't replaced, or if Render Fix owns the replaced file **/
        if ( !PathIsGame(repl_path) && !PathIsRF(repl_path) )
            return false;
    }

    char opti_buf[256]; // optional file path

    /** Make optional folder PAK path **/
    snprintf(opti_buf, ARYLEN(opti_buf), "%s/optional/%s/PRS/%s.pak", mtGetModPath(), pcOptiFolder, pcPvrName);

    if ( !uFileExists(opti_buf) )
    {
        snprintf(opti_buf, ARYLEN(opti_buf), "/optional/%s/PRS/%s.pak", pcOptiFolder, pcPvrName);

        OutputFormat("RF WARN: (RFU_ReplacePvr) Texture PAK file \"%s\" was not found", opti_buf);

        return false;
    }

    ML_ReplaceFile(file_buf, opti_buf);

    return true;
}

static bool
ReplacePlayerPrsSub(const char* pcPrsName, const char* pcOptiFolder, const char* pcErrText)
{
    char file_buf[128]; // base file path

    /** Check for folder based player model files **/
    {
        snprintf(file_buf, ARYLEN(file_buf), "resource/gd_PC/%s/%s.ini", pcPrsName, pcPrsName);

        const char* const repl_path = ML_GetReplaceablePath(file_buf);

        /** Check if the file is replaced, or if Render Fix owns the replaced file **/
        if ( !PathIsGame(repl_path) && !PathIsRF(repl_path) )
            return false;
    }

    /** Check for PRS based player model files **/
    {
        snprintf(file_buf, ARYLEN(file_buf), "resource/gd_PC/%s.PRS", pcPrsName); // also used for replace path

        const char* const repl_path = ML_GetReplaceablePath(file_buf);

        /** Check if the file is replaced, or if Render Fix owns the replaced file **/
        if ( !PathIsGame(repl_path) && !PathIsRF(repl_path) )
            return false;
    }

    char opti_buf[256]; // optional file path

    snprintf(opti_buf, ARYLEN(opti_buf), "%s/optional/%s/%s.PRS", mtGetModPath(), pcOptiFolder, pcPrsName);

    if ( !uFileExists(opti_buf) )
    {
        snprintf(opti_buf, ARYLEN(opti_buf), "/optional/%s/%s.PRS", pcOptiFolder, pcPrsName);

        OutputFormat(pcErrText, opti_buf);

        return false;
    }

    ML_ReplaceFile(file_buf, opti_buf);

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
