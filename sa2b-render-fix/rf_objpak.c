#include <samt/core.h>
#include <samt/file.h>
#include <samt/memory.h>

/** Render Fix **/
#include <rf_core.h>
#include <rf_config.h>

/** Self **/
#include <rf_objpak.h>

/** Macro **/
#define ToFlt(val) (*(float*)(&val))

/** Game Data **/
#define struc_36Instance    DATA_REF(char*, 0x01A557BC)

/** Constants **/
#define TINT_VALUE          (1.f)
#define SHADOW_INTENSITY    (80.f * (1.f / 256.f)) // rjSetCheapShadowMode(80);

/** Source **/
void
RF_ObjPakInit(void)
{
    if ( false )
    {
        size_t fsize;
        byte* const fbuf = mtFileLoad("./resource/Shader/win32/obj.pak", &fsize);

        if (!fbuf)
            return;

        if (fsize != 0x57BD)
        {
            OutputString("Render Fix: obj.pak is not original, aborting changes!");
            mtMemFree(fbuf);
            return;
        }

        bool changed = false;

        if (ToFlt(fbuf[0x07D9]) != TINT_VALUE)
        {
            changed = true;

            ToFlt(fbuf[0x07D9]) = TINT_VALUE;
            ToFlt(fbuf[0x0E21]) = TINT_VALUE;
            ToFlt(fbuf[0x11ED]) = TINT_VALUE;
            ToFlt(fbuf[0x15B5]) = TINT_VALUE;
            ToFlt(fbuf[0x1961]) = TINT_VALUE;
            ToFlt(fbuf[0x1E4D]) = TINT_VALUE;
            ToFlt(fbuf[0x2399]) = TINT_VALUE;
            ToFlt(fbuf[0x2A5D]) = TINT_VALUE;
            ToFlt(fbuf[0x3145]) = TINT_VALUE;
        }

        if (ToFlt(fbuf[0x1949]) != SHADOW_INTENSITY)
        {
            changed = true;

            ToFlt(fbuf[0x1949]) = SHADOW_INTENSITY;
            ToFlt(fbuf[0x2385]) = SHADOW_INTENSITY;
            ToFlt(fbuf[0x2A2D]) = SHADOW_INTENSITY;
            ToFlt(fbuf[0x312D]) = SHADOW_INTENSITY;
        }

        if (!changed)
        {
            mtMemFree(fbuf);
            return;
        }

        OutputString("Render Fix: Writing to obj.pak...");

        /** Write changes to file **/
        {
            const size_t nbw = mtFileWriteEx("./resource/Shader/win32/obj.pak", fbuf, fsize);

            /** If some error occured **/
            if (!nbw)
            {
                mtMemFree(fbuf);
                return;
            }
        }

        mtMemFree(fbuf);

        *(struc_36Instance + 0x644) = 1; // Reload shaders
    }
}
