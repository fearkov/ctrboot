#include "types.h"

extern "C" void FUN_FFFF3CE8(u32 unit);
extern "C" void FUN_FFFF5730(u32 unit);

u32 FUN_FFFF5B34(u32 unit, u32 a, u32 b)
{
    if (a != 0 || b != 0)
    {
        FUN_FFFF3CE8(unit);
        FUN_FFFF5730(unit);
        return 1;
    }
    return 0;
}
