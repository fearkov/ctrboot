#include "types.h"

extern "C" volatile u16 *FUN_FFFF4FD4(u32 unit, u32 offset);

void FUN_FFFF4CA4(u32 unit, u16 *out)
{
    *out = *FUN_FFFF4FD4(unit, 0x24);
}
