#pragma arm
#include "types.h"

extern "C" void FUN_FFFF09C4(u32 value);

// Zeroes the data cache's data RAM, every word of each segment (FUN_FFFF09C4 with 0).
void FUN_FFFF1E9C()
{
    FUN_FFFF09C4(0);
}
