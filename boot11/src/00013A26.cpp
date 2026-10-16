#include "types.h"

extern "C" bool FUN_0001391C(u32 reg, u8* buffer, u32 count);

bool FUN_00013A26(u32* flag)
{
    u8 buf[1];
    if (FUN_0001391C(0xF, buf, 1)) {
        if (buf[0] & 0x80)
            *flag = 1;
        else
            *flag = 0;
        return true;
    }
    return false;
}
