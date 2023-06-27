#include <sa2b/core.h>
#include <sa2b/memtools.h>

#include <sa2b/ninja/ninja.h>

#include <sa2b/src/task.h>
#include <sa2b/src/shadow.h>

#include <sa2b/src/texture.h>

struct xyyzzxsdwstr
{
	NJS_POINT3 pos;
	xssunit hit[6];
};

typedef struct enemywk
{
	MOTIONWK mwp;
	char spac[4];
	int unk3;
	char byte44;
	char byte45;
	char field_46;
	char field_47;
	__int16 field_48;
	__int16 field_4A;
	short flag;
	char f4E[6];
	float float54;
	NJS_POINT3 home;
	NJS_POINT3 vec0;
	char f64[24];
	NJS_VECTOR lightPos;
	float flt1;
	float field_98;
	char field_9C[32];
	NJS_POINT3 colli_center;
	float colli_top;
	float colli_radius;
	float colli_bottom;
	float cliff_height;
	float bound_side;
	float bound_floor;
	float bound_friction;
	float bound_ceiling;
	int bound_add_angle;
	float shadow_scl;
	float shadow_scl_ratio;
	xyyzzxsdwstr shadow;
	float buyoscale;
	int angx_spd;
	int angy_spd;
	char f1CC[8];
	int view_angle;
	float view_range;
	float hear_range;
	int field_1E0;
	char field_1E4[15];
	char field_1F3;
	char field_1F4[4];
	int field_1F8;
	NJS_CNK_OBJECT* pObject;
	char field_200[16];
}
ENEMYWK;

DataPtr(NJS_TEXLIST, texlist_basic_shadow, 0x00B56374);

extern NJS_CNK_MODEL model_basic_shadow[];

static void
DrawFakeShadow(NJS_POINT3* pPos, Angle3* pAng, float scl, float scl_ratio)
{
	Angle3 ang;
	float floor = GetShadowPos(pPos->x, pPos->y + 2.0f, pPos->z, &ang);

	if (floor == -1000000.0f)
		return;

	njSetTexture(texlist_basic_shadow);

	njPushMatrixEx();

	njTranslate(0, pPos->x, floor, pPos->z);
	njRotateZXY(0, ang.x, pAng->y, ang.z);
	njTranslate(0, 0.0f, 0.4f, 0.0f);
	njScale(0, scl, 1.0f, scl * scl_ratio);

	SaveControl3D();
	SaveConstantMaterial();

	OnControl3D(NJD_CONTROL_3D_CONSTANT_MATERIAL);
	SetConstantMaterial(0.5f, 1.0f, 1.0f, 1.0f);

	njCnkDrawModel(model_basic_shadow);

	LoadControl3D();
	LoadConstantMaterial();

	njPopMatrixEx();
}

static void
DrawEnemyShadow(ENEMYWK* ewp, TASKWK* twp)
{
	DrawFakeShadow(&twp->pos, &twp->ang, ewp->shadow_scl, ewp->shadow_scl_ratio);
}

static void
DrawEnemyShadowHalf(ENEMYWK* ewp, TASKWK* twp)
{
	DrawFakeShadow(&twp->pos, &twp->ang, ewp->shadow_scl * 0.5f, ewp->shadow_scl_ratio);
}

__declspec(naked)
static void
__DrawEnemyShadow()
{
	__asm
	{
		push edx
		push eax
		call DrawEnemyShadow
		pop eax
		pop edx
		retn
	}
}

__declspec(naked)
static void
__DrawEnemyShadowHalf()
{
	__asm
	{
		push edx
		push eax
		call DrawEnemyShadowHalf
		pop eax
		pop edx
		retn
	}
}

int DoLighting_p = 0x00487060;

__declspec(naked)
static void
__DrawEnemyShadowKumi()
{
	__asm
	{
		push eax
		push esi
		push edi
		call DrawEnemyShadowHalf
		pop edi
		pop esi
		pop eax
		jmp DoLighting_p
	}
}

static void
DrawEnemyShadowShouku(TASKWK* twp)
{
	DrawFakeShadow(&twp->pos, &twp->ang, 50.0f, 0.75f);
}

__declspec(naked)
static void
__DrawEnemyShadowShouku()
{
	__asm
	{
		push ebp
		call DrawEnemyShadowShouku
		add esp, 4
		retn
	}
}

static void
DrawEnemyShadowNamieRocket(ENEMYWK* ewp, TASKWK* twp)
{
	DrawFakeShadow(&twp->pos, &twp->ang, ewp->shadow_scl, ewp->shadow_scl_ratio);
	njSetTexture((NJS_TEXLIST*)0x014D1598);
}

__declspec(naked)
static void
__DrawEnemyShadowNamieRocket()
{
	__asm
	{
		push edx
		push eax
		call DrawEnemyShadowNamieRocket
		pop eax
		pop edx
		retn
	}
}

static void
DrawEnemyShadowKyoko(TASKWK* twp)
{
	DrawFakeShadow(&twp->pos, &twp->ang, 16.0f, 1.25f);
}

__declspec(naked)
static void
__DrawEnemyShadowKyoko()
{
	__asm
	{
		push ebx
		call DrawEnemyShadowKyoko
		pop ebx
		retn
	}
}

void
EnemyShadowEnable()
{
	WriteJump(0x004799E0, __DrawEnemyShadow);

	WriteCall(0x005011EC, __DrawEnemyShadowKumi);

	WriteCall(0x00506481, __DrawEnemyShadowHalf); // E_Gold
	WriteCall(0x007A219E, __DrawEnemyShadowHalf); // E_Beeton
	WriteCall(0x004F8F6B, __DrawEnemyShadowHalf); // E_Namie

	WriteNoOP(0x004F9E7E, 0x004F9ED1);
	WriteCall(0x004F9E7E, __DrawEnemyShadowShouku);

	WriteCall(0x004F75E2, __DrawEnemyShadowNamieRocket);

	WriteNoOP(0x004FC47E, 0x004FC6B4);
	WriteNoOP(0x004FC6B6, 0x004FC6BF);
	WriteCall(0x004FC47E, __DrawEnemyShadowKyoko);
}