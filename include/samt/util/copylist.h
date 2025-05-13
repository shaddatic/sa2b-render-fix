/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/util/copylist.h'
*
*   Description:
*     The 'copylist' utility is for copying a set of source buffers at arbitrary
*   locations into one singular buffer, in consecutive order.
*/
#ifndef H_SAMT_UTIL_COPYLIST
#define H_SAMT_UTIL_COPYLIST

/************************/
/*  Information         */
/************************/
/****** Overview ********************************************************************/
/*
*     The copylist function set is used to copy a set of arbitrarily located source
*   buffers into one, large, single buffer. This allows much easier handling of the
*   data, and increased memory locality when used for things such as Ninja object
*   trees and motions.
*/
/****** Instructions ****************************************************************/
/*
*   1. Create the copylist and add all of the source data pointers, including
*      their sizes, into it; ensuring that no pointers were added more than once.
* 
*   2. Get or create a buffer the size of the copylist or larger, then use the
*      'Copy' function to copy all the source data into it.
*
*   3. Resolve any pointers you want to point into the new copied data. This can
*      include data inside the copy buffer itself.
*
*   4. Free the copylist.
*/
/****** Examples ********************************************************************/
/*
*   //
*   // get chunk object and model data sizes
*   //
* 
*   NJS_CNK_OBJECT* p_obj = ... ;
*
*   const size_t sz_vlist = mtCnkGetVlistSize( p_obj->model->vlist );
*   const size_t sz_plist = mtCnkGetPlistSize( p_obj->model->plist );
*
*   //
*   // create copylist and add source data pointers and their sizes
*   //
* 
*   mt_copylist* pclh = mtCopyListCreate();
*
*   mtCopyListAdd( pclh, p_obj              , sizeof(NJS_CNK_OBJECT) );
*   mtCopyListAdd( pclh, p_obj->model       , sizeof(NJS_CNK_MODEL)  );
*   mtCopyListAdd( pclh, p_obj->model->vlist, sz_vlist               );
*   mtCopyListAdd( pclh, p_obj->model->plist, sz_plist               );
*
*   // stop duplicate source entry by checking for pointer first (this code is pointless, and is just for example)
*   if ( !mtCopyListExists( pclh, p_obj->model ) ) 
*   {
*       mtCopyListAdd( pclh, p_obj->model, sizeof(NJS_CNK_MODEL) );
*   }
*
*   //
*   // get size of copylist, alloc buffer, and copy all source data
*   //
* 
*   void* p_buf = MemAlloc( mtCopyListSize(pclh) );
*
*   mtCopyListCopy( pclh, p_buf );
*
*   //
*   // resolve pointers (in this context, we're only resolving pointers inside the
*   // buffer itself. But, it works exactly the same for pointers outside the buffer)
*   //
*
*   NJS_CNK_OBJECT* p_obj_buf = p_buf; // 'p_obj' was added first, so it will be at the top of the buffer
*
*   mtCopyListResolve( pclh, &p_obj_buf->model );
*   mtCopyListResolve( pclh, &p_obj_buf->model->vlist );
*   mtCopyListResolve( pclh, &p_obj_buf->model->plist );
*
*   //
*   // free the copylist
*   //
* 
*   mtCopyListFree( pclh );
*/

EXTERN_START

/************************/
/*  Opaque Types        */
/************************/
/****** Copylist ********************************************************************/
typedef struct mt_copylist      mt_copylist;

/************************/
/*  Prototypes          */
/************************/
/****** Create/Free *****************************************************************/
/*
*   Description:
*     Create a new, empty copylist.
*
*   Returns:
*     New copylist pointer
*/
mt_copylist* mtCopyListCreate( void );
/*
*   Description:
*     Free a copylist.
*/
void    mtCopyListFree( mt_copylist* pclh );

/****** Add Entry *******************************************************************/
/*
*   Description:
*     Add a source pointer entry to a copylist, using a pointer and size.
*
*   Notes:
*     - Please ensure each source pointer is only added once using the 'Exists'
*       function.
*
*   Parameters:
*     - pclh        : copylist header
*     - pSrc        : source data
*     - szSrc       : size of source data in bytes
*/
void    mtCopyListAdd( mt_copylist* pclh, const void* pSrc, size_t szSrc );

/****** Check Entry *****************************************************************/
/*
*   Description:
*     Check if a source pointer is already in the copylist.
*
*   Parameters:
*     - pclh        : copylist header
*     - pSrc        : source data
*
*   Returns:
*     'true' if the source pointer already exists in the copylist; or 'false' if it
*   does not.
*/
bool    mtCopyListExists( const mt_copylist* pclh, const void* pSrc );

/****** Copy To Buffer **************************************************************/
/*
*   Description:
*     Copy all source pointers into a buffer, in order. The buffer needs to be
*   large enough to store all source data, including padding. You can get the size
*   of the copylist using the 'GetSize' function.
*
*   Parameters:
*     - pclh        : copylist header
*     - pDst         : copy destination buffer
*/
void    mtCopyListCopy( const mt_copylist* pclh, void* pDst );
/*
*   Description:
*     Get the total size of the copylist. This is the buffer size needed to
*   successfully copy all source data.
*
*   Parameters:
*     - pclh        : copylist header
*
*   Returns:
*     Size of copylist, including padding.
*/
size_t  mtCopyListSize( const mt_copylist* pclh );

/****** Resolve Source Pointer ******************************************************/
/*
*   Description:
*     Redirect a source pointer to the newly copied data in the destination buffer.
*
*   Notes:
*     - This needs to be called *after* the source data has been copied into the
*       final buffer. If not, this function will produce 'nullptr' as there is no
*       copy location.
*     - If this returns 'false', and it's used correctly, it means this pointer is
*       already resolved and is pointing to the copy location.
*
*   Parameters:
*     - pclh        : copylist header
*     - ppSrc       : pointer to source pointer
*
*   Returns:
*     'true' if the source pointer was found and redirected to the copy; or 'false'
*   if it was not found.
*/
bool    mtCopyListResolve( const mt_copylist* pclh, const void** ppSrc );

EXTERN_START

#endif/*H_SAMT_UTIL_COPYLIST*/
