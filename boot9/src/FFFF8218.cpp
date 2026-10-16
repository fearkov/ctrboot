#pragma arm
#include "types.h"

// Busy-wait: spins until the count, taken down by 4 on every pass, runs out.
void FUN_FFFF8218(u32 count)
{
    count -= 4;
    do {
        count -= 4;
    } while (count < 0xFFFFFFFCu);
}
