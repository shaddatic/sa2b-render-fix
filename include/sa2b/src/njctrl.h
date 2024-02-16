/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/njctrl.h'
*
*   Contains Ninja wrapper tools made for the Adventure games and this toolkit.
*   Many of these were inlined away, so the toolkit has recreated all of them.
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SA2B_NJCTRL_H_
#define _SA2B_NJCTRL_H_

/************************/
/*  Data                */
/************************/
/** Used by the game to save and load, not SAMT 
    SAMT uses it's own variables for all these functions **/
#define __control_3d_flag_      DataRef(uint32_t, 0x01DEB6A4)
#define __constant_attr_and_    DataRef(uint32_t, 0x01DEB6A8)
#define __constant_attr_or_     DataRef(uint32_t, 0x01DEB6A0)

/************************/
/*  Functions           */
/************************/
EXTERN_START
void    SaveControl3D( void );
void    LoadControl3D( void );

void    OnControl3D(  uint32_t flag );
void    OffControl3D( uint32_t flag );

void    SaveConstantAttr( void );
void    LoadConstantAttr( void );

void    OnConstantAttr(  uint32_t soc_and, uint32_t soc_or );
void    OffConstantAttr( uint32_t soc_and, uint32_t soc_or );

void    SaveConstantMaterial( void );
void    LoadConstantMaterial( void );

void    SetConstantMaterial( float32_t a, float32_t r, float32_t g, float32_t b );

void    ResetConstantMaterial( void );

/** Toolkit additions **/
void    SaveCurrentTexList( void );
void    LoadCurrentTexList( void );

EXTERN_END

#endif /* _SA2B_NJCONTROL_H_ */
