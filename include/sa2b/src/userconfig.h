#pragma once

struct UserConfig_vtable
{
	int sub_4025E0;
};

struct UserConfig
{
	UserConfig_vtable* vtable;
	int Fullscreen;
	int Width;
	int Height;
	int RefreshRate;
	int Language;
	int Display;
	int Res;
	int Analytics;
	int ConfigLoaded;		// Always 0, possibly an oversight
	int ControlsLoaded;		// Only 0 if failed to load
	int InputWay_P1;
	int InputWay_P2;
	int Vibrate_P1;
	int Vibrate_P2;
	char gap_38[447];
	char field_1FB;
};

DataRef(UserConfig*, gpUserConfig, 0x1AF19EC);