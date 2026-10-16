#include "types.h"

extern "C" u32 FUN_00013970(void);
extern "C" u32 FUN_00013932(u32 reg, u8* buffer, u32 count);

bool FUN_00013A90(u32 flag)
{
    u32 value;
    u32 reg;
    if (FUN_00013970()) {
        if (flag)
            value = 0x28;
        else
            value = 0x14;
        reg = 0x22;
    } else {
        if (flag)
            value = 0x20;
        else
            value = 0x10;
        reg = 0x20;
    }
    return FUN_00013932(reg, (u8*)&value, 1) != 0;
}
