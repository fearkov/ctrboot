#pragma arm
#include "types.h"

// Busy wait: counts down in steps of five until the subtraction wraps.
void FUN_00011A38(u32 count)
{
    do {
        count -= 5;
    } while (count < 0xFFFFFFFBu);
}
