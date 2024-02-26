#include <sa2b/core.h>
#include <sa2b/user.h>
#include <sa2b/memory.h>

/** Ninja **/
#include <sa2b/ninja/ninja.h>

/** Source **/
#include <sa2b/src/texture.h>
#include <sa2b/src/landtable.h>

/** Std **/
#include <stdio.h>

/** Self **/
#include <rf_core.h>
#include <rf_mdlutil.h>

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

void
RF_CnkTintFix(Sint16* pPList)
{
    Sint16* plist = pPList;
    int type;

    while (1)
    {
        while (1)
        {
            while (1)
            {
                while (1)
                {
                    while (1)
                    {
                        while (1)
                        {
                            type = ((u8*)plist)[0];

                            if (type >= NJD_BITSOFF)
                                break;

                            ++plist;
                        }

                        if (type >= NJD_TINYOFF)
                            break;

                        ++plist;
                    }

                    if (type >= NJD_MATOFF)
                        break;

                    plist += 2;
                }

                if (type >= NJD_VERTOFF)
                    break;

                plist += 2;

                switch (type) {
                case NJD_CM_D:
                    TintCheckAndFix(plist);
                case NJD_CM_A:
                case NJD_CM_S:
                    plist += 2;
                    break;
                case NJD_CM_DA:
                case NJD_CM_DS:
                    TintCheckAndFix(plist);
                case NJD_CM_AS:
                    plist += 4;
                    break;
                case NJD_CM_DAS:
                    TintCheckAndFix(plist);
                    plist += 6;
                    break;
                }
            }

            if (type >= NJD_STRIPOFF)
                break;
        }

        if (type == NJD_ENDOFF)
            break;

        plist += ((u16*)plist)[1] + 2;
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

#define plist (*ppPList)
#define idxTri (*pIdxTri)

static void
FlipTriStrip(Sint16** ppPList, int* pIdxTri)
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

#undef plist
#undef idxTri

void
RF_CnkModelFlipStripWinding(NJS_CNK_MODEL* pModel, int idxStrip, int idxTri)
{
    int16_t* plist = pModel->plist;
    int type;

    while (1)
    {
        while (1)
        {
            while (1)
            {
                while (1)
                {
                    while (1)
                    {
                        while (1)
                        {
                            type = ((u8*)plist)[0];

                            if (type >= NJD_BITSOFF)
                                break;

                            ++plist;
                        }

                        if (type >= NJD_TINYOFF)
                            break;

                        ++plist;
                    }

                    if (type >= NJD_MATOFF)
                        break;

                    plist += 2;
                }

                if (type >= NJD_VERTOFF)
                    break;

                plist += 2;

                switch (type) {
                case NJD_CM_D:
                case NJD_CM_A:
                case NJD_CM_S:
                    plist += 2;
                    break;
                case NJD_CM_DA:
                case NJD_CM_DS:
                case NJD_CM_AS:
                    plist += 4;
                    break;
                case NJD_CM_DAS:
                    plist += 6;
                    break;
                }
            }

            if (type >= NJD_STRIPOFF)
                break;
        }

        if (type == NJD_ENDOFF)
            break;

        if (idxStrip < 0)
        {
            int tmp = -1;
            FlipTriStrip(&plist, &tmp);
        }
        else if (idxStrip-- == 0)
        {
            FlipTriStrip(&plist, &idxTri);
            return;
        }
        else
        {
            plist += ((u16*)plist)[1] + 2;
        }
    }
}

#pragma endregion

/*
*   Strip Flags
*/
#pragma region cnk_stripflag_on

void
RF_CnkMaterialFlagOn(Sint16* pPList, int idxMat, uint32_t flag)
{
    Sint16* plist = pPList;
    int type;

    while (1)
    {
        while (1)
        {
            while (1)
            {
                while (1)
                {
                    while (1)
                    {
                        while (1)
                        {
                            type = ((u8*)plist)[0];

                            if (type >= NJD_BITSOFF)
                                break;

                            ++plist;
                        }

                        if (type >= NJD_TINYOFF)
                            break;

                        ++plist;
                    }

                    if (type >= NJD_MATOFF)
                        break;

                    plist += 2;
                }

                if (type >= NJD_VERTOFF)
                    break;

                plist += 2;

                switch (type) {
                case NJD_CM_D:
                case NJD_CM_A:
                case NJD_CM_S:
                    plist += 2;
                    break;
                case NJD_CM_DA:
                case NJD_CM_DS:
                case NJD_CM_AS:
                    plist += 4;
                    break;
                case NJD_CM_DAS:
                    plist += 6;
                    break;
                }
            }

            if (type >= NJD_STRIPOFF)
                break;
        }

        if (type == NJD_ENDOFF)
            break;

        if (idxMat == -1)
        {
            ((u16*)plist)[0] |= flag;
        }
        else if (idxMat-- == 0)
        {
            ((u16*)plist)[0] |= flag;
            return;
        }

        plist += ((u16*)plist)[1] + 2;
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
    NJS_CNK_MODEL* models[32];

    MemSet(models, 0x00, sizeof(models));

    OBJ_LANDENTRY* plentry = pLand->pLandEntry;

    const s16 nb = pLand->ssCount;

    for (int i = 0; i < nb; ++i)
    {
        NJS_CNK_OBJECT* object = (NJS_CNK_OBJECT*)plentry->pObject;

        for (int j = 0; j < arylen(models); ++j)
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
    Sint16* plist = pPList;
    int type;

    while (1)
    {
        while (1)
        {
            while (1)
            {
                while (1)
                {
                    while (1)
                    {
                        while (1)
                        {
                            type = ((u8*)plist)[0];

                            if (type >= NJD_BITSOFF)
                                break;

                            ++plist;
                        }

                        if (type >= NJD_TINYOFF)
                            break;

                        ++plist;
                    }

                    if (type >= NJD_MATOFF)
                        break;

                    plist += 2;
                }

                if (type >= NJD_VERTOFF)
                    break;

                plist += 2;

                switch (type) {
                case NJD_CM_D:
                case NJD_CM_A:
                case NJD_CM_S:
                    plist += 2;
                    break;
                case NJD_CM_DA:
                case NJD_CM_DS:
                case NJD_CM_AS:
                    plist += 4;
                    break;
                case NJD_CM_DAS:
                    plist += 6;
                    break;
                }
            }

            if (type >= NJD_STRIPOFF)
                break;
        }

        if (type == NJD_ENDOFF)
            break;

        if (idxMat == -1)
        {
            ((u16*)plist)[0] &= ~flag;
        }
        else if (idxMat-- == 0)
        {
            ((u16*)plist)[0] &= ~flag;
            return;
        }

        plist += ((u16*)plist)[1] + 2;
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
    NJS_CNK_MODEL* models[32];

    MemSet(models, 0x00, sizeof(models));

    OBJ_LANDENTRY* plentry = pLand->pLandEntry;

    const s16 nb = pLand->ssCount;

    for (int i = 0; i < nb; ++i)
    {
        NJS_CNK_OBJECT* object = (NJS_CNK_OBJECT*)plentry->pObject;

        for (int j = 0; j < arylen(models); ++j)
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
        while (1)
        {
            while (1)
            {
                while (1)
                {
                    while (1)
                    {
                        while (1)
                        {
                            type = ((u8*)plist)[0];

                            if (type >= NJD_BITSOFF)
                                break;

                            ++plist;
                        }

                        if (type >= NJD_TINYOFF)
                            break;

                        ++plist;
                    }

                    if (type >= NJD_MATOFF)
                        break;

                    plist += 2;
                }

                if (type >= NJD_VERTOFF)
                    break;

                if (idxMat == -1)
                {
                    ((u16*)plist)[0] &= ~NJD_FBS_MASK;
                    ((u16*)plist)[0] |= src;
                }
                else if (idxMat-- == 0)
                {
                    ((u16*)plist)[0] &= ~NJD_FBS_MASK;
                    ((u16*)plist)[0] |= src;
                    return;
                }

                plist += 2;

                switch (type) {
                case NJD_CM_D:
                case NJD_CM_A:
                case NJD_CM_S:
                    plist += 2;
                    break;
                case NJD_CM_DA:
                case NJD_CM_DS:
                case NJD_CM_AS:
                    plist += 4;
                    break;
                case NJD_CM_DAS:
                    plist += 6;
                    break;
                }
            }

            if (type >= NJD_STRIPOFF)
                break;
        }

        if (type == NJD_ENDOFF)
            break;

        plist += ((u16*)plist)[1] + 2;
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
        while (1)
        {
            while (1)
            {
                while (1)
                {
                    while (1)
                    {
                        while (1)
                        {
                            type = ((u8*)plist)[0];

                            if (type >= NJD_BITSOFF)
                                break;

                            ++plist;
                        }

                        if (type >= NJD_TINYOFF)
                            break;

                        ++plist;
                    }

                    if (type >= NJD_MATOFF)
                        break;

                    plist += 2;
                }

                if (type >= NJD_VERTOFF)
                    break;

                if (idxMat == -1)
                {
                    ((u16*)plist)[0] &= ~NJD_FBD_MASK;
                    ((u16*)plist)[0] |= dst;
                }
                else if (idxMat-- == 0)
                {
                    ((u16*)plist)[0] &= ~NJD_FBD_MASK;
                    ((u16*)plist)[0] |= dst;
                    return;
                }

                plist += 2;

                switch (type) {
                case NJD_CM_D:
                case NJD_CM_A:
                case NJD_CM_S:
                    plist += 2;
                    break;
                case NJD_CM_DA:
                case NJD_CM_DS:
                case NJD_CM_AS:
                    plist += 4;
                    break;
                case NJD_CM_DAS:
                    plist += 6;
                    break;
                }
            }

            if (type >= NJD_STRIPOFF)
                break;
        }

        if (type == NJD_ENDOFF)
            break;

        plist += ((u16*)plist)[1] + 2;
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
        while (1)
        {
            while (1)
            {
                while (1)
                {
                    while (1)
                    {
                        while (1)
                        {
                            type = ((Uint8*)plist)[0];

                            if (type >= NJD_BITSOFF)
                                break;

                            ++plist;
                        }

                        if (type >= NJD_TINYOFF)
                            break;

                        ++plist;
                    }

                    if (type >= NJD_MATOFF)
                        break;

                    if (idxTID == -1)
                    {
                        plist[1] = (plist[1] & 0xE000) | (texID & 0x1FFF);
                    }
                    else if (idxTID-- == 0)
                    {
                        plist[1] = (plist[1] & 0xE000) | (texID & 0x1FFF);
                        return;
                    }

                    plist += 2;
                }

                if (type >= NJD_VERTOFF)
                    break;

                plist += 2;

                switch (type) {
                case NJD_CM_D:
                case NJD_CM_A:
                case NJD_CM_S:
                    plist += 2;
                    break;
                case NJD_CM_DA:
                case NJD_CM_DS:
                case NJD_CM_AS:
                    plist += 4;
                    break;
                case NJD_CM_DAS:
                    plist += 6;
                    break;
                }
            }

            if (type >= NJD_STRIPOFF)
                break;
        }

        if (type == NJD_ENDOFF)
            break;

        int stripsize = ((Uint16*)plist)[1];

        plist += stripsize + 2;
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

void
RF_CnkMaterialDiffuse(Sint16* pPList, int idxMat, int a, int r, int g, int b)
{
    Sint16* plist = pPList;
    int type;

    while (1)
    {
        while (1)
        {
            while (1)
            {
                while (1)
                {
                    while (1)
                    {
                        while (1)
                        {
                            type = ((u8*)plist)[0];

                            if (type >= NJD_BITSOFF)
                                break;

                            ++plist;
                        }

                        if (type >= NJD_TINYOFF)
                            break;

                        ++plist;
                    }

                    if (type >= NJD_MATOFF)
                        break;

                    plist += 2;
                }

                if (type >= NJD_VERTOFF)
                    break;

                plist += 2;

                switch (type) {
                case NJD_CM_D:
                    if (!idxMat)
                    {
                    SET_COLOR:

                        uint8_t* col = (u8*)plist;

                        if (a != -1)
                            col[3] = (u8)a;
                        if (r != -1)
                            col[2] = (u8)r;
                        if (g != -1)
                            col[1] = (u8)g;
                        if (b != -1)
                            col[0] = (u8)b;

                        return;
                    }

                    --idxMat;

                case NJD_CM_A:
                case NJD_CM_S:
                    plist += 2;
                    break;
                case NJD_CM_DA:
                case NJD_CM_DS:
                    if (!idxMat)
                        goto SET_COLOR;

                    --idxMat;

                case NJD_CM_AS:
                    plist += 4;
                    break;
                case NJD_CM_DAS:
                    if (!idxMat)
                        goto SET_COLOR;

                    --idxMat;

                    plist += 6;
                    break;
                }
            }

            if (type >= NJD_STRIPOFF)
                break;
        }

        if (type == NJD_ENDOFF)
            break;

        plist += ((u16*)plist)[1] + 2;
    }

    RF_DebugFuncError("'idxStrip' param is out of range!");
}

void
RF_CnkModelMaterialDiffuse(NJS_CNK_MODEL* pModel, int idxMat, int a, int r, int g, int b)
{
    RF_CnkMaterialDiffuse(pModel->plist, idxMat, a, r, g, b);
}

#pragma endregion
