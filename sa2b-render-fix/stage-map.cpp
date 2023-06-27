#include <sa2b/core.h>
#include <sa2b/config.h>
#include <sa2b/memtools.h>

#include <sa2b/ninja/ninja.h>

#include <sa2b/src/misc.h>

static void
DrawMapTextBackdrop()
{
	NJS_COLOR colors[4];
	NJS_POINT2 points[4];

	float screenratio = (ScreenRatioX / 640.0f / (ScreenRatioY / 480.0f) - 1.0f) * 320.0f;

	colors[0].color = 0x600000FF;
	colors[1].color = 0x600000FF;
	colors[2].color = 0x600000FF;
	colors[3].color = 0x600000FF;

	points[0].x = 0.0f - screenratio;
	points[0].y = 26.0f;

	points[1].x = 0.0f - screenratio;
	points[1].y = 58.0f;

	points[2].x = 640.0f + screenratio;
	points[2].y = 26.0f;

	points[3].x = 640.0f + screenratio;
	points[3].y = 58.0f;

	NJS_POINT2COL poly = { points, colors, 0, 4 };

	njDrawPolygon2D(&poly, 4, -1.0f, NJD_FILL | NJD_TRANSPARENT);
}

static void
DrawMapPurpleFill()
{
	NJS_COLOR colors[4];
	NJS_POINT2 points[4];

	float screenratio = (ScreenRatioX / 640.0f / (ScreenRatioY / 480.0f) - 1.0f) * 320.0f;

	colors[0].color = 0xFF210C29;
	colors[1].color = 0xFF210C29;
	colors[2].color = 0xFF210C29;
	colors[3].color = 0xFF210C29;

	points[0].x = 0.0f - screenratio;
	points[0].y = 0.0f;

	points[1].x = 0.0f - screenratio;
	points[1].y = 480.0f;

	points[2].x = 640.0f + screenratio;
	points[2].y = 0.0f;

	points[3].x = 640.0f + screenratio;
	points[3].y = 480.0f;

	NJS_POINT2COL poly = { points, colors, 0, 4 };

	njDrawPolygon2D(&poly, 4, -20000.0f, NJD_FILL);
}

const int SOCDisplaySprite_p = 0x0041DC80;

__declspec(naked)
static void
__DrawMapPurpleFill()
{
	__asm
	{
		push eax
		call DrawMapPurpleFill
		pop eax
		jmp SOCDisplaySprite_p
	}
}

void
StageMapTextBackdropRestore()
{
	WriteJump(0x00675D50, DrawMapTextBackdrop);
}

static const float posshift = -108.0f;

void
StageMapStretchFix()
{
	WritePointer(0x006763BB, &posshift);		/* Move icons left */
	WritePointer(0x00676046, 0x00907420);		/* stop stretch */
	WriteCall(0x00676080, __DrawMapPurpleFill); /* fill blank space */
}