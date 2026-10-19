#pragma arm
#include "types.h"

// Invalidates the whole unified TLB.
void FUN_00011C48()
{
    register u32 invalidate __asm("cp15:0:c8:c7:0");
    invalidate = 0;
}
