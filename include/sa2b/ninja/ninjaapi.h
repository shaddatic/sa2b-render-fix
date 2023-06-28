/*
	Ninja Library
	
	COPYRIGHT (C) SEGA ENTERSRISES,LTD.
*/

#ifndef _NINJA_API_H_
#define _NINJA_API_H_


/*--------------------------------------*/
/*      Prototype                       */
/*--------------------------------------*/

/************************/
/*	System				*/
/************************/
void	njSetBackColor(uint32 col1, uint32 col2, uint32 col3);

/************************/
/*	Draw				*/
/************************/
void    njDrawPolygon(NJS_POLYGON_VTX* polygon, sint32 count, sint32 trans);
void    njDrawTexture(NJS_TEXTURE_VTX* polygon, sint32 count, sint32 tex, sint32 flag);
void    njDrawTextureMemList(NJS_TEXTURE_VTX* polygon, sint32 count, sint32 tex, sint32 flag);
void    njDrawTextureH(NJS_TEXTUREH_VTX* polygon, sint32 count, sint32 tex, sint32 flag);

void    njDrawPolygon3DEx(NJS_POLYGON_VTX* p, sint32 count, sint32 trans);
void	njDrawPolygon3DExStart(sint32 trans);
void    njDrawPolygon3DExSetData(NJS_POLYGON_VTX* p, sint32 count);
void	njDrawPolygon3DExEnd(void);

void	njDrawTexture3DEx(NJS_TEXTURE_VTX* p, sint32 count, sint32 trans);
void	njDrawTexture3DExStart(sint32 trans);
void	njDrawTexture3DExSetData(NJS_TEXTURE_VTX* p, sint32 count);
void	njDrawTexture3DExEnd(void);

/************************/
/*	Model				*/
/************************/

void	njControl3D(uint32 flag);
void	njSetConstantAttr(uint32 and_attr, uint32 or_attr);
void	njSetConstantMaterial(NJS_ARGB* mat);

/************************/
/*	Motion				*/
/************************/
DataRef(void*, _nj_cnk_motion_callback_, 0x01A55834);

void	njCnkDrawMotion( NJS_CNK_OBJECT *object, NJS_MOTION *motion, float32 frame );
void	njCnkSetMotionCallback( void (*func)(NJS_CNK_OBJECT *cnkobj) );

/************************/
/*	Draw2D				*/
/************************/

void	njDrawPoint2D(NJS_POINT2COL *p, sint32 n, float32 pri, uint32 attr);
void	njDrawLine2D(NJS_POINT2COL *p, sint32 n, float32 pri, uint32 attr);
void	njDrawTriangle2D(NJS_POINT2COL *p, sint32 n, float32 pri, uint32 attr);
void	njDrawPolygon2D(NJS_POINT2COL *p, sint32 n, float32 pri, uint32 attr);		/* Ignores 'n' argument, always uses 4 */
void	njDrawCircle2D(NJS_POINT2COL *p, sint32 n, float32 pri, uint32 attr);

/************************/
/*	Math				*/
/************************/
#define njAbs(n)         ((float32)fabsf   ((float32)(n)))
#define njArcCos(n)      ((Angle)NJM_RAD_ANG(acosf  ((float32)(n)) ))
#define njArcCosec(n)    ((Angle)NJM_RAD_ANG(asinf  (1.0f/(float32)(n)) ))
#define njArcCot(n)      ((Angle)NJM_RAD_ANG(atanf  (1.0f/(float32)(n)) ))
#define njArcSec(n)      ((Angle)NJM_RAD_ANG(acosf  (1.0f/(float32)(n)) ))
#define njArcSin(n)      ((Angle)NJM_RAD_ANG(asinf  ((float32)(n)) ))
#define njArcTan(n)      ((Angle)NJM_RAD_ANG(atanf  ((float32)(n)) ))
#define njArcTan2(y,x)   ((Angle)NJM_RAD_ANG(atan2f ((float32)(y),(float32)(x)) ))

