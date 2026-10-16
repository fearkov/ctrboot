#include "types.h"

extern "C" volatile u16 *FUN_FFFF4FD4(u32 unit, u32 offset);

void FUN_FFFF487A(u32 unit)
{
    *FUN_FFFF4FD4(unit, 0x24) &= ~0x200;
}
