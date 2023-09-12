#pragma once

#include <sa2b/memtools.h>

#include <sa2b/ninja/ninja.h>

/*
*   Abstract Types
*/
typedef struct _OBJ_LANDTABLE   OBJ_LANDTABLE;

/*
*   Display Order Fixes
*/
#define DISP        0x14
#define DISP_DELY   0x1C
#define DISP_SORT   0x20
#define DISP_LATE   0x24
#define DISP_LAST   0x28
#define DISP_SHAD   0x2C

#define SwitchDisplayer(addr, disp) WriteData(addr + 2, disp, uint8) /* Use this on 'mov dword ptr' operations */

#define ReplaceFloat(addr, pflt) WritePointer(addr + 2, pflt)

/*
*   Chunk Tri Strip Winding
*/
void    CnkModelFlipWinding(NJS_CNK_MODEL* pModel);
void    CnkModelFlipStripWinding(NJS_CNK_MODEL* pModel, int idxStrip, int idxTri);

/*
*   Chunk Material Params
*/
/** Use '-1' to set all materials within the strip data **/
void    CnkMaterialFlagOn(Sint16* pPList, int idxMat, uint32 flag);
void    CnkMaterialFlagOff(Sint16* pPList, int idxMat, uint32 flag);

void    CnkModelMaterialFlagOn(NJS_CNK_MODEL* pModel, int idxMat, uint32 flag);
void    CnkModelMaterialFlagOff(NJS_CNK_MODEL* pModel, int idxMat, uint32 flag);

/** Chunk Object Materials (Applies to all materials in all models) **/
void    CnkObjectMaterialFlagOn(NJS_CNK_OBJECT* pObject, uint32 flag);
void    CnkObjectMaterialFlagOff(NJS_CNK_OBJECT* pObject, uint32 flag);

/** Chunk LandTable Materials (Applies to all materials in all models) **/
void    CnkLandTableMaterialFlagOn(OBJ_LANDTABLE* pLand, uint32 flag);
void    CnkLandTableMaterialFlagOff(OBJ_LANDTABLE* pLand, uint32 flag);

/** Use '-1' for params you don't wish to change, 
    those values won't be applied at all to the model **/
void    CnkMaterialDiffuse(Sint16* pPList, int idxMat, int a, int r, int g, int b);
void    CnkMaterialAmbient(Sint16* pPList, int idxMat, int a, int r, int g, int b); // MIA
void    CnkMaterialSpecular(Sint16* pPList, int idxMat, int i, int r, int g, int b);// MIA

void    CnkModelMaterialDiffuse(NJS_CNK_MODEL* pModel, int idxMat, int a, int r, int g, int b);
void    CnkModelMaterialAmbient(NJS_CNK_MODEL* pModel, int idxMat, int a, int r, int g, int b); // MIA
void    CnkModelMaterialSpecular(NJS_CNK_MODEL* pModel, int idxMat, int i, int r, int g, int b);// MIA

/*
*   GVM Tables
*/
typedef struct gvmtable TEX_GVMTABLE;

void	SwapGVMTableIndex(TEX_GVMTABLE* pGvmTable, int idx1, int idx2);

/*
*   Mod Tools
*/
void    __ModNonFatalFuncError(const char* func, const char* body);
void	ModConflictWarning(const char* body);

#define ModNonFatalFuncError(body) __ModNonFatalFuncError(__func__, body)

/*
*   Raw Pointer (ptr) Variants
* 
*   because C++ is too good for uint->ptr conversions >:(
*/
#ifdef __cplusplus

/** Chunk Tri Strip Winding **/
inline void
CnkModelFlipWinding(ptr pModel)
{
    return CnkModelFlipWinding((NJS_CNK_MODEL*)pModel);
}

inline void
CnkModelFlipStripWinding(ptr pModel, int idxStrip, int idxTri)
{
    return CnkModelFlipStripWinding((NJS_CNK_MODEL*)pModel, idxStrip, idxTri);
}

/** Chunk Material Params **/
inline void
CnkMaterialFlagOn(ptr pPList, int idxStrip, uint32 flag)
{
    return CnkMaterialFlagOn((Sint16*)pPList, idxStrip, flag);
}

inline void
CnkMaterialFlagOff(ptr pPList, int idxStrip, uint32 flag)
{
    return CnkMaterialFlagOff((Sint16*)pPList, idxStrip, flag);
}

inline void
CnkModelMaterialFlagOn(ptr pModel, int idxStrip, uint32 flag)
{
    return CnkModelMaterialFlagOn((NJS_CNK_MODEL*)pModel, idxStrip, flag);
}

inline void
CnkModelMaterialFlagOff(ptr pModel, int idxStrip, uint32 flag)
{
    return CnkModelMaterialFlagOff((NJS_CNK_MODEL*)pModel, idxStrip, flag);
}

inline void 
CnkObjectMaterialFlagOn(ptr pObject, uint32 flag)
{
    return CnkObjectMaterialFlagOn((NJS_CNK_OBJECT*)pObject, flag);
}

inline void
CnkObjectMaterialFlagOff(ptr pObject, uint32 flag)
{
    return CnkObjectMaterialFlagOff((NJS_CNK_OBJECT*)pObject, flag);
}

inline void
CnkMaterialDiffuse(ptr pPList, int idxMat, int a, int r, int g, int b)
{
    return CnkMaterialDiffuse((Sint16*)pPList, idxMat, a, r, g, b);
}

inline void 
CnkModelMaterialDiffuse(ptr pModel, int idxMat, int a, int r, int g, int b)
{
    return CnkModelMaterialDiffuse((NJS_CNK_MODEL*)pModel, idxMat, a, r, g, b);
}

/** GVM Tables **/
inline void
SwapGVMTableIndex(ptr pGvmTable, int idx1, int idx2)
{
    return SwapGVMTableIndex((TEX_GVMTABLE*)pGvmTable, idx1, idx2);
}

#endif /* __cplusplus */