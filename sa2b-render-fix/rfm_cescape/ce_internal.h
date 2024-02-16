/*
*   SA2 Render Fix - '/rfm_cescape/ce_internal.h'
*
*   Description:
*       Internal header for City Escape module.
*
*   Contributors:
*   -   Shaddatic
*/
#ifndef _RFM_CESCAPE_INTERNAL_H_
#define _RFM_CESCAPE_INTERNAL_H_

/************************/
/*  Abstract Types      */
/************************/
typedef struct task         TASK;

/************************/
/*  Functions           */
/************************/
EXTERN_START
void    ObjectTreeShadows(TASK* tp);

EXTERN_END

#endif/*_RFM_CESCAPE_INTERNAL_H_*/
