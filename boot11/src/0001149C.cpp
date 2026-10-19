#pragma arm
#include "types.h"

// Sets the four low bits of the CP15 control register; returns their previous value.
u32 FUN_0001149C()
{
    register u32 control __asm("cp15:0:c1:c0:0");
    u32 v = control;
    u32 old = v & 0xF;
    control = v | 0xF;
    return old;
}
