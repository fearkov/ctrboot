// Built at -O1, like FUN_00011A54: at -O3 armcc merges the three identical arms, and the schedule barrier
// keeps -O1 from moving the shared return up under the first arm.
#pragma arm
#pragma O1
#include "types.h"

// Writes a performance monitor counter and returns its old value: 1 is count register 0, 2 is count
// register 1, anything else is the cycle counter. The ROM reaches the cycle counter register in all three.
u32 FUN_00011A7C(int counter, u32 value)
{
    register u32 cycle __asm("cp15:0:c15:c12:1");
    register u32 count0 __asm("cp15:0:c15:c12:1");
    register u32 count1 __asm("cp15:0:c15:c12:1");
    u32 old;
    switch (counter) {
    default:
        old = cycle;
        cycle = value;
        break;
    case 1:
        old = count0;
        count0 = value;
        break;
    case 2:
        old = count1;
        count1 = value;
        break;
    }
    __schedule_barrier();
    return old;
}
