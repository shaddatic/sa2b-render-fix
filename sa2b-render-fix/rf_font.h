/*
*   SA2 Render Fix - '/rf_font.h'
*
*   Description:
*       Render Fix Font module.
*
*   Contributors:
*   -   Shaddatic
*/
#ifndef _RF_FONT_H_
#define _RF_FONT_H_

/************************/
/*  Includes            */
/************************/
/****** API Header ******************************************************************/
#include <rfapi_font.h>             /* font api header                              */

EXTERN_START

/************************/
/*  Functions           */
/************************/
/****** Font ************************************************************************/
/*
*   Load a game font file.
*
*   Parameters:
*     - fpath   : full path to font file
*     - ftype   : file type of font
*
*   Returns:
*       Pointer to the created font object, or nullptr if there was an error
*/
RFS_FONT*   RF_FontLoadFile( const c8* fpath, RFE_FONT_FTYPE ftype );
/*
*   Half the current space character width.
*
*   Japanese ASCII fonts use half the width of their Latin counterpart. Render Fix
*   doesn't know what is ASCII & what is ASCII_J, so only applies regular ASCII
*   space widths. Use this to fix your Japanese ASCII fonts.
*
*   Parameters:
*     - pFont   : pointer to font object
*/
void    RF_FontHalfSpace( RFS_FONT* pFont );

/****** Advanced Font ***************************************************************/
/*
*   Set custom character width map. The first entry is the space character.
*
*   Parameters:
*     - pFont   : pointer to font object
*     - pLeft   : pointer to width list that's at least as long as there are characters in the font (96, 224, or 3423)
*/
void    RF_FontSetLeft( RFS_FONT* pFont, uint8_t* pLeft );

/****** Font States *****************************************************************/
/*
*   Replace a font in the vanilla game by language and type.
*
*   Parameters:
*     - language : language to apply the font to
*     - type     : type of the font to replace
*     - pFont    : pointer to font object to replace with
*/
void    RF_FontReplace( RFE_FONT_LANG language, RFE_FONT_TYPE type, RFS_FONT* pFont );
/*
*   Get current font by language and type. This can be used to temporarily replace a
*   font for drawing, then re-applying the original font once you're done.
*
*   Parameters:
*     - language : language to get the font from
*     - type     : type of the font to get
*
*   Returns:
*       The current font being used for that language and type
*/
RFS_FONT*   RF_FontGet( RFE_FONT_LANG language, RFE_FONT_TYPE type );
/*
*   Replace a font in Chao World by type.
*
*   Parameters:
*     - type     : type of the font to replace
*     - pFont    : pointer to font object to replace with
*/
void    RF_FontChaoReplace( RFE_FONT_TYPE type, RFS_FONT* pFont );
/*
*   Get current font in Chao World by type. This can be used to temporarily replace
*   a font for drawing, then re-applying the original font once you're done.
*
*   Parameters:
*     - type     : type of the font to get
*/
RFS_FONT*   RF_FontChaoGet( RFE_FONT_TYPE type );

EXTERN_END

#endif/*_RF_FONT_H_*/