#define njCeil(n)        ((float32)ceilf   ((float32)(n)))
#define njCosech(n)      ((float32)( 1.0f / sinhf((float32)NJM_ANG_RAD(n)) ))
#define njCosh(n)        ((float32)coshf   ((float32)NJM_ANG_RAD(n)))
#define njCoth(n)        ((float32)( 1.0f / tanhf((float32)NJM_ANG_RAD(n)) ))
#define njExp(x)         ((float32)expf((x)))
#define njFloor(n)       ((float32)floorf  ((float32)(n)))
#define njHypot(x,y)     ((float32)njSqrt  ( (x)*(x) + (y)*(y) ))
#define njLog(n)         ((float32)logf    ((float32)(n)))
#define njLog10(n)       ((float32)log10f  ((float32)(n)))
#define njLog2(n)        ((float32)( njLog((n)) / njLog(2.f) ))
#define njPow(n1,n2)     ((float32)powf    ((float32)(n1),(float32)(n2)))
#define njSech(n)        ((float32)( 1.0 / coshf((float32)NJM_ANG_RAD(n)) ))
#define njSinh(n)        ((float32)sinhf   ((float32)NJM_ANG_RAD(n)))
#define njTanh(n)        ((float32)tanhf   ((float32)NJM_ANG_RAD(n)))
#define njRandom()       ((float32)((float32)rand()/(float32)(RAND_MAX+1)))
#define njRandomSeed(n)  (srand((uint32)(n)))

float32 njCos		(Angle n);
float32	njCosec     (Angle n);
float32	njCot       (Angle n);
float32	njFraction  (float32 n);
float32	njInvertSqrt(float32 n);
float32	njRoundOff  (float32 n);
float32	njRoundUp   (float32 n);
float32	njSec       (Angle n);
float32 njSin		(Angle n);
float32	njSqrt      (float32 n);
float32	njTan       (Angle n);

/************************/
/*	Matrix				*/
/************************/

void	njInitMatrix(NJS_MATRIX *m, sint32 n, sint32 flag);
void	njCalcPoints(NJS_MATRIX *m, NJS_POINT3 *ps, NJS_POINT3 *pd, sint32 num);
void	njCalcVectors(NJS_MATRIX *m, NJS_VECTOR *vs, NJS_VECTOR *vd, sint32 num);
void    njGetTranslation(NJS_MATRIX *m, NJS_POINT3 *p);
void    njUnitTransPortion(NJS_MATRIX *m);
void    njUnitRotPortion(NJS_MATRIX *m);
void    njClearMatrix();
bool32	njPushMatrix(NJS_MATRIX_PTR m);
bool32	njPopMatrix(uint32 n);
void	njUnitMatrix(NJS_MATRIX *m);
void	njSetMatrix(NJS_MATRIX* md, NJS_MATRIX* ms);
void	njGetMatrix(NJS_MATRIX *m);
void	njAddMatrix(NJS_MATRIX *md, NJS_MATRIX *ms);
void	njSubMatrix(NJS_MATRIX *md, NJS_MATRIX *ms);
void	njMultiMatrix(NJS_MATRIX *md, NJS_MATRIX *ms);
void	njTranslate(NJS_MATRIX* m, float32 x, float32 y, float32 z);
void	njTranslateV(NJS_MATRIX* m, NJS_POINT3* v);
void	njRotateX(NJS_MATRIX* m, Angle x);
void	njRotateY(NJS_MATRIX* m, Angle y);
void	njRotateZ(NJS_MATRIX* m, Angle z);
void	njRotateXYZ(NJS_MATRIX *m, Angle angx, Angle angy, Angle angz);
void	njRotateZXY(NJS_MATRIX *m, Angle angx, Angle angy, Angle angz);
void	njRotate(NJS_MATRIX *m, NJS_VECTOR *v, Angle ang);
void	njScale(NJS_MATRIX* m, float32 sx, float32 sy, float32 sz);
void	njScaleV(NJS_MATRIX *m, NJS_VECTOR *v);
bool32	njInvertMatrix(NJS_MATRIX *m);
void	njTransposeMatrix(NJS_MATRIX *m);
float32	njDetMatrix(NJS_MATRIX *m);
void	njResMatrix(NJS_MATRIX *m, Angle *ang,NJS_VECTOR *scale,NJS_VECTOR *trans);
void	njProject(NJS_MATRIX *m,NJS_PLANE *pl);
void    njProject2(NJS_MATRIX *m, NJS_PLANE *pl, NJS_POINT3 *v, NJS_POINT3*p);
void	njMirror(NJS_MATRIX *m,NJS_PLANE *pl);

