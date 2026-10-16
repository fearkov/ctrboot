// Built with the instruction scheduler off (#pragma O1): the dump issues the
// and/lsr pair back to back and the bic after it, which the ARM11 scheduler of
// -O3 -Otime avoids (it separates the shifter operand's producer with the bic).
#pragma arm
#pragma O1
#include "types.h"

u32 FUN_0001140C()
{
    register u32 control __asm("cp15:0:c1:c0:0");
    u32 v = control;
    u32 old = (v & 0x1000) >> 12;
    control = v & ~0x1000u;
    return old;
}
