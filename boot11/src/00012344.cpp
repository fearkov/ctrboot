#include "types.h"

void FUN_00012344()
{
    s32 i;
    volatile u8* a = (volatile u8*)0x10140000;
    for (i = 0; i < 8; i++)
        a[i] = (i << 2) | 0x80;
    volatile u8* b = (volatile u8*)0x10140008;
    for (i = 0; i < 8; i++)
        b[i] = (i << 2) | 0x80;
}
