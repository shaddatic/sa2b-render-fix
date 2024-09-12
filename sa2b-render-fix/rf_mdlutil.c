#include <sa2b/core.h>
#include <sa2b/user.h>
#include <sa2b/memory.h>

/** Ninja **/
#include <sa2b/ninja/ninja.h>

/** Source **/
#include <sa2b/sonic/texture.h>
#include <sa2b/sonic/landtable.h>

/** Std **/
#include <stdio.h>

/** Self **/
#include <rf_core.h>
#include <rf_mdlutil.h>

/*
*   Constants
*/
#define NJD_BITSOFF_MAX     (NJD_CB_DP+1)
#define NJD_TINYOFF_MAX     (NJD_CT_TID2+1)
#define NJD_MATOFF_MAX      (NJD_CM_DAS2+1)
#define NJD_STRIPOFF_MAX    (NJD_CS_UVH2+1)

/*
*   Tint Fixing
*/
#pragma region gjs_tintfix

static void
GjsMeshTintFix(GJS_MESHSET* pGinjaMesh, int nbMesh)
{
    while (nbMesh--)
    {
        GJS_MESHPARAM* param = pGinjaMesh->params;
        const int nbparam = pGinjaMesh->nbParam;

        for (int i = 0; i < nbparam; ++i)
        {
            if (param->type == GJD_MESH_DIFFUSE)
            {
                param->data = 0xFFFFFFFF;
                break;
            }
            ++param;
        }
        ++pGinjaMesh;
    }
}

void
RF_GjsModelTintFix(GJS_MODEL* pModel)
{
    if (pModel->nbSolid)
        GjsMeshTintFix(pModel->meshsolid, pModel->nbSolid);
    if (pModel->nbTrans)
        GjsMeshTintFix(pModel->meshtrans, pModel->nbTrans);
}

void
RF_GjsObjectTintFix(GJS_OBJECT* pObject)
{
    if (pObject->model)
        RF_GjsModelTintFix(pObject->model);
    if (pObject->child)
        RF_GjsObjectTintFix(pObject->child);
    if (pObject->sibling)
        RF_GjsObjectTintFix(pObject->sibling);
}

#pragma endregion
#pragma region cnk_tintfix

static void
TintCheckAndFix(Sint16* pDif)
{
    NJS_BGRA* col = (NJS_BGRA*)pDif;

    /** 0xB2 is the default parameter for diffuse. We have to check for this as
        non-tex materials had their diffuse values read unlike other mat types, where
        they then would change the diffuse values away from the default. Alpha is always read.
        A better solution is to check if the mat has a texture, so I did this instead. **/

    if (col->r == 0xB2 && col->g == 0xB2 && col->b == 0xB2)
    {
        col->r = 0xFF;
        col->g = 0xFF;
        col->b = 0xFF;
    }
}

static void
RF_CnkTintFix(Sint16* pPList)
{
    Sint16* plist = pPList;
    int type;

    while (1)
    {
        type = ((u8*)plist)[0];

        if (type == NJD_ENDOFF)
        {
            /** NJD_ENDOFF **/
            break;
        }

        if (type == NJD_NULLOFF)
        {
            /** NJD_NULLOFF **/

            /** Next offset **/
            ++plist;
            continue;
        }

        if (type < NJD_BITSOFF_MAX)
        {
            /** NJD_BITSOFF **/

            /** Next offset **/
            ++plist;
            continue;
        }

        if (type < NJD_TINYOFF_MAX)
        {
            /** NJD_TINYOFF **/

            /** Next offset **/
            plist += 2;
            continue;
        }

        if (type < NJD_MATOFF_MAX)
        {
            /** NJD_MATOFF **/

            switch (type) {
            case NJD_CM_D:
                TintCheckAndFix(&plist[2]);
            case NJD_CM_A:
            case NJD_CM_S:
                break;
            case NJD_CM_DA:
            case NJD_CM_DS:
                TintCheckAndFix(&plist[2]);
            case NJD_CM_AS:
                break;
            case NJD_CM_DAS:
                TintCheckAndFix(&plist[2]);
                break;
            }

            /** Next offset **/
            plist += ((u16*)plist)[1] + 2;
            continue;
        }

        if (type < NJD_STRIPOFF_MAX)
        {
            /** NJD_STRIPOFF **/

            /** Next offset **/
            plist += ((u16*)plist)[1] + 2;
            continue;
        }

        /** An error occured, stop **/
        break;
    }
}

