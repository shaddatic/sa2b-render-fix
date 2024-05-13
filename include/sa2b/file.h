/*
*   Sonic Adventure Mod Tools (SA2B) - '/file.h'
*
*   Description:
*       Contains functions related to opening and interacting with files & folders
*   using unicode (u) strings.
*
*   Contributors:
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _SAMT_FILE_H_
#define _SAMT_FILE_H_

EXTERN_START

/************************/
/*  Abstract Types      */
/************************/
/****** MSVC stdio ******************************************************************/
typedef struct _iobuf       FILE;

/************************/
/*  Constants           */
/************************/
/****** Max Path Length *************************************************************/
#ifndef PATH_MAX
#   define PATH_MAX    (260)
#endif

/************************/
/*  Enums               */
/************************/
/****** File Open Mode **************************************************************/
typedef enum
{
    FMODE_RB,   /* read only, start of file                             (byte mode) */
    FMODE_WB,   /* write only, new file                                 (byte mode) */
    FMODE_AB,   /* write only, end of file                              (byte mode) */

    FMODE_RT,   /* read only, start of file                             (text mode) */
    FMODE_WT,   /* write only, new file                                 (text mode) */
    FMODE_AT,   /* write only, end of file                              (text mode) */
}
ufmode;

/************************/
/*  File Functions      */
/************************/
/****** File Open *******************************************************************/
/*
*   Description:
*     Open a file using a ASCII/UTF-8 file path
*
*   Parameters:
*     - fpath   : path to file encoded in ASCII or UTF-8
*     - mode    : read/write permissions on the opened file
*
*   Returns:
*     Pointer to a FILE object, or nullptr if there was an error
*/
FILE*   uFileOpen( const utf8* fpath, ufmode mode );
/*
*   Description:
*     Write 'nb' bytes into an open FILE buffer from 'pBuf'
*
*   Parameters:
*     - f       : pointer to an open FILE object
*
*   Returns:
*     If the file was succesfully closed
*/
bool    uFileClose( FILE* f );

/****** File Read/Write *************************************************************/
/*
*   Description:
*     Read 'nb' bytes from an open FILE buffer into 'pBuf'
*
*   Parameters:
*     - f       : pointer to an open FILE object
*     - pBuf    : pointer to a buffer to read contents into
*     - nb      : number of bytes to read from 'f' into 'pBuf'
*
*   Returns:
*     Number of bytes written to the buffer, 0 indicates an error
*/
size_t  uFileRead( FILE* f, void* pBuf, size_t nb );
/*
*   Description:
*     Write 'nb' bytes into an open FILE buffer from 'pBuf'
*
*   Parameters:
*     - f       : pointer to an open FILE object
*     - pBuf    : pointer to a buffer to write contents from
*     - nb      : number of bytes to write into 'f' from 'pBuf'
*
*   Returns:
*     Number of bytes written to the file, 0 indicates an error
*/
size_t  uFileWrite( FILE* f, const void* pBuf, size_t nb );

/****** File Seek *******************************************************************/
/*
*   Description:
*     Set the seek offset to a specific position
*
*   Parameters:
*     - f       : pointer to an open FILE object
*     - offset  : position to set the seek offset to
*
*   Returns:
*     If successful
*/
bool    uFileSeekSet( FILE* f, int32_t offset );
/*
*   Description:
*     Move the seek offset relative to its current position
*
*   Parameters:
*     - f       : pointer to an open FILE object
*     - offset  : offset to move by
*
*   Returns:
*     If successful
*/
bool    uFileSeekAdvance( FILE* f, int32_t offset );
/*
*   Description:
*     Get the current seek offset
*
*   Parameters:
*     - f       : pointer to an open FILE object
*
*   Returns:
*     The current seek offset
*/
int32_t uFileSeekGet( FILE* f );
/*
*   Description:
*     Set seek offset to the start of the file
*
*   Parameters:
*     - f       : pointer to an open FILE object
*
*   Returns:
*     If successful.
*/
bool    uFileSeekStart( FILE* f );
/*
*   Description:
*     Set seek offset to the end of the file
*
*   Parameters:
*     - f       : pointer to an open FILE object
*
*   Returns:
*     If successful
*/
bool    uFileSeekEnd( FILE* f );

