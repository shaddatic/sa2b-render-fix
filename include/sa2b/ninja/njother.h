/*
*   Sonic Adventure Mod Tools (SA2B) - '/ninja/njother.h'
*
*   Contains Ninja utilities not included in the libraries
*
*   Contributors:
*   -   SEGA,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _NINJA_OTHER_H_
#define _NINJA_OTHER_H_

/************************/
/*  Data                */
/************************/
/** Used by the game to save and load, 
    not SAMT **/
DataRef(uint32, __control_3d_flag_, 0x01DEB6A4);
DataRef(uint32, __constant_attr_and_, 0x01DEB6A8);
DataRef(uint32, __constant_attr_or_, 0x01DEB6A0);

/************************/
/*  Functions           */
/************************/
void	SaveControl3D();
void	LoadControl3D();

void	OnControl3D(uint32 flag);
void	OffControl3D(uint32 flag);

void	SaveConstantAttr();
void	LoadConstantAttr();

void	OnConstantAttr(uint32 soc_and, uint32 soc_or);
void	OffConstantAttr(uint32 soc_and, uint32 soc_or);

void	SaveConstantMaterial();
void	LoadConstantMaterial();

void	SetConstantMaterial(float32 a, float32 r, float32 g, float32 b);

void	SaveCurrentTexList();
void	LoadCurrentTexList();

#endif /* _NINJA_OTHER_H_ */