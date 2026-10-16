#include "types.h"

extern "C" volatile u16 *FUN_FFFF4FD4(u32 unit, u32 offset);

void FUN_FFFF4E00(u32 unit, u16 lo, u16 hi)
{
    *FUN_FFFF4FD4(unit, 4) = lo;
    *FUN_FFFF4FD4(unit, 6) = hi;
}
