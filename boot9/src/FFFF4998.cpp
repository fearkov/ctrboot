#include "types.h"

extern "C" volatile u16 *FUN_FFFF4FD4(u32 unit, u32 offset);

u32 FUN_FFFF4998(u32 unit)
{
    u16 reg = *FUN_FFFF4FD4(unit, 2);
    return (reg & 0x7ff) >> 8;
}
