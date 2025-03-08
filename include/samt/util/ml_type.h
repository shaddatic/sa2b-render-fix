/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/util/ml_type.h'
*
*   Description:
*       Mod loader abstract type definitions.
*/
#ifndef H_SAMT_UTIL_MLTYPE
#define H_SAMT_UTIL_MLTYPE

EXTERN_START

/************************/
/*  Constants           */
/************************/
/****** Mod Loader Version **********************************************************/
#define ML_VERSION              (15) /* supported Mod loader version                */

/************************/
/*  Structures          */
/************************/
/****** Mod Loader Structures *******************************************************/
typedef s32                     ml_modinfo[10]; /* modinfo                          */
typedef struct ml_helpfuncs     ml_helpfuncs;   /* helperfunctions                  */

EXTERN_END

#endif/*H_SAMT_UTIL_MLTYPE*/
