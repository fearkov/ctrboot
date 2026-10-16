#include "types.h"

extern volatile u8 DAT_10161001;
extern volatile u8 DAT_10144001;

void FUN_00013768(u32 which, u32 flag)
{
    u8 v = (flag << 5) | 0xC1;
    volatile u8* p = (which == 0) ? &DAT_10161001 : &DAT_10144001;
    *p = v;
}
