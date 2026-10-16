#include "types.h"

extern "C" volatile u16 *FUN_FFFF4FD4(u32 unit, u32 offset);

void FUN_FFFF493C(u32 unit)
{
    *FUN_FFFF4FD4(unit, 0x100) |= 0x800;
}
