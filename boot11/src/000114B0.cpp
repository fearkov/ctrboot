#pragma arm
#include "types.h"

u32 FUN_000114B0()
{
    register u32 control __asm("cp15:0:c1:c0:0");
    u32 v = control;
    u32 old = v & 0xF;
    control = v & ~0xFu;
    return old;
}
