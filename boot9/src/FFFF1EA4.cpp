#pragma arm
#include "types.h"

extern "C" void FUN_FFFF0BA0(u32 value);

// Zeroes the instruction cache's data RAM, every word of each way (FUN_FFFF0BA0 with 0).
void FUN_FFFF1EA4()
{
    FUN_FFFF0BA0(0);
}
