/*
*   Sonic Adventure Mod Tools (SA2B) - '/ninja/njparticle.h'
*
*   Contains Ninja particle functions
*
*   Contributors:
*   -   SEGA,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _NINJA_PTCL_H_
#define _NINJA_PTCL_H_

void    njPtclPolygonStart(Uint32 col);
void    njPtclPolygonEnd(void);
void    njPtclDrawPolygon(NJS_POINT3* p, Sint32 n, Float h);

void    njPtclSpriteStart(Sint32 texid, Uint32 col, Sint32 flag);
void    njPtclSpriteEnd(void);
void    njPtclDrawSprite(NJS_POINT3* p, Sint32 n, Float w, Float h);

void    njPtclStripStart(void);
void    njPtclStripEnd(void);
void    njPtclStrip(NJS_POINT3* p, Uint32 col, Sint32 n);

#endif /* _NINJA_PTCL_H_ */

/*
 * End Of File
 */
