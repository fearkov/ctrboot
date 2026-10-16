#include "types.h"

extern "C" volatile u16 *FUN_FFFF4FD4(u32 unit, u32 offset);

void FUN_FFFF490A(u32 unit, u16 value)
{
    *FUN_FFFF4FD4(unit, 8) |= 0x100;
    *FUN_FFFF4FD4(unit, 0xA) = value;
}
