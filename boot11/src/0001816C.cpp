#pragma arm
#include "types.h"

// Busy wait: spins until the count, taken down by 4 on every pass, wraps around.
void FUN_0001816C(u32 count)
{
    count -= 4;
    do {
        count -= 4;
    } while (count < 0xFFFFFFFCu);
}
