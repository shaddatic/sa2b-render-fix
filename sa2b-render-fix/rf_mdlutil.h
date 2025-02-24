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
#include <samt/ninja/ninja.h>

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
*   Blending
*/
/** Source **/
void    RF_CnkBlendingSrc(       Sint16*         pPList, int idxMat, uint16_t src );
void    RF_CnkModelBlendingSrc(  NJS_CNK_MODEL*  pModel, int idxMat, uint16_t src );
void    RF_CnkObjectBlendingSrc( NJS_CNK_OBJECT* pObject,            uint16_t src );

/** Destination **/
void    RF_CnkBlendingDst(       Sint16*         pPList, int idxMat, uint16_t dst );
void    RF_CnkModelBlendingDst(  NJS_CNK_MODEL*  pModel, int idxMat, uint16_t dst );
void    RF_CnkObjectBlendingDst( NJS_CNK_OBJECT* pObject,            uint16_t dst );

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

/****** Model Compare ***************************************************************/
/*
*   Description:
*     Check if two seperate models exactly match each other, byte for byte,
*   excluding pointers. Plist and Vlist data is also scanned.
*
*   Parameters:
*     - pMdl1       : chunk model 1
*     - pMdl2       : chunk model 2
*
*   Returns:
*     'true' if models match; or 'false' if they do not.
*/
bool    RF_CnkModelMatch( const NJS_CNK_MODEL* pMdl1, const NJS_CNK_MODEL* pMdl2 );
/*
*   Description:
*     Check if two seperate object trees exactly match each other, byte for byte,
*   excluding pointers. Model data is also scanned.
*
*   Parameters:
*     - pObj1       : chunk object tree 1
*     - pObj2       : chunk object tree 2
*
*   Returns:
*     'true' if objects match; or 'false' if they do not.
*/
bool    RF_CnkObjectMatch( const NJS_CNK_OBJECT* pObj1, const NJS_CNK_OBJECT* pObj2 );

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
#define CnkBlendingSrc(_plist, _mat, _src)                      RF_CnkBlendingSrc((Sint16*)(_plist), (_mat), (_src))
#define CnkModelBlendingSrc(_mdl, _mat, _src)                   RF_CnkModelBlendingSrc((NJS_CNK_MODEL*)(_mdl), (_mat), (_src))
#define CnkObjectBlendingSrc(_obj, _src)                        RF_CnkObjectBlendingSrc((NJS_CNK_OBJECT*)(_obj), (_src))
#define CnkBlendingDst(_plist, _mat, _dst)                      RF_CnkBlendingDst((Sint16*)(_plist), (_mat), (_dst))
#define CnkModelBlendingDst(_mdl, _mat, _dst)                   RF_CnkModelBlendingDst((NJS_CNK_MODEL*)(_mdl), (_mat), (_dst))
#define CnkObjectBlendingDst(_obj, _dst)                        RF_CnkObjectBlendingDst((NJS_CNK_OBJECT*)(_obj), (_dst))
#define CnkChangeTexID(_plist, _idx, _tid)                      RF_CnkChangeTexID((Sint16*)(_plist), (_idx), (_tid))
#define CnkModelChangeTexID(_mdl, _idx, _tid)                   RF_CnkModelChangeTexID((NJS_CNK_MODEL*)(_mdl), (_idx), (_tid))
#define CnkObjectChangeTexID(_obj, _tid)                        RF_CnkObjectChangeTexID((NJS_CNK_OBJECT*)(_obj), (_tid))
#define CnkMaterialDiffuse(_plist, _mat, _a, _r, _g, _b)        RF_CnkMaterialDiffuse((Sint16*)(_plist), (_mat), (_a), (_r), (_g), (_b))
#define CnkModelMaterialDiffuse(_mdl, _mat, _a, _r, _g, _b)     RF_CnkModelMaterialDiffuse((NJS_CNK_MODEL*)(_mdl), (_mat), (_a), (_r), (_g), (_b))

#endif/*_RF_MDLUTIL_H_*/
