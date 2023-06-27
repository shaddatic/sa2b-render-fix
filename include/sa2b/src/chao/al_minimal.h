#pragma once

typedef struct colliwk		colliwk;

#include <sa2b/src/motion.h>

enum EMinimalTypeBTL : sint32
{
	eMinimalTypeBTL_Pen = 0x0,		// Penguin
	eMinimalTypeBTL_Goma = 0x1,		// Seal
	eMinimalTypeBTL_Rako = 0x2,		// Otter
	eMinimalTypeBTL_Usa = 0x3,		// Rabbit
	eMinimalTypeBTL_Chit = 0x4,		// Cheetah
	eMinimalTypeBTL_Ino = 0x5,		// Warthog
	eMinimalTypeBTL_Kuma = 0x6,		// Bear
	eMinimalTypeBTL_Tora = 0x7,		// Tiger
	eMinimalTypeBTL_Gori = 0x8,		// Gorilla
	eMinimalTypeBTL_Kuja = 0x9,		// Peacock
	eMinimalTypeBTL_Oum = 0xA,		// Parrot
	eMinimalTypeBTL_Kon = 0xB,		// Condor
	eMinimalTypeBTL_Ska = 0xC,		// Skunk
	eMinimalTypeBTL_Shep = 0xD,		// Sheep
	eMinimalTypeBTL_Ara = 0xE,		// Raccoon
	eMinimalTypeBTL_Han = 0xF,		// Half Fish
	eMinimalTypeBTL_Bone = 0x10,	// Skeleton Dog
	eMinimalTypeBTL_Batman = 0x11,	// Batman
	eMinimalTypeBTL_Dra = 0x12,		// Dragon
	eMinimalTypeBTL_Uni = 0x13,		// Unicorn
	eMinimalTypeBTL_Phen = 0x14,	// Phoenix
	eMinimalType__end_BTL = 0x15,
};

enum : sint32
{
	FLICKY_GOMA = 0x0,	// Seal
	FLICKY_PENG = 0x1,	// Penguin
	FLICKY_RAKO = 0x2,	// Otter
	FLICKY_PEAC = 0x3,	// Peacock
	FLICKY_SWAL = 0x4,	// Swallow
	FLICKY_PARR = 0x5,	// Parrot
	FLICKY_DEER = 0x6,	// Deer
	FLICKY_BANY = 0x7,	// Bunny
	FLICKY_WARA = 0x8,	// Kangaroo
	FLICKY_GORI = 0x9,	// Gorilla
	FLICKY_LION = 0xA,	// Lion
	FLICKY_ELEP = 0xB,	// Elephant
	FLICKY_MOGU = 0xC,	// Mole
	FLICKY_KOAL = 0xD,	// Koala
	FLICKY_SKUN = 0xE,	// Skunk
	FLICKY_MAX = 0xF,
};

enum : sint32
{
	MINI_MTN_WAIT = 0x0,
	MINI_MTN_WALK = 0x1,
	MINI_MTN_HUG = 0x2,
	MINI_MTN_FLY = 0x3,
};

#define GET_MINIMAL_WORK(tp) ((MINIMAL_WORK*)tp->twp)

struct MINIMAL_WORK
{
	char mode;
	char smode;
	char id;
	char btimer;
	__int16 flag;
	__int16 wtimer;
	Angle3 ang;
	NJS_POINT3 pos;
	NJS_POINT3 scl;
	colliwk* cwp;
	float spd;
	sint32 RangeOutTimer;
	MOTION_CTRL MtnCtrl;
	MOTION_TABLE MtnTable[4];
	sint32 CaptureFlag;
};

FuncPtr(void, __cdecl, AL_CreateMinimalCreateManager, (), 0x00549490);