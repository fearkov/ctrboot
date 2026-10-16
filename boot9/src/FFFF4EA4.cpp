#include "types.h"

extern "C" volatile u16 *FUN_FFFF4FD4(u32 unit, u32 offset);

// Sets bit 8 of the register at 0x24 of a controller block.
void FUN_FFFF4EA4(u32 unit)
{
    volatile u16 *reg = FUN_FFFF4FD4(unit, 0x24);
    *reg |= 0x100;
}
