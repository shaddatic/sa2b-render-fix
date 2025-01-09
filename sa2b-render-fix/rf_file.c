#include <sa2b/core.h>
#include <sa2b/model.h>
#include <sa2b/modloader.h>

/** Ninja **/
#include <sa2b/ninja/ninja.h>

/** Std **/
#include <stdio.h>

/** Render Fix **/
#include <rf_core.h>
#include <rf_usermsg.h>

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

    const char* fpath = ML_GetReplaceablePath(buf);

    NJS_CNK_OBJECT* object = MDL_ChunkLoadObjectFile(fpath);

    if (!object)
        RF_FileError(buf);
    
    return object;
}

NJS_CNK_MODEL*
RF_ChunkLoadModelFile(const char* fname)
{
    char buf[260];

    snprintf(buf, 260, "./" MODEL_PATH "/%s.sa2mdl", fname);

    const char* fpath = ML_GetReplaceablePath(buf);

    NJS_CNK_MODEL* model = mtLoadChunkModelFile(fpath);

    if (!model)
        RF_FileError(buf);

    return model;
}

GJS_OBJECT*
RF_GinjaLoadObjectFile(const char* fname)
{
    char buf[260];

    snprintf(buf, 260, "./" MODEL_PATH "/%s.sa2bmdl", fname);

    const char* fpath = ML_GetReplaceablePath(buf);

    GJS_OBJECT* object = MDL_GinjaLoadObjectFile(fpath);

    if (!object)
        RF_FileError(buf);

    return object;
}
