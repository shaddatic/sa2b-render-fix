/*
*   SA2 Render Fix - '/rf_file.h'
*
*   Description:
*       Contains functions to open files inside the replaceable
*   global directory, allowing other mods to replace models and
*   still be loaded by Render Fix.
*
*   Contributors:
*   -   Shaddatic
*/
#ifndef _RF_FILE_H_
#define _RF_FILE_H_

/************************/
/*  Includes            */
/************************/
#include <samt/ninja/ninja.h>

#include <samt/samdl.h>

/************************/
/*  Structures          */
/************************/
typedef struct
{
    const utf8* puPath;
    mt_samdl*   pSamdl;
}
LOAD_SAMDL_LIST;

/************************/
/*  Functions           */
/************************/
EXTERN_START
/** Load Chunk object file (.sa2mdl) **/
NJS_CNK_OBJECT* RF_ChunkLoadObjectFile(const char* fname);

/** Load Chunk object file (.sa2mdl) but only return the first model **/
NJS_CNK_MODEL*  RF_ChunkLoadModelFile(const char* fname);

/** Load Ginja object file (.sa2bmdl) **/
GJS_OBJECT*     RF_GinjaLoadObjectFile(const char* fname);

/** Load a list of Chunk object files, and free any duplicates **/
void    RF_LoadChunkObjectList(LOAD_SAMDL_LIST* pInOutList, size_t nbList);

EXTERN_END

#endif/*_RF_FILE_H_*/
