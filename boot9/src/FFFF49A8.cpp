#include "types.h"

extern "C" volatile u16 *FUN_FFFF4FD4(u32 unit, u32 offset);

u16 FUN_FFFF49A8(u32 unit)
{
    return *FUN_FFFF4FD4(unit, 0x1c);
}