void	njCalcPoint(NJS_MATRIX* m, NJS_POINT3* ps, NJS_POINT3* pd);
void	njAddVector(NJS_VECTOR *vd, NJS_VECTOR *vs);
void	njSubVector(NJS_VECTOR *vd, NJS_VECTOR *vs);
void	njCalcVector(NJS_MATRIX* m, NJS_VECTOR* vs, NJS_VECTOR* vd);
float32	njUnitVector(NJS_POINT3* p);
float32	njScalor(NJS_VECTOR* v);
float32	njScalor2(NJS_VECTOR *v);
void	njProjectScreen(NJS_MATRIX *m, NJS_POINT3 *p3, NJS_POINT2 *p2);
float32	njOuterProduct(NJS_VECTOR *v1, NJS_VECTOR *v2, NJS_VECTOR *ov);
float32	njInnerProduct(NJS_VECTOR *v1, NJS_VECTOR *v2);

/************************/
/*	 Matrix Ex Funcion  */
/************************/

void	njTranslateEx(NJS_VECTOR* v);
void	njRotateEx(Angle* ang, sint32 lv);
void	njScaleEx(NJS_VECTOR *v);

bool32	njPopMatrixEx( void );
bool32	njPushMatrixEx( void );

void	njQuaternionEx(NJS_QUATERNION *qua);

/************************/
/*	Collision   		*/
/************************/

bool32	njIsParalellL2L(NJS_LINE *l1, NJS_LINE *l2);
bool32	njIsParalellL2PL(NJS_LINE *l, NJS_PLANE *pl);
bool32	njIsParalellPL2PL(NJS_PLANE *pl1, NJS_PLANE *pl2);
float32	njDistanceP2P(NJS_POINT3 *p1, NJS_POINT3 *p2);
float32	njDistanceP2L(NJS_POINT3 *p, NJS_LINE *l, NJS_POINT3 *cp);
float32	njDistanceP2PL(NJS_POINT3 *p, NJS_PLANE *pl, NJS_POINT3 *cp);
float32	njDistanceL2L(NJS_LINE *l1, NJS_LINE *l2, NJS_POINT3 *cp1, NJS_POINT3 *cp2);
float32	njDistanceL2PL(NJS_LINE *l, NJS_PLANE *pl, NJS_POINT3 *cp);
float32	njDistancePL2PL(NJS_PLANE *pl1, NJS_PLANE *pl2, NJS_LINE *l);
void	njGetPlaneNormal(NJS_POINT3 *p, NJS_VECTOR *v);
void	njGetPlaneNormal2(NJS_POINT3 *p0, NJS_POINT3 *p1, NJS_POINT3 *p2, NJS_VECTOR *v);
sint32     njCollisionCheckBB(NJS_BOX *h1, NJS_BOX *h2);
sint32     njCollisionCheckSS(NJS_SPHERE *sphere1, NJS_SPHERE *sphere2);
sint32     njCollisionCheckCC(NJS_CAPSULE *h1, NJS_CAPSULE *h2);
sint32     njCollisionCheckSC(NJS_SPHERE *sphere, NJS_CAPSULE *capsule);
sint32     njCollisionCheckBS(NJS_BOX *box, NJS_SPHERE *sphere);
sint32     njCollisionCheckBC(NJS_BOX *box, NJS_CAPSULE *capsule);


/************************/
/*	View				*/
/************************/