void
RF_CnkModelTintFix(NJS_CNK_MODEL* pModel)
{
    if (pModel->plist)
        RF_CnkTintFix(pModel->plist);
}

void
RF_CnkObjectTintFix(NJS_CNK_OBJECT* pObject)
{
    if (pObject->model)
        RF_CnkModelTintFix(pObject->model);
    if (pObject->child)
        RF_CnkObjectTintFix(pObject->child);
    if (pObject->sibling)
        RF_CnkObjectTintFix(pObject->sibling);
}

#pragma endregion

/*
*   Triangle Strip Winding
*/
#pragma region cnk_triangle_winding

void
RF_CnkModelFlipWinding(NJS_CNK_MODEL* pModel)
{
    RF_CnkModelFlipStripWinding(pModel, -1, -1);
}

static void
FlipTriStrip(Sint16* plist, int idxTri)
{
    int nbstrip = plist[2] & 0x3FFF;

    plist += 3;

    while (nbstrip--)
    {
        int len = *plist;

        if (idxTri < 0)
        {
            *plist = -len;
        }
        else if (idxTri-- == 0)
        {
            *plist = -len;
            return;
        }

        ++plist;

        if (len < 0)
            len = -len;

        plist += len * 3;
    }
}

void
RF_CnkStripFlipStripWinding(Sint16* pPList, int idxStrip, int idxTri)
{
    Sint16* plist = pPList;
    int type;

    while (1)
    {
        type = ((u8*)plist)[0];

        if (type == NJD_ENDOFF)
        {
            /** NJD_ENDOFF **/
            break;
        }

        if (type == NJD_NULLOFF)
        {
            /** NJD_NULLOFF **/

            /** Next offset **/
            ++plist;
            continue;
        }

        if (type < NJD_BITSOFF_MAX)
        {
            /** NJD_BITSOFF **/

            /** Next offset **/
            ++plist;
            continue;
        }

        if (type < NJD_TINYOFF_MAX)
        {
            /** NJD_TINYOFF **/

            /** Next offset **/
            plist += 2;
            continue;
        }

        if (type < NJD_MATOFF_MAX)
        {
            /** NJD_MATOFF **/

            /** Next offset **/
            plist += ((u16*)plist)[1] + 2;
            continue;
        }

        if (type < NJD_STRIPOFF_MAX)
        {
            /** NJD_STRIPOFF **/

            if (idxStrip < 0)
            {
                FlipTriStrip(plist, -1);
            }
            else if (idxStrip-- == 0)
            {
                FlipTriStrip(plist, idxTri);
                return;
            }

            /** Next offset **/
            plist += ((u16*)plist)[1] + 2;
            continue;
        }

        /** An error occured, stop **/
        break;
    }
}

void
RF_CnkModelFlipStripWinding(NJS_CNK_MODEL* pModel, int idxStrip, int idxTri)
{
    RF_CnkStripFlipStripWinding(pModel->plist, idxStrip, idxTri);
}

#pragma endregion

/*
*   Strip Flags
*/
#pragma region cnk_stripflag_on

