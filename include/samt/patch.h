/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/patch.h'
*
*   Description:
*     For writing variably sized code patches in a single, standardized function call.
*/
#ifndef H_SAMT_PATCH
#define H_SAMT_PATCH

EXTERN_START

/********************************/
/*  Structures                  */
/********************************/
/****** Patch Struct ****************************************************************************/
typedef struct mt_patch
{
    pint        ptr;                /* write address                                            */
    size        len;                /* patch size                                               */
    byte        dat[];              /* patch data                                               */
}
mt_patch;

/********************************/
/*  Prototypes                  */
/********************************/
/****** Write Patch *****************************************************************************/
/*
*   Description:
*     Write a patch to protected memory space.
*
*   Parameters:
*     - pPatch      : patch structure
*/
void    mtPatchWrite( const mt_patch* pPatch );

EXTERN_END

#endif/*H_SAMT_PATCH*/