void    njSetScreen(NJS_SCREEN *s);
void    njSetScreenDist(float32 tgtdist);
void	njSetPerspective(Angle ang);
void    njSetAspect(float32 ax, float32 ay);
void    njInitView(NJS_VIEW *v);
void    njSetView(NJS_VIEW *v);
/* 削除予定 */
void    njUnitViewMatrix(NJS_VIEW *v);
void    njMultiViewMatrix(NJS_VIEW *v, NJS_MATRIX *m);
void    njRotateViewX(NJS_VIEW *v, Angle ang);
void    njRotateViewY(NJS_VIEW *v, Angle ang);
void    njRotateViewZ(NJS_VIEW *v, Angle ang);
void    njRotateViewXYZ(NJS_VIEW *v, Angle ax, Angle ay, Angle az);
void    njTranslateView(NJS_VIEW *v, float32 x, float32 y, float32 z);
void    njTranslateViewV(NJS_VIEW *v, NJS_POINT3 *p);
/* ここまで */
void    njRotateViewXRelative(NJS_VIEW *v, Angle ang);
void    njRotateViewYRelative(NJS_VIEW *v, Angle ang);
void    njRotateViewZRelative(NJS_VIEW *v, Angle ang);
void    njRotateViewXYZRelative(NJS_VIEW *v, Angle ax, Angle ay, Angle az);
void    njTranslateViewRelative(NJS_VIEW *v, float32 x, float32 y, float32 z);
void    njTranslateViewVRelative(NJS_VIEW *v, NJS_POINT3 *p);
void    njForwardViewRelative(NJS_VIEW *v, float32 x);
void    njRotateViewXAbsolute(NJS_VIEW *v, Angle ang);
void    njRotateViewYAbsolute(NJS_VIEW *v, Angle ang);
void    njRotateViewZAbsolute(NJS_VIEW *v, Angle ang);
void    njRotateViewXYZAbsolute(NJS_VIEW *v, Angle ax, Angle ay, Angle az);
void    njTranslateViewAbsolute(NJS_VIEW *v, float32 x, float32 y, float32 z);
void    njTranslateViewVAbsolute(NJS_VIEW *v, NJS_POINT3 *p);
void    njForwardViewAbsolute(NJS_VIEW *v, float32 x);
void    njSetBaseView(NJS_VIEW *v);
void    njReturn2BaseView(NJS_VIEW *v);
void	njLookAtView(NJS_VIEW *v, float32 x, float32 y, float32 z);
void	njLookAtViewV(NJS_VIEW *v, NJS_POINT3 *p);
void    njClip2D(NJS_POINT2 *v);
void    njClipZ(float32 n, float32 f);
int     njCalcScreen(NJS_POINT3 *p, float32 *sx, float32 *sy);
void    njRotateViewPosXRelative(NJS_VIEW *v, Angle ang);
void    njRotateViewPosYRelative(NJS_VIEW *v, Angle ang);
void    njRotateViewPosZRelative(NJS_VIEW *v, Angle ang);
void    njRotateViewPosXAbsolute(NJS_VIEW *v, Angle ang);
void    njRotateViewPosYAbsolute(NJS_VIEW *v, Angle ang);
void    njRotateViewPosZAbsolute(NJS_VIEW *v, Angle ang);
void    njUnitViewVector(NJS_VIEW *v);

/************************/
/*	Graphics3D			*/
/************************/

void    njDrawPoint3D(NJS_POINT3COL *p, sint32 n, uint32 attr);
void    njDrawLine3D(NJS_POINT3COL *p, sint32 n, uint32 attr);
void    njDrawTriangle3D(NJS_POINT3COL *p, sint32 n, uint32 attr);
void    njDrawPolygon3D(NJS_POINT3COL *p, sint32 n, uint32 attr);

/************************/
/*	 Light Funcion		*/
/************************/
void	njCreateLight(NJS_LIGHT_PTR, sint32);
void	njDeleteLight(NJS_LIGHT_PTR);
void	njLightOn(NJS_LIGHT_PTR);
void	njLightOff(NJS_LIGHT_PTR);
void	njSetLight(NJS_LIGHT_PTR);

void	njSetLightLocation(NJS_LIGHT_PTR, float32, float32, float32);
void	njSetLightDirection(NJS_LIGHT_PTR, float32, float32, float32);
void	njSetLightColor(NJS_LIGHT_PTR, float32, float32, float32);
void	njSetLightAlpha(NJS_LIGHT_PTR, float32);
void	njSetLightIntensity(NJS_LIGHT_PTR, float32, float32, float32);
void	njSetLightAngle(NJS_LIGHT_PTR, Angle, Angle);
void	njSetLightRange(NJS_LIGHT_PTR, float32, float32);
void	njSetUserLight(NJS_LIGHT_PTR, NJF_LIGHT_FUNC);

void	njMultiLightMatrix(NJS_LIGHT_PTR, NJS_MATRIX*);
void	njRotateLightXYZ(NJS_LIGHT_PTR, Angle, Angle, Angle);
void	njRotateLightX(NJS_LIGHT_PTR, Angle);
void	njRotateLightY(NJS_LIGHT_PTR, Angle);
void	njRotateLightZ(NJS_LIGHT_PTR, Angle);
void	njTranslateLightV(NJS_LIGHT_PTR, NJS_VECTOR*);
void	njTranslateLight(NJS_LIGHT_PTR, float32, float32, float32);
void	njUnitLightMatrix(NJS_LIGHT_PTR);

void	njDeleteAllLight(void);
void	njLightAllOff(void);
void	njLightAllOn(void);

void    njCnkSetAmbient(float32 r, float32 g, float32 b);

