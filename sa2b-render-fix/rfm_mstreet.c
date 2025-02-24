#include <samt/core.h>
#include <samt/writemem.h>

#include <rf_core.h>
#include <rf_util.h>

void
RFM_MissionStreetInit(void)
{
    static const float PosOne = 1.0f;
    ReplaceFloat(0x005B5C3C, &PosOne);
}
