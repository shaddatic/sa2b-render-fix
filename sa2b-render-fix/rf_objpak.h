/*
*   SA2 Render Fix - '/rf_objpak.h'
*
*   Description:
*       For writing changes to the shader containing 'obj.pak'
*   file.
*
*   Contributors:
*   -   Shaddatic
*/
#ifndef _RF_OBJPAK_H_
#define _RF_OBJPAK_H_

/************************/
/*  Functions           */
/************************/
EXTERN_START
/** Initialize **/
void    RF_ObjPakInit( void );

/** Write file and flag a reload **/
int     RF_ObjPakWriteChangesToFile( void );

/** Register shadow map opacity **/
void    RF_ObjPakRegisterShadowOpacity( float opacity );
/** Register Xbox 360 screen tint removal **/
void    RF_ObjPakRegisterTintFix( bool bRemoveTint );

EXTERN_END

#endif/*_RF_OBJPAK_H_*/
