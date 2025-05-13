/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/file.h'
*
*   Description:
*     UTF-8 based file and filesystem controls, utilities, and functions.
*/
#ifndef H_SAMT_FILE
#define H_SAMT_FILE

EXTERN_START

/********************************/
/*  Opaque Types                */
/********************************/
/****** MSVC stdio ******************************************************************************/
typedef struct _iobuf               FILE; /* msvc std file type                                 */

/********************************/
/*  Enums                       */
/********************************/
/****** File Open Mode **************************************************************************/
typedef enum mt_fmode
{
    FMODE_RB,                       /* read only, start of file                     (byte mode) */
    FMODE_WB,                       /* write only, new file                         (byte mode) */
    FMODE_AB,                       /* write only, append file                      (byte mode) */
                                                                                    
    FMODE_RT,                       /* read only, start of file                     (text mode) */
    FMODE_WT,                       /* write only, new file                         (text mode) */
    FMODE_AT,                       /* write only, append file                      (text mode) */
                                                                                    
    FMODE_RB_RW,                    /* read/write, start of file                    (byte mode) */
    FMODE_WB_RW,                    /* read/write, new file                         (byte mode) */
    FMODE_AB_RW,                    /* read/write, append file                      (byte mode) */
                                                                                    
    FMODE_RT_RW,                    /* read/write, start of file                    (text mode) */
    FMODE_WT_RW,                    /* read/write, new file                         (text mode) */
    FMODE_AT_RW,                    /* read/write, append file                      (text mode) */
}
mt_fmode;

/********************************/
/*  Prototypes                  */
/********************************/
/************************************************************************************************/
/*
*   File Stream Control
*/
/****** File Open *******************************************************************************/
/*
*   Description:
*     Open a file stream for reading and/or writing.
*
*   Parameters:
*     - puPath      : path to file
*     - fmode       : read/write permissions on the opened file
*
*   Returns:
*     New FILE pointer; or 'nullptr' on failure.
*/
FILE*   mtFileOpen( const c8* puPath, mt_fmode fmode );
/*
*   Description:
*     Close an open file stream.
*
*   Parameters:
*     - f           : open file stream
*
*   Returns:
*     'true' if the file was succesfully closed; or 'false' on failure.
*/
bool    mtFileClose( FILE* f );

/****** File Read/Write *************************************************************************/
/*
*   Description:
*     Read from an open file stream, and advance the seek offset.
*
*   Parameters:
*     - f       : open file stream
*     - pDst    : read destination
*     - sz      : size of read, in bytes
*
*   Returns:
*     Number of bytes written to the buffer; or '0' on failure.
*/
size_t  mtFileRead( FILE* f, void* pDst, size_t sz );
/*
*   Description:
*     Write to an open file stream, and advance the seek offset.
*
*   Parameters:
*     - f       : open file stream
*     - pSrc    : write source
*     - sz      : size of write, in bytes
*
*   Returns:
*     Number of bytes written to the buffer; or '0' on failure.
*/
size_t  mtFileWrite( FILE* f, const void* pSrc, size_t sz );
/*
*   Description:
*     Write the same section of a source buffer to an open file stream multiple
*   times, and advance the seek offset.
*
*   Parameters:
*     - f       : open file stream
*     - pSrc    : write source
*     - sz      : size of write, in bytes
*     - nb      : number of times to repeat
*
*   Returns:
*     Number of bytes written to the buffer; or '0' on failure.
*/
size_t  mtFileWriteMulti( FILE* f, const void* pSrc, size_t sz, size_t nb );

/****** File Seek *******************************************************************************/
/*
*   Description:
*     Set the seek offset to a specific position
*
*   Parameters:
*     - f       : open file stream
*     - offset  : new seek offset, in bytes
*
*   Returns:
*     'true' on success; or 'false' on failure.
*/
bool    mtFileSeekSet( FILE* f, s32 offset );
/*
*   Description:
*     Move the seek offset relative to its current position
*
*   Parameters:
*     - f       : open file stream
*     - offset  : seek offset to advance, in bytes
*
*   Returns:
*     'true' on success; or 'false' on failure.
*/
bool    mtFileSeekAdvance( FILE* f, s32 offset );
/*
*   Description:
*     Get the current seek offset
*
*   Parameters:
*     - f       : open file stream
*
*   Returns:
*     The current seek offset of the file stream.
*/
s32     mtFileSeekGet( FILE* f );
/*
*   Description:
*     Set seek offset to the start of the file
*
*   Parameters:
*     - f       : open file stream
*
*   Returns:
*     'true' on success; or 'false' on failure.
*/
bool    mtFileSeekStart( FILE* f );
/*
*   Description:
*     Set seek offset to the end of the file
*
*   Parameters:
*     - f       : open file stream
*
*   Returns:
*     'true' on success; or 'false' on failure.
*/
bool    mtFileSeekEnd( FILE* f );

/****** File Size *******************************************************************************/
/*
*   Description:
*     Get the total size of an open file stream
*
*   Parameters:
*     - f       : open file stream
*
*   Returns:
*     The total size of the open file stream, in bytes.
*/
size_t  mtFileSize( FILE* f );

