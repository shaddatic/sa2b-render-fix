/*
*   Sonic Adventure Mod Tools (SA2B) - '/ninja/njdraw.h'
*
*   Contains functions, macros, structs, and typedefs for basic drawing
*
*   Contributors:
*     - SEGA,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _NJDRAW_H_
#define _NJDRAW_H_

/*--------------------------------------*/
/*      Scroll Structure                */
/*--------------------------------------*/

#define NJM_MAP(celnum,u,v) (((celnum) << 16 | (u) << 8 | (v)))
#define NJM_MAPCELL(map)    (((map) >> 16)&0x0000FFFF)
#define NJM_MAPU(map)       (((map) >> 8)&0x000000FF)
#define NJM_MAPV(map)       ((map)&0x000000FF)

/*
 * NJS_SCLATTR
 */
typedef Uint32 NJS_SCLATTR;     /* scroll attribute structure   */

/*
 * NJS_SCLMTRX
 */
typedef Float NJS_SCLMTRX[4];   /* scroll rotation matrix       */

/*
 * NJS_SCROLL
 */
typedef struct {
    Uint16      celps;          /* pixel size of the cells      */
    Uint16      mapw;           /* number of the width of map   */
    Uint16      maph;           /* number of the height of map  */
    Uint16      sw, sh;         /* size of the scroll draw      */
    NJS_TEXLIST* list;          /* texlist ID                   */
    Uint32*     map;            /* map array pointer            */
    Float       px, py;         /* scroll transration           */
    Float       bx, by;         /* map draw scroll              */
    Float       pr;             /* priority                     */
    Uint16      sflag;          /* scale flag                   */
    Float       sx, sy;         /* scale x,y                    */
    Float       spx, spy;       /* center of scale x,y            */
    Uint16      mflag;          /* matrix flag                  */
    Float       cx, cy;         /* center of rotation x,y       */
    NJS_SCLMTRX m;              /* rotation matrix              */
    Uint32      colmode;        /* color mode                   */
    NJS_POINT2  clip[2];
    NJS_SCLATTR attr;           /* scroll attribute             */
    NJS_COLOR   sclc;
}NJS_SCROLL;

enum {
    _SM00,_SM01,
    _SM10,_SM11
};

/*--------------------------------------*/
/*      Sprite                          */
/*--------------------------------------*/
typedef struct {
    Sint16      sx, sy;         /* size             */
    Sint16      cx, cy;         /* center           */
    Sint16      u1, v1;         /* upper left       */
    Sint16      u2, v2;         /* lower right      */
    Sint16      texid;          /* texture id       */
    Sint16      attr;           /* attribute        */
} NJS_TEXANIM;

typedef struct {
    NJS_POINT3   p;             /* point            */
    Float        sx, sy;        /* scale            */
    Angle        ang;           /* angle            */
    NJS_TEXLIST* tlist;         /* texture list     */
    NJS_TEXANIM* tanim;         /* animation list   */
} NJS_SPRITE;

/*--------------------------------------*/
/*      Quad Draw                       */
/*--------------------------------------*/

typedef struct {
    Float    x1, y1, x2, y2;
    Float    u1, v1, u2, v2;
} NJS_QUAD_TEXTURE;

typedef struct {
    Float   x, y, z;
    Float   vx1, vy1;
    Float   vx2, vy2;
    Uint32  dmy;
    Float   u, v;
    Float   vu1, vv1;
    Float   vu2, vv2;
    Uint32  dmy2[2];
} NJS_QUAD_TEXTURE_EX;

/************************/
/*  Draw                */
/************************/
void    njDrawPolygon(NJS_POLYGON_VTX* polygon, Int count, Int trans);
void    njDrawTexture(NJS_TEXTURE_VTX* polygon, Int count, Int tex, Int flag);
void    njDrawTextureEx(NJS_TEXTURE_VTX* polygon, Int count, Int trans); /* Ignores 'count' argument, always 4 */
void    njDrawTextureHEx(NJS_TEXTUREH_VTX* polygon, Int count, Int trans);

