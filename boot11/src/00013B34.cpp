#include "types.h"

extern volatile u16 DAT_10146000;

u32 FUN_00013B34(void)
{
    u32 keys = ~DAT_10146000 & 0xFFF;
    return keys & ~((keys & 0x40) << 1) & ~((keys & 0x20) >> 1);
}
