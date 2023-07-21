#include <sa2b/core.h>
#include <sa2b/memtools.h>

#include <sa2b/ninja/ninja.h>

FuncPtr(void, __cdecl, gjDiffuse, (NJS_BGRA color), 0x0042BA60);

static void
SetDefaultGinjaDiffuse()
{
	NJS_BGRA set = { 255, 255, 255, 255 };
	gjDiffuse(set);
}

static const
void* gjSetModelParams_p = (void*)0x0042BDB0;

static __declspec(naked) void
__SetDefaultGinjaDiffuse()
{
	__asm
	{
		push eax
		call SetDefaultGinjaDiffuse
		pop eax
		call gjSetModelParams_p
		retn
	}
}

void
DefaultGinjaDiffuseEnable()
{
	WriteCall(0x0042BF32, __SetDefaultGinjaDiffuse);
	WriteCall(0x0042BF72, __SetDefaultGinjaDiffuse);
}

static void
DisableTintGinjaMesh(GJS_MESHSET* pGinjaMesh, int nbMesh)
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
DisableTintGinjaModel(GJS_MODEL* pModel)
{
	if (pModel->nbSolid)
		DisableTintGinjaMesh(pModel->meshsolid, pModel->nbSolid);
	if (pModel->nbTrans)
		DisableTintGinjaMesh(pModel->meshtrans, pModel->nbTrans);
}

void
DisableTintGinjaObject(GJS_OBJECT* pObject)
{
	if (pObject->model)
		DisableTintGinjaModel(pObject->model);
	if (pObject->child)
		DisableTintGinjaObject(pObject->child);
	if (pObject->sibling)
		DisableTintGinjaObject(pObject->sibling);
}

static void
DisableTintChunkPList(sint16* pPList)
{
	sint16* plist = pPList;
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
							type = ((uint8*)plist)[0];

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
					plist[0] = (sint16)0xFFFF;
					plist[1] = (sint16)0xFFFF;
				case NJD_CM_A:
				case NJD_CM_S:
					plist += 2;
					break;
				case NJD_CM_DA:
				case NJD_CM_DS:
					plist[0] = (sint16)0xFFFF;
					plist[1] = (sint16)0xFFFF;
				case NJD_CM_AS:
					plist += 4;
					break;
				case NJD_CM_DAS:
					plist[0] = (sint16)0xFFFF;
					plist[1] = (sint16)0xFFFF;
					plist += 6;
					break;
				}
			}

			if (type >= NJD_STRIPOFF)
				break;
		}

		if (type == NJD_ENDOFF)
			break;

		plist += ((uint16*)plist)[1] + 2;
	}
}

void
DisableTintChunkModel(NJS_CNK_MODEL* pModel)
{
	if (pModel->plist)
		DisableTintChunkPList(pModel->plist);
}

void
DisableTintChunkObject(NJS_CNK_OBJECT* pObject)
{
	if (pObject->model)
		DisableTintChunkModel(pObject->model);
	if (pObject->child)
		DisableTintChunkObject(pObject->child);
	if (pObject->sibling)
		DisableTintChunkObject(pObject->sibling);
}

void
DisableTintGinjaObjectList(int* pList, int nbList)
{
	GJS_OBJECT** list = (GJS_OBJECT**)pList;

	for (int i = 0; i < nbList; ++i)
	{
		DisableTintGinjaObject(list[i]);
	}
}

void
DisableTintGinjaModelList(int* pList, int nbList)
{
	GJS_MODEL** list = (GJS_MODEL**)pList;

	for (int i = 0; i < nbList; ++i)
	{
		DisableTintGinjaModel(list[i]);
	}
}

void 
DisableTintChunkObjectList(int* pList, int nbList)
{
	NJS_CNK_OBJECT** list = (NJS_CNK_OBJECT**)pList;

	for (int i = 0; i < nbList; ++i)
	{
		DisableTintChunkObject(list[i]);
	}
}

void 
DisableTintChunkModelList(int* pList, int nbList)
{
	NJS_CNK_MODEL** list = (NJS_CNK_MODEL**)pList;

	for (int i = 0; i < nbList; ++i)
	{
		DisableTintChunkModel(list[i]);
	}
}

#include <sa2b/src/datadll.h>

typedef struct 
{
	char data0[4];
	NJS_CNK_OBJECT* pObject;
	NJS_CNK_OBJECT* pLODObject;
	NJS_TEXLIST* pTexlist;
	char data1[8];
	short shrt0;
}
SPECIAL_INFO;

void
DisableCartModelTints()
{
	SPECIAL_INFO* psi = GetDataDllAddr(SPECIAL_INFO, "specialInfo");

	if (!psi)
		return;

	for (int i = 0; i < 8; ++i)
	{
		if (psi[i].pObject)
			DisableTintChunkObject(psi[i].pObject);
		if (psi[i].pLODObject)
			DisableTintChunkObject(psi[i].pLODObject);
	}

    NJS_CNK_OBJECT* object_limo = GetDataDllAddr(NJS_CNK_OBJECT, "object_chara_limoall_limoall");
    DisableTintChunkObject(object_limo);
    object_limo = GetDataDllAddr(NJS_CNK_OBJECT, "object_tornado_3rd_tornado_3rd");
    DisableTintChunkObject(object_limo);
}