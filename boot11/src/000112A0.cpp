// Built with the instruction scheduler off (#pragma O1): the dump issues the
// and/lsr pair back to back and the bic after it, which the ARM11 scheduler of
// -O3 -Otime avoids (it separates the shifter operand's producer with the bic).
#pragma arm
#pragma O1
#include "types.h"

u32 FUN_000112A0()
{
    register u32 control __asm("cp15:0:c1:c0:0");
    u32 v = control;
    u32 old = (v & 4) >> 2;
    control = v & ~4u;
    return old;
}
