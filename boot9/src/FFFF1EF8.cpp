#pragma arm
#include "types.h"

extern "C" void FUN_FFFF0994(u32 value);

// Zeroes the tag of every data cache line, which invalidates them all (FUN_FFFF0994 with 0).
void FUN_FFFF1EF8()
{
    FUN_FFFF0994(0);
}
