#include "types.h"

extern "C" u16 FUN_FFFF49B4(u32 unit);

bool FUN_FFFF4B46(u32 unit, u32 mask)
{
    return (mask & ~FUN_FFFF49B4(unit)) != 0;
}
