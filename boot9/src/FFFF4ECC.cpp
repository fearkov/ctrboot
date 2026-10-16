#include "types.h"

extern "C" volatile u16 *FUN_FFFF4FD4(u32 unit, u32 offset);

void FUN_FFFF4ECC(u32 unit, u16 value)
{
    *FUN_FFFF4FD4(unit, 0x24) = value;
}