void
RF_CnkMaterialFlagOn(Sint16* pPList, int idxMat, uint32_t flag)
{
    const Sint16* plist = pPList;
    int type;

    while (1)
    {
        type = ((u8*)plist)[0];

        if (type == NJD_NULLOFF) // Null Offset
        {
            /** NJD_NULLOFF **/

            /** Next offset **/
            ++plist;
            continue;
        }

        if (type < NJD_BITSOFF_MAX)
        {
            /** NJD_BITSOFF **/

            /** Next offset **/
            ++plist;
            continue;
        }

        if (type < NJD_TINYOFF_MAX)
        {
            /** NJD_TINYOFF **/

            /** Next offset **/
            plist += 2;
            continue;
        }

        if (type < NJD_MATOFF_MAX)
        {
            /** NJD_MATOFF **/

            /** Next offset **/
            plist += ((u16*)plist)[1] + 2;
            continue;
        }

        if (type < NJD_STRIPOFF_MAX)
        {
            /** NJD_STRIPOFF **/
            if (idxMat == -1)
            {
                ((u16*)plist)[0] |= flag;
            }
            else if (idxMat-- == 0)
            {
                ((u16*)plist)[0] |= flag;
                return;
            }

            /** Next offset **/
            plist += ((u16*)plist)[1] + 2;
            continue;
        }

        /** NJD_ENDOFF **/
        break;
    }
}

void
RF_CnkModelMaterialFlagOn(NJS_CNK_MODEL* pModel, int idxMat, uint32_t flag)
{
    RF_CnkMaterialFlagOn(pModel->plist, idxMat, flag);
}

void
RF_CnkObjectMaterialFlagOn(NJS_CNK_OBJECT* pObject, uint32_t flag)
{
    if (pObject->model)
        RF_CnkModelMaterialFlagOn(pObject->model, -1, flag);
    if (pObject->child)
        RF_CnkObjectMaterialFlagOn(pObject->child, flag);
    if (pObject->sibling)
        RF_CnkObjectMaterialFlagOn(pObject->sibling, flag);
}

void
RF_CnkLandTableMaterialFlagOn(OBJ_LANDTABLE* pLand, uint32_t flag)
{
    NJS_CNK_MODEL* models[32] = { 0 };

    OBJ_LANDENTRY* plentry = pLand->pLandEntry;

    const s16 nb = pLand->ssCount;

    for (int i = 0; i < nb; ++i)
    {
        NJS_CNK_OBJECT* object = (NJS_CNK_OBJECT*)plentry->pObject;

        for (int j = 0; j < ARYLEN(models); ++j)
        {
            if (models[j] == NULL)
            {
                models[j] = object->model;
                RF_CnkModelMaterialFlagOn(object->model, -1, flag);
                goto LOOP;
            }

            if (models[j] == object->model)
                goto LOOP;
        }

        RF_CnkModelMaterialFlagOn(object->model, -1, flag); // Backup in case 'models' is full

    LOOP:

        ++plentry;
    }
}

#pragma endregion
#pragma region cnk_stripflag_off

void
RF_CnkMaterialFlagOff(Sint16* pPList, int idxMat, uint32_t flag)
{
    const Sint16* plist = pPList;
    int type;

    while (1)
    {
        type = ((u8*)plist)[0];

        if (type == NJD_NULLOFF) // Null Offset
        {
            /** NJD_NULLOFF **/

            /** Next offset **/
            ++plist;
            continue;
        }

        if (type < NJD_BITSOFF_MAX)
        {
            /** NJD_BITSOFF **/

            /** Next offset **/
            ++plist;
            continue;
        }

        if (type < NJD_TINYOFF_MAX)
        {
            /** NJD_TINYOFF **/

            /** Next offset **/
            plist += 2;
            continue;
        }

        if (type < NJD_MATOFF_MAX)
        {
            /** NJD_MATOFF **/

            /** Next offset **/
            plist += ((u16*)plist)[1] + 2;
            continue;
        }

        if (type < NJD_STRIPOFF_MAX)
        {
            /** NJD_STRIPOFF **/
            if (idxMat == -1)
            {
                ((u16*)plist)[0] &= ~flag;
            }
            else if (idxMat-- == 0)
            {
                ((u16*)plist)[0] &= ~flag;
                return;
            }

            /** Next offset **/
            plist += ((u16*)plist)[1] + 2;
            continue;
        }

        /** NJD_ENDOFF **/
        break;
    }
}