/************************/
/*	 Texture Funcion	*/
/************************/
void	njInitTextureBuffer(sint8 *addr,uint32 elemsize);
void	njInitTexture(NJS_TEXMEMLIST *addr,uint32 n);
void	njInitTextureGlobalIndex(uint32 globalIndex);
void	njExitTexture(void);
void	njInitCacheTextureBuffer(sint8 *addr,uint32 elemsize);
sint32	njLoadTexture(NJS_TEXLIST *texlist);
sint32	njLoadTextureNum(uint32 n);
void	njSetTexture(NJS_TEXLIST* texlist);
sint32	njSetTextureNum(uint32 n);
sint32	njSetTextureNumG(uint32 globalIndex);
sint32	njGetTextureNumG(void);
void	njReleaseTextureAll(void);
void	njReleaseTexture(NJS_TEXLIST* texlist);
sint32	njReleaseTextureNum(uint32 n);
sint32	njReleaseTextureNumG(uint32 globalIndex);
void	njReleaseCacheTextureAll(void);
sint32	njReleaseCacheTextureNum(uint32 n);
sint32	njReleaseCacheTextureNumG(uint32 globalIndex);
uint32	njCalcTexture(uint32 flag);
sint32	njLoadCacheTexture(NJS_TEXLIST *texlist);
sint32	njLoadCacheTextureNum(uint32 n);
sint32	njLoadCacheTextureNumG(uint32 globalIndex);
void	njSetTexturePath(const char *path);
void	njSetTextureInfo(NJS_TEXINFO *info,uint16 *tex,sint32 Type,sint32 nWidth,sint32 nHeight);
void	njSetTextureName(NJS_TEXNAME *texname,void *addr,uint32 globalIndex,uint32 attr);
sint32	njReLoadTextureNum(uint32 n,void *texaddr,uint32 attr,uint32 lod);
sint32	njReLoadTextureNumG(uint32 globalIndex,void *texaddr,uint32 attr,uint32 lod);
void	njRenderTextureNum(uint32 n);
void	njRenderTextureNumG(uint32 globalIndex);
void	njSetRenderWidth(uint32 nWidth);
void	njFrameBufferBmp(char *bmp,char *buffer);
void	njSetPvmTextureList(NJS_TEXLIST *texlist,NJS_TEXNAME *texname,char *filename,sint32 elemsize);
sint32	njLoadTexturePvmFile(const char *filename,NJS_TEXLIST *texlist);
sint32 	njLoadTexturePvmMemory(uint8 *addr,NJS_TEXLIST *texlist);
void 	njSetPaletteBankNum(uint32 n,sint32 bank);
void 	njSetPaletteBankNumG(uint32 globalIndex,sint32 bank);
void 	njSetPaletteMode(uint32 mode);
uint32	njGetPaletteMode(void);
void 	njSetPaletteData(sint32 offset,sint32 count,void* string);
void	njGetPaletteData(sint32 offset,sint32 count,void* string);
sint32 	njLoadPaletteFile(const char *filename,NJS_TEXPALETTE *pl);
sint32 	njReLoadVQCodebookNum(uint32 n,void *texaddr,uint32 attr);
sint32 	njReLoadVQCodebookNumG(uint32 globalIndex,void *texaddr,uint32 attr);
void 	njTwiddledTexture(sint16 *dst,sint16* src,sint32 elemsize);
sint32	njReLoadRectangleTexturePartNum(uint32 n,void *texaddr,uint32 attr,uint32 *p);
sint32	njReLoadRectangleTexturePartNumG(uint32 globalIndex,void *texaddr,uint32 attr,uint32 *p);
sint32	njReLoadTexturePartNum(uint32 n,sint8 *addr,uint32 offset,uint32 elemsize);
sint32	njReLoadTexturePartNumG(uint32 globalIndex,sint8 *addr,uint32 offset,uint32 elemsize);
sint32	njLoadTextureReq(NJS_TEXLIST *texlist);
sint32	njLoadTextureReqStop(void);
void	njSetSizeYUV420(uint32 nWidth,uint32 nHeight);
sint32	njLoadTextureYUV420Num(uint32 n,uint32 *string);
sint32	njLoadTextureYUV420NumG(uint32 globalIndex,uint32 *string);
void	njGarbageTexture(NJS_TEXMEMLIST *addr,uint32 n);
NJS_TEXERRSTAT *njGetTextureErrStat(void);
sint32	njReadTextureNum(uint32 n,sint8 *addr);
sint32	njReadTextureNumG(uint32 globalIndex,sint8 *addr);
uint32	njCalcTextureSize(uint32 nWidth,uint32 nHeight,uint32 nTextureType);
void	njSetTextureParam(NJS_TEXMEMLIST *texmemlist);

