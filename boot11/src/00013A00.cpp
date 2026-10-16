#include "types.h"

extern "C" bool FUN_0001391C(u32 reg, u8* buffer, u32 count);

bool FUN_00013A00(u8* low, u8* high)
{
    u8 buf[2];
    if (FUN_0001391C(0, buf, 2)) {
        *low = buf[0] & 0xF;
        *high = buf[1];
        return true;
    }
    return false;
}
