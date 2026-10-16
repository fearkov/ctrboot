#include "types.h"

extern "C" volatile u16 *FUN_FFFF4FD4(u32 unit, u32 offset);

// Writes the two registers at 0x104 and 0x108 of a controller block.
void FUN_FFFF4E84(u32 unit, u16 first, u16 second)
{
    *FUN_FFFF4FD4(unit, 0x104) = first;
    *FUN_FFFF4FD4(unit, 0x108) = second;
}
