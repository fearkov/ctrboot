#include "types.h"

extern "C" volatile u16 *FUN_FFFF4FD4(u32 unit, u32 offset);

void FUN_FFFF489E(u32 unit)
{
    *FUN_FFFF4FD4(unit, 0x100) &= ~0x1000;
}