void    njDrawPolygon2DExStart(Int trans);
void    njDrawPolygon2DExSetData(NJS_POLYGON_VTX* p, Int count);
void    njDrawPolygon2DExEnd(void);

void    njDrawTexture2DExStart(Int trans);
void    njDrawTexture2DExSetData(NJS_TEXTURE_VTX* p, Int count);
void    njDrawTexture2DExEnd(void);

void    njDrawTexture2DHExStart(Int trans);
void    njDrawTexture2DHExSetData(NJS_TEXTUREH_VTX* p, Int count);
void    njDrawTexture2DHExEnd(void);

void    njDrawPolygon3DEx(NJS_POLYGON_VTX* p, Int count, Int trans);
void    njDrawPolygon3DExStart(Int trans);
void    njDrawPolygon3DExSetData(NJS_POLYGON_VTX* p, Int count);
void    njDrawPolygon3DExEnd(void);

void    njDrawTexture3DEx(NJS_TEXTURE_VTX* p, Int count, Int trans);
void    njDrawTexture3DExStart(Int trans);
void    njDrawTexture3DExSetData(NJS_TEXTURE_VTX* p, Int count);
void    njDrawTexture3DExEnd(void);

void    njDrawTexture3DHEx(NJS_TEXTUREH_VTX* p, Int count, Int trans);
void    njDrawTexture3DHExStart(Int trans);
void    njDrawTexture3DHExSetData(NJS_TEXTUREH_VTX* p, Int count);
void    njDrawTexture3DHExEnd(void);

#define _nj_quad_color_     DATA_REF(Uint32, 0x01A54FF0)

void    njQuadTextureStart(Sint32 trans);
void    njQuadTextureEnd(void);
void    njSetQuadTexture(Sint32 texid, Uint32 col);
void    njSetQuadTextureG(Sint32 gid, Uint32 col);
void    njSetQuadTextureColor(Uint32 col);
void    njDrawQuadTexture(NJS_QUAD_TEXTURE* q, Float z);
void    njDrawQuadTextureEx(NJS_QUAD_TEXTURE_EX* q);
void    njSetQuadTextureH(Sint32 texid, Uint32 col, Uint32 off);
void    njSetQuadTextureHColor(Uint32 col, Uint32 off);

void    njDrawLineExStart(Float r, Uint32 BaseColor, Sint32 Trans); /* Ignores 'r' argument, always 1px */
void    njDrawLineExEnd(void);
void    njDrawLine3DExSetStrip(NJS_POINT3* vtx, Sint32 Count);
void    njDrawLine3DExSetList(NJS_POINT3* vtx, Sint32 Count);
void    njDrawLine2DExSetStrip(NJS_POINT2* vtx, Float ooz, Sint32 Count);
void    njDrawLine2DExSetList(NJS_POINT2* vtx, Float ooz, Sint32 Count);

/************************/
/*  Draw 2D             */
/************************/
/*
*   Parameters:
*     - p       : Pointer to a POINT2COL list
*     - n       : Number of entries in POINT2COL list
*     - pri     : Draw priority, between -1.f & -65535.f
*     - attr    : Draw attributes
*/
void    njDrawPoint2D(    NJS_POINT2COL* p, Sint32 n, Float pri, Uint32 attr );
void    njDrawLine2D(     NJS_POINT2COL* p, Sint32 n, Float pri, Uint32 attr );
void    njDrawTriangle2D( NJS_POINT2COL* p, Sint32 n, Float pri, Uint32 attr );
void    njDrawPolygon2D(  NJS_POINT2COL* p, Sint32 n, Float pri, Uint32 attr ); /* Ignores 'n' argument, always uses 4 */
void    njDrawCircle2D(   NJS_POINT2COL* p, Sint32 n, Float pri, Uint32 attr );

/************************/
/*  Sprite              */
/************************/
void    njDrawSprite2D( NJS_SPRITE* sp, Int n, Float pri, Uint32 attr );
void    njDrawSprite3D( NJS_SPRITE* sp, Int n,            Uint32 attr );

#endif
