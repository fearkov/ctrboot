#include "types.h"

extern "C" volatile u16 *FUN_FFFF4FD4(u32 unit, u32 offset);

void FUN_FFFF48D2(u32 unit, u16 bits)
{
    *FUN_FFFF4FD4(unit, 0x20) &= ~bits;
}
