/********************************/
/*  Includes                    */
/********************************/
/****** SAMT ************************************************************************************/
#include <samt/core.h>              /* core                                                     */
#include <samt/samdl.h>             /* samdl                                                    */
#include <samt/string.h>            /* str                                                      */
#include <samt/modloader.h>         /* replace path                                             */

/****** Ninja ***********************************************************************************/
#include <samt/ninja/njcommon.h>    /* object defs                                              */

/****** Render Fix ******************************************************************************/
#include <rf_core.h>                /* core                                                     */
#include <rf_usermsg.h>             /* msgbox                                                   */
#include <rf_mdlutil.h>             /* chunk compare                                            */

/****** Self ************************************************************************************/
#include <rf_samdl.h>               /* self                                                     */

#define RFMDL_PATH                  "resource/gd_PC/RFMDL"

#define BUF_LEN                     (256)

/********************************/
/*  Source                      */
/********************************/
/****** Error Out *******************************************************************************/
static void
FileError(c8* buf, const c8* fpath)
{
    mtStrFormat(buf, BUF_LEN, "Failed to load SAModel file 'RFMDL/%s'", fpath);

    RF_Alert("File Error", buf);
}

/****** Get Object ******************************************************************************/
mt_samdl*
RF_GetSAModel(const c8* puPath, s32 flag)
{
    c8 buf[256];

    mtStrFormat(buf, ARYLEN(buf), "%s/model/%s", mtGetModPath(), puPath);

    mt_samdl* p_samdl = mtSAModelLoad(buf, flag);

    if ( p_samdl )
    {
        RF_DbgInfo("Loaded samdl file: '/rf/model/%s'", puPath);
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

    RF_DbgInfo("Loaded samdl file: '/RFMDL/%s'", puPath);
    return p_samdl;
}

void
RF_FreeSAModel(mt_samdl* pSamdl)
{
    mtSAModelFree(pSamdl);
}

/****** Get List ********************************************************************************/
size
RF_GetSAModelList(RFS_SAMDL* restrict pSamdls, const size nbSamdl, s32 flag)
{
    size nb = 0;

    for ( size i = 0; i < nbSamdl; ++i )
    {
        if ( !pSamdls[i].puInPath )
        {
            continue;
        }

        mt_samdl* p_samdl = RF_GetSAModel(pSamdls[i].puInPath, flag);

        if ( !p_samdl )
        {
            continue;
        }

        pSamdls[i].pOutSamdl = p_samdl;

        nb++;
    }

    /** compare loaded models for duplicates, and free them **/

    for ( size ix_man = 0; ix_man < nbSamdl; ++ix_man )
    {
        mt_samdl* p_samdl = pSamdls[ix_man].pOutSamdl;

        if ( !p_samdl )
        {
            continue;
        }

        for ( size ix_cmp = ix_man+1; ix_cmp < nbSamdl; ++ix_cmp )
        {
            mt_samdl* p_samdl_cmp = pSamdls[ix_cmp].pOutSamdl;

            if ( !p_samdl_cmp
            ||    p_samdl_cmp == p_samdl
            ||    p_samdl->size != p_samdl_cmp->size )
            {
                continue;
            }

            if ( RF_CnkObjectMatch(p_samdl->pChunk, p_samdl_cmp->pChunk) )
            {
                mtSAModelFree( p_samdl_cmp );

                pSamdls[ix_cmp].pOutSamdl = p_samdl;

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
    mt_samdl* p_samdl = RF_GetSAModel(puPath, SAMDL_CHUNK);

    return p_samdl->pChunk;
}

NJS_CNK_MODEL*
RF_GetCnkModel(const c8* puPath)
{
    mt_samdl* p_samdl = RF_GetSAModel(puPath, SAMDL_CHUNK|SAMDL_MODEL);

    return p_samdl->pChunk->model;
}

/****** Ginja ***********************************************************************************/
GJS_OBJECT*
RF_GetGjsObject(const c8* puPath)
{
    mt_samdl* p_samdl = RF_GetSAModel(puPath, SAMDL_GINJA);

    return p_samdl->pGinja;
}

GJS_MODEL*
RF_GetGjsModel(const c8* puPath)
{
    mt_samdl* p_samdl = RF_GetSAModel(puPath, SAMDL_GINJA|SAMDL_MODEL);

    return p_samdl->pGinja->model;
}
