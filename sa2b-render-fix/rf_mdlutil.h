/*
*   SA2 Render Fix - '/rf_mdlutil.h'
*
*   Description:
*       Common Render Fix model utilities. 'Object' or
*   'LandTable' variants of functions will effect every Model
*   in the Object/Land tree.
*
*   Contributors:
*   -   Shaddatic
*/
#ifndef _RF_MDLUTIL_H_
#define _RF_MDLUTIL_H_

/************************/
/*  Includes            */
/************************/
#include <sa2b/ninja/ninja.h>

/************************/
/*  Abstract Types      */
/************************/
typedef struct _OBJ_LANDTABLE   OBJ_LANDTABLE;

/************************/
/*  Functions           */
/************************/
EXTERN_START
/*
*   Tint Fix 
*/
/** Ginja **/
void    RF_GjsModelTintFix(  GJS_MODEL*  pModel  );
void    RF_GjsObjectTintFix( GJS_OBJECT* pObject );

/** Chunk **/
void    RF_CnkTintFix(       Sint16*         pPList  );
void    RF_CnkModelTintFix(  NJS_CNK_MODEL*  pModel  );
void    RF_CnkObjectTintFix( NJS_CNK_OBJECT* pObject );

/*
*   Triangle Winding
*/
/** All strips & tris **/
void    RF_CnkModelFlipWinding( NJS_CNK_MODEL* pModel );

/** Specific strip or tri (use -1 to modify all) **/
void    RF_CnkModelFlipStripWinding( NJS_CNK_MODEL* pModel, int idxStrip, int idxTri );

/*
*   Material Flags
*/
/** On flag **/
void    RF_CnkMaterialFlagOn(          Sint16*         pPList, int idxMat, uint32_t flag );
void    RF_CnkModelMaterialFlagOn(     NJS_CNK_MODEL*  pModel, int idxMat, uint32_t flag );
void    RF_CnkObjectMaterialFlagOn(    NJS_CNK_OBJECT* pObject,            uint32_t flag );
void    RF_CnkLandTableMaterialFlagOn( OBJ_LANDTABLE*  pLand,              uint32_t flag );

/** Off flag **/
void    RF_CnkMaterialFlagOff(          Sint16*         pPList, int idxMat, uint32_t flag );
void    RF_CnkModelMaterialFlagOff(     NJS_CNK_MODEL*  pModel, int idxMat, uint32_t flag );
void    RF_CnkObjectMaterialFlagOff(    NJS_CNK_OBJECT* pObject,            uint32_t flag );
void    RF_CnkLandTableMaterialFlagOff( OBJ_LANDTABLE*  pLand,              uint32_t flag );

/*
*   Texture ID
*/
void    RF_CnkChangeTexID(       Sint16*         pPList, int idxTID, Sint16 texID );
void    RF_CnkModelChangeTexID(  NJS_CNK_MODEL*  pModel, int idxTID, Sint16 texID );
void    RF_CnkObjectChangeTexID( NJS_CNK_OBJECT* pObject,            Sint16 texID );

/*
*   Material Params
*/
/** Diffuse **/
void    RF_CnkMaterialDiffuse(      Sint16*        pPList, int idxMat, int a, int r, int g, int b );
void    RF_CnkModelMaterialDiffuse( NJS_CNK_MODEL* pModel, int idxMat, int a, int r, int g, int b );

EXTERN_END

/************************/
/*  Macro               */
/************************/
/** Quick macros (uint -> type*) **/
#define GjsModelTintFix(_mdl)                                   RF_GjsModelTintFix((GJS_MODEL*)(_mdl))
#define GjsObjectTintFix(_obj)                                  RF_GjsObjectTintFix((GJS_OBJECT*)(_obj))
#define CnkTintFix(_plist)                                      RF_CnkTintFix((Sint16*)(_plist));
#define CnkModelTintFix(_mdl)                                   RF_CnkModelTintFix((NJS_CNK_MODEL*)(_mdl))
#define CnkObjectTintFix(_obj)                                  RF_CnkObjectTintFix((NJS_CNK_OBJECT*)(_obj))
#define CnkModelFlipWinding(_mdl)                               RF_CnkModelFlipWinding((NJS_CNK_MODEL*)(_mdl))
#define CnkModelFlipStripWinding(_mdl, _strip, _tri)            RF_CnkModelFlipStripWinding((NJS_CNK_MODEL*)(_mdl), (_strip), (_tri))
#define CnkMaterialFlagOn(_plist, _mat, _flag)                  RF_CnkMaterialFlagOn((Sint16*)(_plist), (_mat), (_flag))
#define CnkModelMaterialFlagOn(_mdl, _mat, _flag)               RF_CnkModelMaterialFlagOn((NJS_CNK_MODEL*)(_mdl), (_mat), (_flag))
#define CnkObjectMaterialFlagOn(_obj, _flag)                    RF_CnkObjectMaterialFlagOn((NJS_CNK_OBJECT*)(_obj), (_flag))
#define CnkLandTableMaterialFlagOn(_lt, _flag)                  RF_CnkLandTableMaterialFlagOn((OBJ_LANDTABLE*)(_lt), (_flag))
#define CnkMaterialFlagOff(_plist, _mat, _flag)                 RF_CnkMaterialFlagOff((Sint16*)(_plist), (_mat), (_flag))
#define CnkModelMaterialFlagOff(_mdl, _mat, _flag)              RF_CnkModelMaterialFlagOff((NJS_CNK_MODEL*)(_mdl), (_mat), (_flag))
#define CnkObjectMaterialFlagOff(_obj, _flag)                   RF_CnkObjectMaterialFlagOff((NJS_CNK_OBJECT*)(_obj), (_flag))
#define CnkLandTableMaterialFlagOff(_lt, _flag)                 RF_CnkLandTableMaterialFlagOff((OBJ_LANDTABLE*)(_lt), (_flag))
#define CnkMaterialDiffuse(_plist, _mat, _a, _r, _g, _b)        RF_CnkMaterialDiffuse((Sint16*)(_plist), (_mat), (_a), (_r), (_g), (_b))
#define CnkModelMaterialDiffuse(_mdl, _mat, _a, _r, _g, _b)     RF_CnkModelMaterialDiffuse((NJS_CNK_MODEL*)(_mdl), (_mat), (_a), (_r), (_g), (_b))

#endif/*_RF_MDLUTIL_H_*/
