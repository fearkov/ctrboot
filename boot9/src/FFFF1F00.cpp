#pragma arm
#include "types.h"

extern "C" void FUN_FFFF0B70(u32 value);

// Zeroes the tag of every instruction cache line, which invalidates them all (FUN_FFFF0B70 with 0).
void FUN_FFFF1F00()
{
    FUN_FFFF0B70(0);
}
