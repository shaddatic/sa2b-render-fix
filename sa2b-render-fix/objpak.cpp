#define _CRT_SECURE_NO_WARNINGS

#include <sa2b/core.h>

#include <stdio.h>
#include <stdlib.h>

DataRef(char*, struc_36Instance, 0x01A557BC);

#define ToFlt(val) (*(float*)(&val))

int
EditObjPak(bool tintDisable, float shadowOpacity)
{
	FILE* f = fopen("./resource/Shader/win32/obj.pak", "rb");

	if (!f)
		return 1;

	fseek(f, 0, SEEK_END);

	size_t size = ftell(f);

	if (size != 0x57BD)
	{
		puts("Render Fix: obj.pak is not original, aborting changes!");
		fclose(f);
		return 1;
	}

	fseek(f, 0, SEEK_SET);

	char* buffer = (char*)malloc(size);

	/* If this fails, something really bad happened */
	if (!buffer)
	{
		fclose(f);
		return 1;
	}

	fread(buffer, size, 1, f);

	fclose(f);

	float tintvalue = tintDisable ? 1.0f : 0.909090936183929f;

	if (ToFlt(buffer[0x07D9]) == tintvalue)
	{
		free(buffer);
		return 0;
	}

	ToFlt(buffer[0x07D9]) = tintvalue;
	ToFlt(buffer[0x0E21]) = tintvalue;
	ToFlt(buffer[0x11ED]) = tintvalue;
	ToFlt(buffer[0x15B5]) = tintvalue;
	ToFlt(buffer[0x1961]) = tintvalue;
	ToFlt(buffer[0x1E4D]) = tintvalue;
	ToFlt(buffer[0x2399]) = tintvalue;
	ToFlt(buffer[0x2A5D]) = tintvalue;
	ToFlt(buffer[0x3145]) = tintvalue;

	puts("Render Fix: Writing to obj.pak...");

	f = fopen("./resource/Shader/win32/obj.pak", "wb");

	if (!f)
	{
		free(buffer);
		return 1;
	}

	fwrite(buffer, size, 1, f);

	fclose(f);

	free(buffer);

	*(struc_36Instance + 0x644) = 1; // Reload shaders

	return 0;
}