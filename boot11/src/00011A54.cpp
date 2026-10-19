// Built at -O1: at -O3 armcc turns the three reads into conditional mrc instructions. The schedule barrier
// before the return keeps -O1 from moving the shared return up under the first read.
#pragma arm
#pragma O1
#include "types.h"

// Reads a performance monitor counter: 1 is count register 0, 2 is count register 1, anything else is the
// cycle counter.
u32 FUN_00011A54(int counter)
{
    register u32 cycle __asm("cp15:0:c15:c12:1");
    register u32 count0 __asm("cp15:0:c15:c12:2");
    register u32 count1 __asm("cp15:0:c15:c12:3");
    u32 value;
    switch (counter) {
    default:
        value = cycle;
        break;
    case 1:
        value = count0;
        break;
    case 2:
        value = count1;
        break;
    }
    __schedule_barrier();
    return value;
}
