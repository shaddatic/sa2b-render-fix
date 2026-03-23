/********************************/
/*  Includes                    */
/********************************/
/****** SAMT ************************************************************************************/
#include <samt/core.h>              /* core                                                     */
#include <samt/samdl.h>             /* samdl                                                    */
#include <samt/string.h>            /* str                                                      */
#include <samt/modloader.h>         /* replace path                                             */
#include <samt/memory.h>            /* memory                                                   */

/****** Ninja ***********************************************************************************/
#include <samt/ninja/njcommon.h>    /* object defs                                              */

/****** Render Fix ******************************************************************************/
#include <rf_core.h>                /* core                                                     */
#include <rf_mdlutil.h>             /* chunk compare                                            */

/****** Self ************************************************************************************/
#include <rf_samdl.h>               /* self                                                     */

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
/****** Error Out *******************************************************************************/
static void
FileError(c8* buf, const c8* puPath)
{
    mtStrFormat(buf, BUF_LEN, "Failed to load SAModel file 'RFMDL/%s'", puPath);

    RF_MsgWarn("File Error", buf);
}

/****** Get Object ******************************************************************************/
mt_samdl*
RF_GetSAModel(const c8* puPath, u32 flag)
{
    c8 buf[BUF_LEN];

    mtStrFormat(buf, ARYLEN(buf), "%s/model/%s", mtGetModPath(), puPath);

    mt_samdl* p_samdl = mtSAModelLoad(buf, flag);

    if ( p_samdl )
    {
        RF_DbgExtra("Loaded samdl file: '/rf/model/%s'", puPath);
        return p_samdl;
    }

    mtStrFormat(buf, ARYLEN(buf), "./" RFMDL_PATH "/%s", puPath);

    const c8* pu_replpath = mlGetReplacedFile(buf);

    p_samdl = mtSAModelLoad(pu_replpath, flag);

    if ( !p_samdl )
    {
        FileError(buf, puPath);

        return nullptr;
    }

    RF_DbgExtra("Loaded samdl file: '/RFMDL/%s'", puPath);
    return p_samdl;
}

void
RF_FreeSAModel(mt_samdl* pSamdl)
{
    mtSAModelFree(pSamdl);
}

/****** Get List ********************************************************************************/
isize
RF_GetSAModelList(RFS_MDLFILE* restrict pMdls, const isize nbSamdl, u32 flag)
{
    isize nb = 0;

    for ( isize i = 0; i < nbSamdl; ++i )
    {
        if ( !pMdls[i].puPath )
        {
            continue;
        }

        NJS_CNK_OBJECT* p_object = (NJS_CNK_OBJECT*) RF_GetSAModel(pMdls[i].puPath, SAMDL_NOHEAD|SAMDL_CHUNK);

        if ( !p_object )
        {
            continue;
        }

        pMdls[i].pObject = p_object;

        nb++;
    }

    /** compare loaded models for duplicates, and free them **/

    for ( isize ix_man = 0; ix_man < nbSamdl; ++ix_man )
    {
        NJS_CNK_OBJECT* p_obj = pMdls[ix_man].pObject;

        if ( !p_obj )
        {
            continue;
        }

        for ( isize ix_cmp = ix_man+1; ix_cmp < nbSamdl; ++ix_cmp )
        {
            NJS_CNK_OBJECT* p_obj_cmp = pMdls[ix_cmp].pObject;

            if ( !p_obj_cmp || p_obj_cmp == p_obj )
            {
                continue;
            }

            if ( RF_CnkObjectMatch(p_obj, p_obj_cmp) )
            {
                mtFree( p_obj_cmp );

                pMdls[ix_cmp].pObject = p_obj;

                nb--;
            }
        }
    }

    return nb;
}

/****** Chunk ***********************************************************************************/
NJS_CNK_OBJECT*
RF_GetCnkObject(const c8* puPath)
{
    return (NJS_CNK_OBJECT*) RF_GetSAModel(puPath, SAMDL_NOHEAD|SAMDL_CHUNK);
}

NJS_CNK_MODEL*
RF_GetCnkModel(const c8* puPath)
{
    NJS_CNK_OBJECT* object = (NJS_CNK_OBJECT*) RF_GetSAModel(puPath, SAMDL_NOHEAD|SAMDL_CHUNK|SAMDL_MODEL);

    return object ? object->model : nullptr;
}

/****** Ginja ***********************************************************************************/
GJS_OBJECT*
RF_GetGjsObject(const c8* puPath)
{
    return (GJS_OBJECT*) RF_GetSAModel(puPath, SAMDL_NOHEAD|SAMDL_GINJA);
}

GJS_MODEL*
RF_GetGjsModel(const c8* puPath)
{
    GJS_OBJECT* object = (GJS_OBJECT*) RF_GetSAModel(puPath, SAMDL_NOHEAD|SAMDL_GINJA|SAMDL_MODEL);

    return object ? object->model : nullptr;
}
