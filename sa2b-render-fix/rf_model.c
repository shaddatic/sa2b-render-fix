/********************************/
/*  Includes                    */
/********************************/
/****** SAMT ************************************************************************************/
#include <samt/core.h>              /* core                                                     */
#include <samt/samdl.h>             /* samdl                                                    */
#include <samt/string.h>            /* str                                                      */
#include <samt/modloader.h>         /* replace path                                             */
#include <samt/memory.h>            /* memory                                                   */
#include <samt/file.h>              /* file                                                     */

/****** Ninja ***********************************************************************************/
#include <samt/ninja/njcommon.h>    /* object defs                                              */

/****** Render Fix ******************************************************************************/
#include <rf_core.h>                /* core                                                     */
#include <rf_mdlutil.h>             /* chunk compare                                            */
#include <rfu_njbin.h>              /* ninja binary                                             */

/****** Self ************************************************************************************/
#include <rf_model.h>               /* self                                                     */

/********************************/
/*  Constants                   */
/********************************/
/****** Paths ***********************************************************************************/
#define LOCAL_PATH                  "model"
#define RFMDL_PATH                  "resource/gd_PC/RFMDL"

/****** Str Buffer ******************************************************************************/
#define BUF_LEN                     (256)

/********************************/
/*  Source                      */
/********************************/
/****** Common File *****************************************************************************/
static void*
GetObjectFromFile(const c8* puPath, const c8* puBinExt, const c8* puMdlExt, bool(*fnBinCheck)(u32))
{
    c8 strbuf[BUF_LEN];

    // try local ninja binary
    mtStrFormat(strbuf, ARYLEN(strbuf), "%s/model/%s%s", mtGetModPath(), puPath, puBinExt);

    if ( mtFileExists(strbuf) )
    {
        void* p_obj = RFU_NinjaBinaryGet(strbuf, fnBinCheck);

        // found? Return!
        if ( p_obj )
        {
            RF_DbgExtra("Loaded local model file: '/model/%s%s'", puPath, puBinExt);
            return p_obj;
        }
    }

    // no local files, try external paths!
    enum
    {
        FTYPE_NJBIN,
        FTYPE_SAMDL,
    };

    i32 ftype = FTYPE_NJBIN;

    // get the file type depending on which mod index is higher
    // unless the mod loader is too old, then skip this step
    if ( mlGetVersion() >= ML_MINVER_FILEMODIX )
    {
        // get njbin index
        mtStrFormat(strbuf, ARYLEN(strbuf), "./" RFMDL_PATH "/%s%s", puPath, puBinExt);

        const isize ix_njbin = mlGetFileModIndex(strbuf);

        // get samdl index
        mtStrFormat(strbuf, ARYLEN(strbuf), "./" RFMDL_PATH "/%s%s", puPath, puMdlExt);

        const isize ix_samdl = mlGetFileModIndex(strbuf);

        // set file type based on which has a higher index
        ftype = (ix_njbin >= ix_samdl) ? FTYPE_NJBIN : FTYPE_SAMDL;
    }

    if ( ftype == FTYPE_NJBIN )
    {
        mtStrFormat(strbuf, ARYLEN(strbuf), "./" RFMDL_PATH "/%s%s", puPath, puBinExt);

        const c8* pu_fpath = mlGetReplacedFile(strbuf);

        if ( pu_fpath != strbuf )
        {
            void* p_obj = RFU_NinjaBinaryGet(pu_fpath, fnBinCheck);

            // found? Return!
            if ( p_obj )
            {
                RF_DbgExtra("Loaded model file: '/RFMDL/%s%s'", puPath, puBinExt);
                return p_obj;
            }
        }
    }
    else // FTYPE_SAMDL
    {
        mtStrFormat(strbuf, ARYLEN(strbuf), "./" RFMDL_PATH "/%s%s", puPath, puMdlExt);

        const c8* pu_fpath = mlGetReplacedFile(strbuf);

        if ( pu_fpath != strbuf )
        {
            void* p_obj = mtSAModelLoad(pu_fpath, SAMDL_NOHEAD);

            // found? Return!
            if ( p_obj )
            {
                RF_DbgExtra("Loaded model file: '/RFMDL/%s%s'", puPath, puMdlExt);
                return p_obj;
            }
        }
    }

    // otherwise, no file. Panic!
    RF_MsgWarn("File Error", "Failed to model load file '/RFMDL/%s'", puPath);
    return nullptr;
}

/****** Basic ***********************************************************************************/
static bool
IsBscModelBinary(u32 name)
{
    return (name == 'NJBM');
}

NJS_OBJECT*
RF_GetBscObject(const c8* puPath)
{
    return GetObjectFromFile(puPath, ".nj", ".sa1mdl", IsBscModelBinary);
}

NJS_MODEL*
RF_GetBscModel(const c8* puPath)
{
    NJS_OBJECT* object = RF_GetBscObject(puPath);

    return object ? object->model : nullptr;
}

/****** Chunk ***********************************************************************************/
static bool
IsCnkModelBinary(u32 name)
{
    return (name == 'NJCM' || name == 'N2CM');
}

NJS_CNK_OBJECT*
RF_GetCnkObject(const c8* puPath)
{
    return GetObjectFromFile(puPath, ".nj", ".sa2mdl", IsCnkModelBinary);
}

NJS_CNK_MODEL*
RF_GetCnkModel(const c8* puPath)
{
    NJS_CNK_OBJECT* object = RF_GetCnkObject(puPath);

    return object ? object->model : nullptr;
}

/****** Ginja ***********************************************************************************/
static bool
IsGjsModelBinary(u32 name)
{
    return (name == 'GJCM');
}

GJS_OBJECT*
RF_GetGjsObject(const c8* puPath)
{
    return GetObjectFromFile(puPath, ".gj", ".sa2bmdl", IsGjsModelBinary);
}

GJS_MODEL*
RF_GetGjsModel(const c8* puPath)
{
    GJS_OBJECT* object = RF_GetGjsObject(puPath);

    return object ? object->model : nullptr;
}

/****** Get List ********************************************************************************/
isize
RF_GetCnkObjectList(RFS_OBJFILE* restrict pObjs, const isize nbObj)
{
    isize nb = 0;

    for ( isize i = 0; i < nbObj; ++i )
    {
        if ( !pObjs[i].puPath )
        {
            continue;
        }

        NJS_CNK_OBJECT* p_object = RF_GetCnkObject(pObjs[i].puPath);

        if ( !p_object )
        {
            continue;
        }

        pObjs[i].pObject = p_object;

        nb++;
    }

    /** compare loaded models for duplicates, and free them **/

    for ( isize ix_man = 0; ix_man < nbObj; ++ix_man )
    {
        NJS_CNK_OBJECT* p_obj = pObjs[ix_man].pObject;

        if ( !p_obj )
        {
            continue;
        }

        for ( isize ix_cmp = ix_man+1; ix_cmp < nbObj; ++ix_cmp )
        {
            NJS_CNK_OBJECT* p_obj_cmp = pObjs[ix_cmp].pObject;

            if ( !p_obj_cmp || p_obj_cmp == p_obj )
            {
                continue;
            }

            if ( RF_CnkObjectMatch(p_obj, p_obj_cmp) )
            {
                mtFree( p_obj_cmp );

                pObjs[ix_cmp].pObject = p_obj;

                nb--;
            }
        }
    }

    return nb;
}