void
RF_CnkModelMaterialFlagOff(NJS_CNK_MODEL* pModel, int idxMat, uint32_t flag)
{
    RF_CnkMaterialFlagOff(pModel->plist, idxMat, flag);
}

void
RF_CnkObjectMaterialFlagOff(NJS_CNK_OBJECT* pObject, uint32_t flag)
{
    if (pObject->model)
        RF_CnkModelMaterialFlagOff(pObject->model, -1, flag);
    if (pObject->child)
        RF_CnkObjectMaterialFlagOff(pObject->child, flag);
    if (pObject->sibling)
        RF_CnkObjectMaterialFlagOff(pObject->sibling, flag);
}

void
RF_CnkLandTableMaterialFlagOff(OBJ_LANDTABLE* pLand, uint32_t flag)
{
    NJS_CNK_MODEL* models[32] = { 0 };

    OBJ_LANDENTRY* plentry = pLand->pLandEntry;

    const s16 nb = pLand->ssCount;

    for (int i = 0; i < nb; ++i)
    {
        NJS_CNK_OBJECT* object = (NJS_CNK_OBJECT*)plentry->pObject;

        for (int j = 0; j < ARYLEN(models); ++j)
        {
            if (models[j] == NULL)
            {
                models[j] = object->model;
                RF_CnkModelMaterialFlagOff(object->model, -1, NJD_FST_DB);
                goto LOOP;
            }

            if (models[j] == object->model)
                goto LOOP;
        }

        RF_CnkModelMaterialFlagOff(object->model, -1, NJD_FST_DB); // Backup in case 'models' is full

    LOOP:

        ++plentry;
    }
}

#pragma endregion

#pragma region cnk_blending

void
RF_CnkBlendingSrc(Sint16* pPList, int idxMat, uint16_t src)
{
    Sint16* plist = pPList;
    int type;

    while (1)
    {
        type = ((u8*)plist)[0];

        if (type == NJD_ENDOFF)
        {
            /** NJD_ENDOFF **/
            break;
        }

        if (type == NJD_NULLOFF)
        {
            /** NJD_NULLOFF **/

            /** Next offset **/
            ++plist;
            continue;
        }

        if (type < NJD_BITSOFF_MAX)
        {
            /** NJD_BITSOFF **/

            /** Next offset **/
            ++plist;
            continue;
        }

        if (type < NJD_TINYOFF_MAX)
        {
            /** NJD_TINYOFF **/

            /** Next offset **/
            plist += 2;
            continue;
        }

        if (type < NJD_MATOFF_MAX)
        {
            /** NJD_MATOFF **/

            if (idxMat == -1)
            {
                ((u16*)plist)[0] = ( ((u16*)plist)[0] & ~NJD_FBS_MASK ) | src;
            }
            else if (idxMat-- == 0)
            {
                ((u16*)plist)[0] = ( ((u16*)plist)[0] & ~NJD_FBS_MASK ) | src;
                return;
            }

            /** Next offset **/
            plist += ((u16*)plist)[1] + 2;
            continue;
        }

        if (type < NJD_STRIPOFF_MAX)
        {
            /** NJD_STRIPOFF **/

            /** Next offset **/
            plist += ((u16*)plist)[1] + 2;
            continue;
        }

        /** An error occured, stop **/
        break;
    }
}

void
RF_CnkModelBlendingSrc(NJS_CNK_MODEL* pModel, int idxMat, uint16_t src)
{
    RF_CnkBlendingSrc(pModel->plist, idxMat, src);
}

