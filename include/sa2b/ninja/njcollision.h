/*
*   Sonic Adventure Mod Tools (SA2B) - '/ninja/njcollision.h'
*
*   Contains structs and functions for the Ninja built in collision system
*
*   Contributors:
*     - SEGA,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _NJ_COLLISION_H_
#define _NJ_COLLISION_H_

#define NJD_COL_DELTA       0.025f
#define NJD_COL_VERTICAL    0.0000001f
#define NJD_COL_PARALLEL    0.0000001f

//  Sphere
typedef struct {
    NJS_POINT3 c;
    Float      r;
} NJS_SPHERE;

//  Capsule
typedef struct {
    NJS_POINT3 c1;
    NJS_POINT3 c2;
    Float      r;
} NJS_CAPSULE;

//  Hexahedron
typedef struct {
    NJS_POINT3 v[8];
} NJS_BOX;

//  Parallelepiped (Hexahedron, Cuboid, Cube)
typedef struct {
    NJS_POINT3 p;
    NJS_VECTOR v[3];
} NJS_PARAHEXA;

/*
    Collision Detection
*/
/*  Sphere/Capsule Collision Detection    */
Sint32  njCollisionCheckSS( const NJS_SPHERE* sphere1, const NJS_SPHERE* sphere2 );
Sint32  njCollisionCheckCC( const NJS_CAPSULE* h1, const NJS_CAPSULE* h2 );
Sint32  njCollisionCheckSC( const NJS_SPHERE* sphere, const NJS_CAPSULE* capsule );

/*  Parallelepiped Collision Detection    */
Sint32  njCollisionCheckB2B2( const NJS_PARAHEXA* ca, const NJS_PARAHEXA* cb );
Sint32  njCollisionCheckB2C( const NJS_PARAHEXA* cubo, const NJS_CAPSULE* cp );
Sint32  njCollisionCheckB2S( const NJS_PARAHEXA* cubo, const NJS_SPHERE* sp );

/*  Old Box Collision Detection */
Sint32  njCollisionCheckBB( const NJS_BOX* h1, const NJS_BOX* h2 );
Sint32  njCollisionCheckBS( const NJS_BOX* box, const NJS_SPHERE* sphere );
Sint32  njCollisionCheckBC( const NJS_BOX* box, const NJS_CAPSULE* capsule );

/*
    Parallel Calculation
*/
Bool    njIsParalellL2L( const NJS_LINE* l1, const NJS_LINE* l2 );
Bool    njIsParalellL2PL( const NJS_LINE* l, const NJS_PLANE* pl );
Bool    njIsParalellPL2PL( const NJS_PLANE* pl1, const NJS_PLANE* pl2 );

/*
    Distance Calculation
*/
Float   njDistanceP2P( const NJS_POINT3* p1, const NJS_POINT3* p2 );
Float   njDistanceP2L( const NJS_POINT3* p, const NJS_LINE* l, NJS_POINT3* cp );
Float   njDistanceP2PL( const NJS_POINT3* p, const NJS_PLANE* pl, NJS_POINT3* cp );
Float   njDistanceL2L( const NJS_LINE* l1, const NJS_LINE* l2, NJS_POINT3* cp1, NJS_POINT3* cp2 );
Float   njDistanceL2PL( const NJS_LINE* l, const NJS_PLANE* pl, NJS_POINT3* cp );
Float   njDistancePL2PL( const NJS_PLANE* pl1, const NJS_PLANE* pl2, NJS_LINE* l );

/*
    Get Plane Normal
*/
void    njGetPlaneNormal( const NJS_POINT3* p, NJS_VECTOR* v );
void    njGetPlaneNormal2( const NJS_POINT3* p0, const NJS_POINT3* p1, const NJS_POINT3* p2, NJS_VECTOR* v );

/*
    Bounding Box Calculation
*/
void    njGetBoxMinMax( const NJS_BOX* hull, NJS_POINT3* min, NJS_POINT3* max );
void    njGetSphereMinMax( const NJS_SPHERE* hull, NJS_POINT3* min, NJS_POINT3* max );
void    njGetCapsuleMinMax( const NJS_CAPSULE* hull, NJS_POINT3* min, NJS_POINT3* max );
void    njGetBox2MinMax( const NJS_PARAHEXA* cubo, NJS_POINT3* min, NJS_POINT3* max );

#endif    /* _NJ_COLLISION_H_ */
