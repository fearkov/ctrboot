#pragma arm
#include "types.h"

// Invalidates the whole instruction TLB.
void FUN_00011C54()
{
    register u32 invalidate __asm("cp15:0:c8:c5:0");
    invalidate = 0;
}
