#include "types.h"

extern "C" void FUN_FFFF36C8();
extern "C" void FUN_FFFF3698(u32 hold);

void FUN_FFFF3600(u32 addr, u32 size, u8 *out)
{
    u32 a = addr;
    FUN_FFFF36C8();
    FUN_FFFF3698(1);
    volatile u8 *data = (volatile u8 *)0x10160002;
    *data = 3;
    for (s32 i = 2; i >= 0; i--) {
        FUN_FFFF36C8();
        *data = ((u8 *)&a)[i];
    }
    FUN_FFFF36C8();
    u32 i;
    for (i = 0; i < size - 1; i++) {
        *data = 0;
        FUN_FFFF36C8();
        out[i] = *data;
    }
    FUN_FFFF3698(0);
    volatile u16 *cnt = (volatile u16 *)0x10160000;
    *data = 0;
    while (*cnt & 0x80) {}
    out[i] = *data;
}