void
RF_CnkObjectBlendingSrc(NJS_CNK_OBJECT* pObject, uint16_t src)
{
    if (pObject->model)
        RF_CnkModelBlendingSrc(pObject->model, -1, src);
    if (pObject->child)
        RF_CnkObjectBlendingSrc(pObject->child, src);
    if (pObject->sibling)
        RF_CnkObjectBlendingSrc(pObject->sibling, src);
}

void
RF_CnkBlendingDst(Sint16* pPList, int idxMat, uint16_t dst)
{
    Sint16* plist = pPList;
    int type;

    while (1)
    {
        type = ((u8*)plist)[0];

        if (type == NJD_ENDOFF)
        {
            /** NJD_ENDOFF **/
            break;
        }

        if (type == NJD_NULLOFF)
        {
            /** NJD_NULLOFF **/

            /** Next offset **/
            ++plist;
            continue;
        }

        if (type < NJD_BITSOFF_MAX)
        {
            /** NJD_BITSOFF **/

            /** Next offset **/
            ++plist;
            continue;
        }

        if (type < NJD_TINYOFF_MAX)
        {
            /** NJD_TINYOFF **/

            /** Next offset **/
            plist += 2;
            continue;
        }

        if (type < NJD_MATOFF_MAX)
        {
            /** NJD_MATOFF **/

            if (idxMat == -1)
            {
                ((u16*)plist)[0] = ( ((u16*)plist)[0] & ~NJD_FBD_MASK ) | dst;
            }
            else if (idxMat-- == 0)
            {
                ((u16*)plist)[0] = ( ((u16*)plist)[0] & ~NJD_FBD_MASK ) | dst;
                return;
            }

            /** Next offset **/
            plist += ((u16*)plist)[1] + 2;
            continue;
        }

        if (type < NJD_STRIPOFF_MAX)
        {
            /** NJD_STRIPOFF **/

            /** Next offset **/
            plist += ((u16*)plist)[1] + 2;
            continue;
        }

        /** An error occured, stop **/
        break;
    }
}

void
RF_CnkModelBlendingDst(NJS_CNK_MODEL* pModel, int idxMat, uint16_t dst)
{
    RF_CnkBlendingDst(pModel->plist, idxMat, dst);
}

void
RF_CnkObjectBlendingDst(NJS_CNK_OBJECT* pObject, uint16_t dst)
{
    if (pObject->model)
        RF_CnkModelBlendingDst(pObject->model, -1, dst);
    if (pObject->child)
        RF_CnkObjectBlendingDst(pObject->child, dst);
    if (pObject->sibling)
        RF_CnkObjectBlendingDst(pObject->sibling, dst);
}

#pragma endregion

/*
*   Texture ID
*/
#pragma region cnk_texid
void
RF_CnkChangeTexID(Sint16* pPList, int idxTID, Sint16 texID)
{
    Sint16* plist = pPList;
    int type;

    while (1)
    {
        type = ((u8*)plist)[0];

        if (type == NJD_ENDOFF)
        {
            /** NJD_ENDOFF **/
            break;
        }

        if (type == NJD_NULLOFF)
        {
            /** NJD_NULLOFF **/

            /** Next offset **/
            ++plist;
            continue;
        }

        if (type < NJD_BITSOFF_MAX)
        {
            /** NJD_BITSOFF **/

            /** Next offset **/
            ++plist;
            continue;
        }

        if (type < NJD_TINYOFF_MAX)
        {
            /** NJD_TINYOFF **/

            if (idxTID == -1)
            {
                plist[1] = (plist[1] & 0xE000) | (texID & 0x1FFF);
            }
            else if (idxTID-- == 0)
            {
                plist[1] = (plist[1] & 0xE000) | (texID & 0x1FFF);
                return;
            }

            /** Next offset **/
            plist += 2;
            continue;
        }

        if (type < NJD_MATOFF_MAX)
        {
            /** NJD_MATOFF **/

            /** Next offset **/
            plist += ((u16*)plist)[1] + 2;
            continue;
        }

        if (type < NJD_STRIPOFF_MAX)
        {
            /** NJD_STRIPOFF **/

            /** Next offset **/
            plist += ((u16*)plist)[1] + 2;
            continue;
        }

        /** An error occured, stop **/
        break;
    }
}

