#pragma arm
#include "types.h"

void FUN_FFFF01A4(void)
{
    register u32 wait_for_interrupt __asm("cp15:0:c7:c0:4");
    wait_for_interrupt = 0;
}
