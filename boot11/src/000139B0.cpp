#include "types.h"

extern "C" u32 FUN_00013970();
extern "C" u32 FUN_0001391C(u32 reg, u8* buffer, u32 count);

u32 FUN_000139B0(u32* out)
{
    u8 value;
    if (FUN_00013970()) {
        if (FUN_0001391C(0xF, &value, 1)) {
            if (((value & 0x7F) >> 5) == 3)
                *out = 1;
            else
                *out = 0;
            return 1;
        }
    } else {
        if (FUN_0001391C(0xF, &value, 1)) {
            if (value & 0x40)
                *out = 1;
            else
                *out = 0;
            return 1;
        }
    }
    return 0;
}
