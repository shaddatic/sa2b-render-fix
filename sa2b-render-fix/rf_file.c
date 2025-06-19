#include <samt/core.h>
#include <samt/model.h>
#include <samt/modloader.h>
#include <samt/samdl.h>
#include <samt/memory.h>

/** Ninja **/
#include <samt/ninja/ninja.h>

/** Std **/
#include <stdio.h>

/** Render Fix **/
#include <rf_core.h>
#include <rf_usermsg.h>
#include <rf_mdlutil.h>

/** Self **/
#include <rf_file.h>

/** Constants **/
#define MODEL_PATH      "resource/gd_PC/RFMDL"

static void
RF_FileError(const char* fpath)
{
    char buf[128];

    snprintf(buf, sizeof(buf), "Failed to load file %s", fpath);

    RF_Alert("File Error", buf);
}

NJS_CNK_OBJECT*
RF_ChunkLoadObjectFile(const char* fname)
{
    char buf[260];

    snprintf(buf, 260, "./" MODEL_PATH "/%s.sa2mdl", fname);

    const char* fpath = mlGetReplacedFile(buf);

    mt_samdl* p_samdl = mtSAModelLoad(fpath, SAMDL_CHUNK);

    if ( !p_samdl )
    {
        RF_FileError(buf);
        return nullptr;
    }
    
    return p_samdl->pChunk;
}

NJS_CNK_MODEL*
RF_ChunkLoadModelFile(const char* fname)
{
    char buf[260];

    snprintf(buf, 260, "./" MODEL_PATH "/%s.sa2mdl", fname);

    const char* fpath = mlGetReplacedFile(buf);

    mt_samdl* p_samdl = mtSAModelLoad(fpath, SAMDL_CHUNK|SAMDL_MODEL);

    if ( !p_samdl )
    {
        RF_FileError(buf);
        return nullptr;
    }

    return p_samdl->pChunk->model;
}

void
RF_LoadChunkObjectList(LOAD_SAMDL_LIST* pInOutList, size_t nbList)
{
    for ( size_t i = 0; i < nbList; ++i )
    {
        if ( !pInOutList[i].puPath )
            continue;

        char buf[260];

        snprintf(buf, 260, "./" MODEL_PATH "/%s.sa2mdl", pInOutList[i].puPath);

        const char* fpath = mlGetReplacedFile(buf);

        mt_samdl* p_samdl = mtSAModelLoad(fpath, SAMDL_CHUNK);

        if ( !p_samdl )
        {
            RF_FileError(buf);
        }

        pInOutList[i].pSamdl = p_samdl;
    }

    /** compare loaded models for duplicates, and free them **/

    for ( size_t i = 0; i < nbList; ++i )
    {
        mt_samdl* p_samdl = pInOutList[i].pSamdl;

        if ( !p_samdl )
            continue;

        for ( size_t j = i+1; j < nbList; ++j )
        {
            mt_samdl* p_samdl_cmp = pInOutList[j].pSamdl;

            if ( !p_samdl_cmp || p_samdl_cmp == p_samdl || p_samdl->size != p_samdl_cmp->size )
                continue;

            if ( RF_CnkObjectMatch(p_samdl->pChunk, p_samdl_cmp->pChunk) )
            {
                mtSAModelFree( p_samdl_cmp );

                pInOutList[j].pSamdl = p_samdl;
            }
        }
    }
}

GJS_OBJECT*
RF_GinjaLoadObjectFile(const char* fname)
{
    char buf[260];

    snprintf(buf, 260, "./" MODEL_PATH "/%s.sa2bmdl", fname);

    const char* fpath = mlGetReplacedFile(buf);

    mt_samdl* p_samdl = mtSAModelLoad(fpath, SAMDL_GINJA);

    if ( !p_samdl )
    {
        RF_FileError(buf);
        return nullptr;
    }

    return p_samdl->pGinja;
}
