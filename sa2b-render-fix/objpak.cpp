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

    bool changed = false;

    if (ToFlt(buffer[0x07D9]) != tintvalue)
    {
        changed = true;

        ToFlt(buffer[0x07D9]) = tintvalue;
        ToFlt(buffer[0x0E21]) = tintvalue;
        ToFlt(buffer[0x11ED]) = tintvalue;
        ToFlt(buffer[0x15B5]) = tintvalue;
        ToFlt(buffer[0x1961]) = tintvalue;
        ToFlt(buffer[0x1E4D]) = tintvalue;
        ToFlt(buffer[0x2399]) = tintvalue;
        ToFlt(buffer[0x2A5D]) = tintvalue;
        ToFlt(buffer[0x3145]) = tintvalue;
    }

    if (shadowOpacity > 0.0f && ToFlt(buffer[0x1949]) != shadowOpacity)
    {
        changed = true;

        ToFlt(buffer[0x1949]) = shadowOpacity;
        ToFlt(buffer[0x2385]) = shadowOpacity;
        ToFlt(buffer[0x2A2D]) = shadowOpacity;
        ToFlt(buffer[0x312D]) = shadowOpacity;
    }

    if (!changed)
    {
        free(buffer);
        return 0;
    }

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