#pragma arm
#include "types.h"

// Invalidates the whole data TLB.
void FUN_00011C60()
{
    register u32 invalidate __asm("cp15:0:c8:c6:0");
    invalidate = 0;
}
