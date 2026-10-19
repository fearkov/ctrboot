#include "types.h"

extern "C" u32 FUN_0001370C(u32 dev);
extern "C" u32 FUN_000136E0(u32 dev, u8 data);
extern "C" u32 FUN_000136B4(u32 dev, u8 data);
extern "C" void FUN_00013784(u32 dev);

u32 FUN_000138B8(u32 dev, u8 reg, const u8* data, u32 count)
{
    u32 result = 0;
    s32 i = 0;
    do {
        if (FUN_0001370C(dev) && FUN_000136E0(dev, reg)) {
            u32 j = 0;
            const u8* p = data;
            for (; j < count - 1; j++) {
                if (!FUN_000136E0(dev, *p++))
                    break;
            }
            if (j == count - 1 && FUN_000136B4(dev, *p)) {
                result = 1;
                break;
            }
        }
        FUN_00013784(dev);
        i++;
    } while (i < 8);
    return result;
}
