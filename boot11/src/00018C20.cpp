// Test: the dump returns with pop {r4, pc} (push {r4, lr}), the shape armcc
// gives leaf code built for space. -Otime would use push {r4} / bx lr.
#pragma Ospace
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
