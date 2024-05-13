#include <sa2b/core.h>
#include <sa2b/file.h>
#include <sa2b/memory.h>

/** Render Fix **/
#include <rf_core.h>
#include <rf_config.h>

/** Self **/
#include <rf_objpak.h>

#define struc_36Instance    DataRef(char*, 0x01A557BC)

#define ToFlt(val) (*(float*)(&val))

static float ObjpShadowOpacity = -1.0f;
static int8_t ObjpRemoveTint = -1;

static bool ObjpWritePermission;

void
RF_ObjPakRegisterShadowOpacity(float opacity)
{
    ObjpShadowOpacity = 1.f - opacity;
}

void
RF_ObjPakRegisterTintFix(bool bRemoveTint)
{
    ObjpRemoveTint = bRemoveTint;
}

int
RF_ObjPakWriteChangesToFile(void)
{
    if (!ObjpWritePermission)
        return 0;

    size_t fsize;
    byte* const fbuf = uFileLoad("./resource/Shader/win32/obj.pak", &fsize);

    if (!fbuf)
        return 1;

    if (fsize != 0x57BD)
    {
        OutputString("Render Fix: obj.pak is not original, aborting changes!");
        MemFree(fbuf);
        return 1;
    }

    bool changed = false;

    if (ObjpRemoveTint != -1)
    {
        const float tintvalue = ObjpRemoveTint == 1 ? 1.0f : 0.909090936183929f;

        if (ToFlt(fbuf[0x07D9]) != tintvalue)
        {
            changed = true;

            ToFlt(fbuf[0x07D9]) = tintvalue;
            ToFlt(fbuf[0x0E21]) = tintvalue;
            ToFlt(fbuf[0x11ED]) = tintvalue;
            ToFlt(fbuf[0x15B5]) = tintvalue;
            ToFlt(fbuf[0x1961]) = tintvalue;
            ToFlt(fbuf[0x1E4D]) = tintvalue;
            ToFlt(fbuf[0x2399]) = tintvalue;
            ToFlt(fbuf[0x2A5D]) = tintvalue;
            ToFlt(fbuf[0x3145]) = tintvalue;
        }
    }

    if (ObjpShadowOpacity != -1.0f)
    {
        const float shd_opacity = ObjpShadowOpacity;

        if (ToFlt(fbuf[0x1949]) != shd_opacity)
        {
            changed = true;

            ToFlt(fbuf[0x1949]) = shd_opacity;
            ToFlt(fbuf[0x2385]) = shd_opacity;
            ToFlt(fbuf[0x2A2D]) = shd_opacity;
            ToFlt(fbuf[0x312D]) = shd_opacity;
        }
    }


    if (!changed)
    {
        MemFree(fbuf);
        return 0;
    }

    OutputString("Render Fix: Writing to obj.pak...");

    /** Write changes to file **/
    {
        const size_t nbw = uFileWriteEx("./resource/Shader/win32/obj.pak", fbuf, fsize);

        /** If some error occured **/
        if (!nbw)
        {
            MemFree(fbuf);
            return 1;
        }
    }

    MemFree(fbuf);

    *(struc_36Instance + 0x644) = 1; // Reload shaders

    ObjpRemoveTint = -1;
    ObjpShadowOpacity = -1.0f;

    return 0;
}

void
RF_ObjPakInit(void)
{
    ObjpWritePermission = RF_ConfigGetInt(CNF_DEBUG_OBJPAK_W) == 1;
}
