#include "types.h"

extern u32 DAT_1FFE8130[];

void FUN_00018C20(u32 a, u32 b, u32 c, u32 d)
{
    u32* p = DAT_1FFE8130;
    *p++ = a;
    *p++ = b;
    *p++ = c;
    *p = d;
}
