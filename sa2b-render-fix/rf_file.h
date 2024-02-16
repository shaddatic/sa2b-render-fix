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
#include <sa2b/ninja/ninja.h>

/************************/
/*  Functions           */
/************************/
EXTERN_START
/** Load Chunk object file (.sa2mdl) **/
NJS_CNK_OBJECT* RF_ChunkLoadObjectFile(const char* fname);

/** Load Ginja object file (.sa2bmdl) **/
GJS_OBJECT*     RF_GinjaLoadObjectFile(const char* fname);

EXTERN_END

#endif/*_RF_FILE_H_*/