/************************************************************************************************/
/*
*   Load Whole File
*/
/****** File Load *******************************************************************************/
/*
*   Description:
*     Load an entire file into a buffer with an optional returned size parameter
*
*   Parameters:
*     - puPath      : file path
*     - pOptOutSize : pointer to a size_t used to return the size of the new buffer (optional)
*
*   Returns:
*     Memory buffer containing the entire file allocated with `malloc`, or nullptr
*   if there was an error.
*/
void*   mtFileLoad( const c8* puPath, size_t* pOptOutSize );

/************************************************************************************************/
/*
*   Read/Write/Append Ex
*/
/****** File Ex'press ***************************************************************************/
/*
*   Description:
*     Read the 'nb' bytes of a file at 'fpath' into 'pBuf'
*
*   Parameters:
*     - fpath   : path to file encoded in ASCII or UTF-8
*     - pBuf    : buffer to read into from file
*     - nb      : number of bytes to read into 'pBuf'
*
*   Returns:
*     Number of bytes written to the buffer, 0 indicates an error
*/
size_t  mtFileReadEx( const c8* puPath, void* pDst, size_t sz );
/*
*   Description:
*     Create & write 'nb' bytes into a file at 'fpath' from 'pBuf'
*
*   Parameters:
*     - fpath   : path to file encoded in ASCII or UTF-8
*     - pBuf    : buffer to write to file
*     - nb      : number of bytes to write out
*
*   Returns:
*     Number of bytes written to the file, 0 indicates an error
*/
size_t  mtFileWriteEx( const c8* puPath, const void* pSrc, size_t sz );
/*
*   Description:
*     Write 'nb' bytes to the end of a file at 'fpath' from 'pBuf'
*
*   Parameters:
*     - fpath   : path to file encoded in ASCII or UTF-8
*     - pBuf    : buffer to write out to file
*     - nb      : number of bytes to write out
*
*   Returns:
*     Number of bytes written to the file, 0 indicates an error
*/
size_t  mtFileAppendEx( const c8* puPath, const void* pSrc, size_t sz );

/************************************************************************************************/
/*
*   Filesystem (Files)
*/
/****** Filesystem Control **********************************************************************/
/*
*   Description:
*     Move a file.
*
*   Parameters:
*     - puPath      : file path
*     - puNewPath   : new file path
*
*   Returns:
*     'true' on success; or 'false' if the file doesn't exist or the new path is already taken.
*/
bool    mtFileMove( const c8* puPath, const c8* puNewPath );
/*
*   Description:
*     Copy a file.
*
*   Parameters:
*     - puPath      : file path
*     - puNewPath   : new file path
*
*   Returns:
*     'true' on success; or 'false' on failure.
*/
bool    mtFileCopy( const c8* puPath, const c8* puNewPath );
/*
*   Description:
*     Rename a file.
*
*   Examples:
*     - mtFileRename("./path/to/file.txt", "new.txt"); // "file.txt" -> "new.txt"
*
*   Parameters:
*     - puPath      : file path
*     - puNewName   : new name and extension for file
*
*   Returns:
*     'true' on success; or 'false' if the file doesn't exist or the new name is already taken.
*/
bool    mtFileRename( const c8* puPath, const c8* puNewName );
/*
*   Description:
*     Delete a file.
*
*   Parameters:
*     - puPath      : file path
*
*   Returns:
*     'true' on success; or 'false' on failure.
*/
bool    mtFileDelete( const c8* puPath );

/****** Filesystem Query ************************************************************************/
/*
*   Description:
*     Check if a path exists.
*
*   Parameters:
*     - puPath      : file path
*
*   Returns:
*     If the given path is a valid file.
*/
bool    mtFileExists( const c8* puPath );

/************************************************************************************************/
/*
*   Filesystem (Directories)
*/
/****** Filesystem Control **********************************************************************/
/*
*   Description:
*     Create a new directory.
*
*   Notes:
*     - Will not create any parent directories!
*
*   Parameters:
*     - puPath      : new directory path
*
*   Returns:
*     'true' on success; or 'false' on failure.
*/
bool    mtDirCreate( const c8* puPath );
/*
*   Description:
*     Move a directory and its contents.
*
*   Parameters:
*     - puPath      : directory path
*     - puNewPath   : new directory path
*
*   Returns:
*     'true' on success; or 'false' on failure.
*/
bool    mtDirMove( const c8* puPath, const c8* puNewPath );
/*
*   Description:
*     Copy a directory and its contents.
*
*   Parameters:
*     - puPath      : directory path
*     - puNewPath   : new directory path
*
*   Returns:
*     'true' on success; or 'false' on failure.
*/
void    mtDirCopy( const c8* puPath, const c8* puNewPath );
/*
*   Description:
*     Rename a directory.
*
*   Examples:
*     - mtDirRename("./path/to/directory", "newdir"); // "directory" -> "newdir"
*
*   Parameters:
*     - puPath      : directory path
*     - puNewName   : new directory name
*
*   Returns:
*     'true' on success; or 'false' on failure.
*/
bool    mtDirRename( const c8* puPath, const c8* puNewName );
/*
*   Description:
*     Delete a directory and all its contents.
*
*   Parameters:
*     - puPath      : directory path
*
*   Returns:
*     'true' on success; or 'false' on failure.
*/
bool    mtDirDelete( const c8* puPath );

/****** Filesystem Query ************************************************************************/
/*
*   Description:
*     Check if a path exists.
*
*   Parameters:
*     - puPath      : directory path
*
*   Returns:
*     If the given directory is a valid directory.
*/
bool    mtDirExists( const c8* puPath );

EXTERN_END

#endif/*H_SAMT_FILE*/
