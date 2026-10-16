// Built for space (#pragma Ospace): the dump releases the three spilled argument
// words by popping them into r1-r3 (pop {r1-r7, pc}), where -Otime gives
// add sp, #12 / pop {r4-r7, pc}.
#pragma Ospace
#include "types.h"

extern "C" u32 FUN_0001370C(u32 dev);
extern "C" u32 FUN_000136E0(u32 dev, u8 data);
extern "C" u32 FUN_000136B4(u32 dev, u8 data);
extern "C" void FUN_00013784(u32 dev);

u32 FUN_00013878(u32 dev, u8 reg, u8 value)
{
    u32 result = 0;
    for (s32 i = 0; i < 8; i++) {
        if (FUN_0001370C(dev) && FUN_000136E0(dev, reg) && FUN_000136B4(dev, value)) {
            result = 1;
            break;
        }
        FUN_00013784(dev);
    }
    return result;
}