uint32 *njLoadPvrHeader(NJS_PVRHEADERDATA *pvrh,uint32 *globalIndex,uint32 *pTexture);
sint32 njGetTexSurface(NJS_TEXMEMLIST* texmemlist,NJS_PVRHEADERDATA *pvrh);
sint32 njLoadTexturePartLow(NJS_TEXMEMLIST* texmemlist,uint32 *pTexture,uint32 offset,uint32 elemsize);
sint32 njReleaseTextureLow(NJS_TEXMEMLIST* texmemlist);
sint32 njLoadTextureFinishDMA(void);

sint32 njReadRectangleTexturePartNum(uint32 n,void *texaddr,uint32 *p);
sint32 njReadRectangleTexturePartNumG(uint32 globalIndex,void *texaddr,uint32 *p);

/************************/
/*	 Scroll Funcion		*/
/************************/
void	njDrawScroll(NJS_SCROLL *scl);


/************************/
/*	 Debug Font Funcion	*/
/************************/
void 	njInitPrint(uint32 *texture,uint32 elemsize,uint32 attr);
void 	njExitPrint(void);
void	njPrintSize(uint16 elemsize);
void	njPrintColor(uint32 c);
void	njPrintC(sint32 loc,const char *s);
void	njPrintD(sint32 loc,sint32 val,sint32 digit);
void	njPrintB(sint32 loc,uint32 val,sint32 digit);
void	njPrintH(sint32 loc,uint32 val,sint32 digit);
void	njPrintF(sint32 loc,float32 val,sint32 digit);
void	njPrint(sint32 loc,const char *fmt, ...);

/************************/
/*	 Sprite				*/
/************************/
void	njDrawSprite2D( NJS_SPRITE *sp, sint32 n, float32 pri, uint32 attr );
void	njDrawSprite3D( NJS_SPRITE *sp, sint32 n, uint32 attr );

/************************/
/*	 Fog				*/
/************************/
void	njFogEnable();
void	njFogDisable();
void	njSetFogDensity(uint32 density);
void	njSetFogColor(uint32 c);
void	njSetFogTable(NJS_FOG_TABLE fog);
void	njGenerateFogTable(NJS_FOG_TABLE fog);
void	njGenerateFogTable2(NJS_FOG_TABLE fog, float32 f);
void	njGenerateFogTable3(NJS_FOG_TABLE fog, float32 n, float32 f);
uint32	njGenerateFogDensity(float32 f);

/************************/
/*	 Fade				*/
/************************/
void	njFadeEnable();
void	njFadeDisable();
void	njSetFadeColor(uint32 c);
void	njExecuteFade(float32 f);

/************************/
/*	 Camera				*/
/************************/
void	njForwardCameraPosition(NJS_CAMERA *c, float32 x);
void	njInitCamera(NJS_CAMERA *c);
void	njPitchCameraInterest(NJS_CAMERA *c, Angle ang);
void	njPointCameraInterest( NJS_CAMERA*, float, float, float );
void	njRollCameraInterest( NJS_CAMERA*, Angle );
void	njRotateCameraPositionX(NJS_CAMERA *c, Angle ang);
void	njRotateCameraPositionXYZ(NJS_CAMERA *c, Angle ax, Angle ay, Angle az);
void	njRotateCameraPositionY(NJS_CAMERA *c, Angle ang);
void	njRotateCameraPositionZ(NJS_CAMERA *c, Angle ang);
void	njSetCameraDepth(NJS_CAMERA *c, float32 n, float32 f);
void	njSetCameraAngle( NJS_CAMERA*, Angle );
void	njSetCamera( NJS_CAMERA* );
void	njTranslateCameraPosition(NJS_CAMERA *c, float32 x, float32 y, float32 z);
void	njYawCameraInterest(NJS_CAMERA *c, Angle ang);

/************************/
/*	 Binary				*/
/************************/
sint8	*njOpenBinary(const char *fname);
void	njCloseBinary(sint8 *wbuff);
void	*njReadBinary(sint8 *wbuff, uint32 *fpos, uint32 *ptype);

#endif /* _NINJA_API_H_ */
