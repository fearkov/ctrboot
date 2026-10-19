#include "types.h"

extern "C" u32 FUN_0001370C(u32 dev);
extern "C" u32 FUN_000136E0(u32 dev, u8 data);
extern "C" u32 FUN_00013688(u32 dev);
extern "C" u8 FUN_00013858(u32 dev);
extern "C" u8 FUN_00013838(u32 dev);
extern "C" void FUN_00013784(u32 dev);

u32 FUN_00013626(u32 dev, u8 reg, u8* buffer, u32 count)
{
    u32 result = 0;
    for (s32 i = 0; i < 8; i++) {
        if (FUN_0001370C(dev) && FUN_000136E0(dev, reg) && FUN_00013688(dev)) {
            for (u32 j = 0; j < count - 1; j++)
                *buffer++ = FUN_00013858(dev);
            *buffer = FUN_00013838(dev);
            result = 1;
            break;
        }
        FUN_00013784(dev);
    }
    return result;
}
