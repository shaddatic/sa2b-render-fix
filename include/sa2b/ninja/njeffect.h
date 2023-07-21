/*
*   Sonic Adventure Mod Tools (SA2B) - '/ninja/njeffect.h'
*
*   Contains typedefs and functions for Ninja effects
*
*   Contributors:
*   -   SEGA,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _NJEFFECT_H_
#define _NJEFFECT_H_

typedef Float	NJS_FOG_TABLE[128];

extern	Float	_nj_depth_near_;    // MIA
extern	Float	_nj_depth_far_;     // MIA
extern	Float	_nj_depth_range_;   // MIA
extern	Int		_nj_depth_enable_;  // MIA

DataRef(Int,    _nj_fog_enable_, 0x025EFFCC);

/************************/
/*	 Fog				*/
/************************/
void	njFogEnable(void);
void	njFogDisable(void);

#endif