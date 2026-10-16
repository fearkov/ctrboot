#pragma arm
#include "types.h"

u32 FUN_00011A18()
{
    register u32 mpidr __asm("cp15:0:c0:c0:5");
    return mpidr & 3;
}
