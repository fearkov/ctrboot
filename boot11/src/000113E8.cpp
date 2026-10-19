#pragma arm
#include "types.h"

// Data memory barrier.
void FUN_000113E8()
{
    register u32 barrier __asm("cp15:0:c7:c10:5");
    barrier = 0;
}
