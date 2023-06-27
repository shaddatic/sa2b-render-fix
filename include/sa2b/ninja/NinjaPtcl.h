/*


    COPYRIGHT (C) SEGA ENTERSRISES,LTD.
*/

#ifndef _NINJA_PTCL_H_
#define _NINJA_PTCL_H_



void	njPtclPolygonStart( uint32 col );
void	njPtclPolygonEnd( void );
void	njPtclDrawPolygon( NJS_POINT3 *p, sint32 n, float32 h );
void	njPtclDrawPolygon2( NJS_POINT3 *p, sint32 n, float32 h );

void	njPtclSpriteStart( sint32 texid, uint32 col, sint32 flag );
void	njPtclSpriteEnd( void );
void	njPtclDrawSprite( NJS_POINT3 *p, sint32 n, float32 w, float32 h );

void	njPtclStripStart( void );
void	njPtclStripEnd( void );
void	njPtclStrip( NJS_POINT3 *p, uint32 col, sint32 n );

void	njPtclDrawObject( NJS_CNK_OBJECT *obj, float32 h );
sint32	njPtclDrawModel( NJS_CNK_MODEL *model, float32 h );

void	njPtclDrawMotion( NJS_CNK_OBJECT *object, NJS_MOTION *motion, float32 frame, float32 h );
void	njPtclDrawShapeMotion( NJS_CNK_OBJECT *object, NJS_MOTION *motion, NJS_MOTION *shape, float32 frame, float32 h );

#endif /* _NINJA_PTCL_H_ */

/*
 * End Of File
 */