void
RF_CnkModelChangeTexID(NJS_CNK_MODEL* pModel, int idxTID, Sint16 texID)
{
    RF_CnkChangeTexID(pModel->plist, idxTID, texID);
}

void
RF_CnkObjectChangeTexID(NJS_CNK_OBJECT* pObject, Sint16 texID)
{
    if (pObject->model)
        RF_CnkModelChangeTexID(pObject->model, -1, texID);
    if (pObject->child)
        RF_CnkObjectChangeTexID(pObject->child, texID);
    if (pObject->sibling)
        RF_CnkObjectChangeTexID(pObject->sibling, texID);
}

#pragma endregion

/*
*   Material Params
*/
#pragma region cnk_material_param

static void
SetDiffuse(Sint16* plist, int a, int r, int g, int b)
{
    uint8_t* const col = (u8*)&plist[2];

    if (a != -1) col[3] = (u8)a;
    if (r != -1) col[2] = (u8)r;
    if (g != -1) col[1] = (u8)g;
    if (b != -1) col[0] = (u8)b;
}

void
RF_CnkMaterialDiffuse(Sint16* pPList, int idxMat, int a, int r, int g, int b)
{
    Sint16* plist = pPList;
    int type;

    while (1)
    {
        type = ((u8*)plist)[0];

        if (type == NJD_ENDOFF)
        {
            /** NJD_ENDOFF **/
            break;
        }

        if (type == NJD_NULLOFF)
        {
            /** NJD_NULLOFF **/

            /** Next offset **/
            ++plist;
            continue;
        }

        if (type < NJD_BITSOFF_MAX)
        {
            /** NJD_BITSOFF **/

            /** Next offset **/
            ++plist;
            continue;
        }

        if (type < NJD_TINYOFF_MAX)
        {
            /** NJD_TINYOFF **/

            /** Next offset **/
            plist += 2;
            continue;
        }

        if (type < NJD_MATOFF_MAX)
        {
            /** NJD_MATOFF **/

            switch (type) {
            case NJD_CM_D:

                if (idxMat < 0)
                {
                    SetDiffuse(plist, a, r, g, b);
                }
                else if (idxMat-- == 0)
                {
                    SetDiffuse(plist, a, r, g, b);
                    return;
                }

                break;

            case NJD_CM_DA:
            case NJD_CM_DS:

                if (idxMat < 0)
                {
                    SetDiffuse(plist, a, r, g, b);
                }
                else if (idxMat-- == 0)
                {
                    SetDiffuse(plist, a, r, g, b);
                    return;
                }

                break;

            case NJD_CM_DAS:

                if (idxMat < 0)
                {
                    SetDiffuse(plist, a, r, g, b);
                }
                else if (idxMat-- == 0)
                {
                    SetDiffuse(plist, a, r, g, b);
                    return;
                }

                break;
            }

            /** Next offset **/
            plist += ((u16*)plist)[1] + 2;
            continue;
        }

        if (type < NJD_STRIPOFF_MAX)
        {
            /** NJD_STRIPOFF **/

            /** Next offset **/
            plist += ((u16*)plist)[1] + 2;
            continue;
        }

        /** An error occured, stop **/
        break;
    }
}

void
RF_CnkModelMaterialDiffuse(NJS_CNK_MODEL* pModel, int idxMat, int a, int r, int g, int b)
{
    RF_CnkMaterialDiffuse(pModel->plist, idxMat, a, r, g, b);
}

#pragma endregion
