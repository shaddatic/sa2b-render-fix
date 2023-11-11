#include <sa2b/core.h>
#include <sa2b/config.h>
#include <sa2b/memtools.h>
#include <sa2b/model.h>

#include <sa2b/ninja/ninja.h>

#include <sa2b/src/set.h>

#define ReplaceObjectFunction(plist, idx, pfunc) ((OBJ_ITEMENTRY*)plist)[idx].fnExec = (task_exec)pfunc

#include <sa2b/src/object/o_light.h>

#include <tree-shadows.h>

static void
LightModRestore()
{
    ReplaceObjectFunction(0x0109E830, 58, ObjectLightSW);     // Light SW          (City Escape)
    ReplaceObjectFunction(0x0109E830, 69, ObjectTreeShadows); // ObjectTreeShadows (City Escape)
}

#define SECT "c_escape"

void
CityEscapeSettings(const config* conf)
{
    if (ConfigGetInt(conf, SECT, "lightmod", 1))
    {
        LightModRestore();
    }
}