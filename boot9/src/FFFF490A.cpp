// Matches only when built for space: with -Otime armcc gives the two arguments the other way
// round (value in r4, unit in r5). FUN_FFFF20CC is built the same way.
#pragma Ospace
#include "types.h"

extern "C" volatile u16 *FUN_FFFF4FD4(u32 unit, u32 offset);

void FUN_FFFF490A(u32 unit, u16 value)
{
    *FUN_FFFF4FD4(unit, 8) |= 0x100;
    *FUN_FFFF4FD4(unit, 0xA) = value;
}
