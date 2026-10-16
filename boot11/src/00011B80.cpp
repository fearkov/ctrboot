#pragma arm
#include "types.h"

u32 FUN_00011B80()
{
    register u32 control __asm("cp15:0:c1:c0:0");
    u32 v = control;
    v &= ~1u;
    control = v;
    return v;
}