/****** File Size *******************************************************************/
/*
*   Description:
*     Get the total size of an open file buffer
*
*   Parameters:
*     - f       : pointer to an open FILE object
*
*   Returns:
*     The total size of the open file buffer
*/
size_t  uFileSize( FILE* f );

/****** File Load *******************************************************************/
/*
*   Description:
*     Load an entire file into a buffer with an optional returned size parameter
*
*   Parameters:
*     - fpath       : path to file encoded in ASCII or UTF-8
*     - pOptRetSize : pointer to a size_t used to return the size of the new buffer (optional)
*
*   Returns:
*     Memory buffer containing the entire file allocated with `malloc`, or nullptr
*   if there was an error.
*/
void*   uFileLoad( const utf8* fpath, size_t* pOptRetSize );

/****** File Ex'press ***************************************************************/
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
size_t  uFileReadEx( const utf8* fpath, void* pBuf, size_t nb );
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
size_t  uFileWriteEx( const utf8* fpath, const void* pBuf, size_t nb );
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
size_t  uFileAppendEx( const utf8* fpath, const void* pBuf, size_t nb );

/****** Filesystem Control **********************************************************/
/*
*   Description:
*     Move a file, if it exists, from 'fpathCur' to 'fpathNew'
*
*   Parameters:
*     - fpathCur : current path to the file
*     - fpathNew : new path to the file
*
*   Returns:
*     If success
*/
bool    uFileMove( const utf8* fpathCur, const utf8* fpathNew );
/*
*   Description:
*     Copy a file, if it exists, from 'fpathCur' to 'fpathNew'
*
*   Parameters:
*     - fpathCur : current path to the file
*     - fpathNew : path to place the copy at
*
*   Returns:
*     If success
*/
bool    uFileCopy( const utf8* fpathCur, const utf8* fpathNew );
/*
*   Description:
*     Rename a file, if it exists, at 'fpathCur' to 'fnameNew'
*
*   Examples:
*     uFileRename("./path/to/file.txt", "new.txt");
*
*   Parameters:
*     - fpathCur : current path to the file
*     - fnameNew : new name of the file, including the extension
*
*   Returns:
*     If success
*/
bool    uFileRename( const utf8* fpathCur, const utf8* fnameNew );

/****** Filesystem Query ************************************************************/
/*
*   Description:
*     Test if a given path points to a valid file
*
*   Parameters:
*     - fpath   : path to the file
*
*   Returns:
*     If the given path is valid
*/
bool    uFileExists( const utf8* fpath );

/************************/
/*  Directory Funcs     */
/************************/
/****** Filesystem Control **********************************************************/
/*
*   Description:
*     Create a directory at a given path. Will not create parent directories
*
*   Parameters:
*     - fpath   : path to the new directory
*
*   Returns:
*     If success
*/
bool    uDirectoryCreate( const utf8* fpath );
/*
*   Description:
*     Copy a directory and its contents at a given path
*
*   Parameters:
*     - fpathCur : path of the directory to copy
*     - fpathNew : path of the new copy
*/
bool    uDirectoryMove( const utf8* fpathCur, const utf8* fpathNew );
/*
*   Description:
*     Copy a directory and its contents at a given path
*
*   Parameters:
*     - fpathCur : path of the directory to copy
*     - fpathNew : path of the new copy
*/
void    uDirectoryCopy( const utf8* fpathCur, const utf8* fpathNew );
/*
*   Description:
*     Rename a directory, if it exists, at 'fpathCur' to 'fnameNew'
*
*   Examples:
*     uDirectoryRename("./path/to/directory", "newdir");
*
*   Parameters:
*     - fpathCur : current path to the file
*     - fnameNew : new name of the file, including the extension
*
*   Returns:
*     If success
*/
bool    uDirectoryRename( const utf8* fpathCur, const utf8* fnameNew );

/****** Filesystem Query ************************************************************/
/*
*   Description:
*     Test if a given path points to a valid directory
*
*   Parameters:
*     - fpath   : path to the directory
*
*   Returns:
*     If the given directory is valid
*/
bool    uDirectoryExists( const utf8* fpath );

EXTERN_END

#endif/*_SAMT_FILE_H_*/
