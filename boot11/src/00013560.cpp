#include "types.h"

extern volatile u8 DAT_10161001;
extern volatile u8 DAT_10144001;

void FUN_00013560(u32 which, u32 value)
{
    u8 v = (value << 5) | (value << 4) | 0xC0;
    volatile u8* p = &DAT_10161001;
    if (which)
        p = &DAT_10144001;
    *p = v;
}
