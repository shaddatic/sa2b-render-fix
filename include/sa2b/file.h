/*
*   Sonic Adventure Mod Tools (SA2B) - '/file.h'
*
*   Contains functions related to opening and interacting 
*   with files & folders using unicode (u) strings.
*
*   Contributors:
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SAMT_FILE_H_
#define _SAMT_FILE_H_

#include <stdio.h>

#ifndef PATH_MAX
#define PATH_MAX    (260)
#endif

/************************/
/*  Enums               */
/************************/
/** Open mode enum **/
typedef enum
{
    FMODE_R,
    FMODE_W,
    FMODE_RB,
    FMODE_WB
}
ufmode;

/************************/
/*  File Functions      */
/************************/
EXTERN_START
/** Open file with UTF-8 path string **/
FILE*   uFileOpen(const utf8* pPath, ufmode mode);
/** Buffer entire file, opt. return size **/
void*   uFileLoad(const utf8* pPath, size_t* pOptRetSize); 

void    uFileRename(const utf8* pOrig, const utf8* pNew);
bool    uFileCopy(const utf8* pOrig, const utf8* pNew);
bool    uFileExists(const utf8* pPath);

/************************/
/*  Folder Functions    */
/************************/
/** Creates folder at path **/
bool    uFolderCreate(const utf8* pPath);
/** Copies folder and contents **/
void    uFolderCopy(const utf8* pOrig, const utf8* pNew);

/************************/
/*  Path Functions      */
/************************/
/** Back-up path to parent folder by inserting '\0' **/
void    uPathToParent(utf8* pPath);

EXTERN_END

#endif /* _SAMT_FILE_H_ */
