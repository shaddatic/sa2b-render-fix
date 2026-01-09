/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/util/ptrlist.h'
*
*   Description:
*     For listing a set of pointers in a sorted, ascending order.
*/
#ifndef H_SAMT_UTIL_PTRLIST
#define H_SAMT_UTIL_PTRLIST

EXTERN_START

/********************************/
/*  Structures                  */
/********************************/
/****** Pointer List ****************************************************************************/
typedef struct mt_ptrlist
{
    usize       max;                /* maximum number of pointers                               */
    const void* ptrs[];             /* pointer list, null terminated                            */
}
mt_ptrlist;

/********************************/
/*  Structures                  */
/********************************/
/****** Create/Free *****************************************************************************/
/*
*   Description:
*     Create a new pointer list.
*
*   Parameters:
*     - nbPtr       : fixed size of the pointer list
*
*   Returns:
*     New pointer list.
*/
mt_ptrlist* mtPtrListCreate( usize nbPtr );
/*
*   Description:
*     Free a pointer list.
*
*   Parameters:
*     - pPtrList    : pointer list
*/
void    mtPtrListFree( mt_ptrlist* pPtrList );

/****** Find ************************************************************************************/
/*
*   Description:
*     Find a pointer in the pointer list.
*
*   Parameters:
*     - pPtrList    : pointer list
*     - p           : pointer to search for
*
*   Returns:
*     Array index of pointer; or '-1' if not found.
*/
isize   mtPtrListFind( const mt_ptrlist* pPtrList, const void* p );

/****** Add/Sort ********************************************************************************/
/*
*   Description:
*     Add a pointer to the pointer list.
*
*   Notes:
*     - Duplicates will be ignored.
*
*   Parameters:
*     - pPtrList    : pointer list
*     - p           : pointer to add
*
*   Returns:
*     Array index of of pointer; or '-1' if there's no room left in the array.
*/
isize   mtPtrListAdd( mt_ptrlist* pPtrList, const void* p );
/*
*   Description:
*     Sort the pointers in the pointer list into ascending order.
*
*   Parameters:
*     - pPtrList    : pointer list
*/
void    mtPtrListSort( mt_ptrlist* pPtrList );

EXTERN_END

#endif/*H_SAMT_UTIL_PTRLIST*/
