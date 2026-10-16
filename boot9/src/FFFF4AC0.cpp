#include "types.h"

extern "C" u16 FUN_FFFF49CC(u32 unit);

bool FUN_FFFF4AC0(u32 unit, u32 mask)
{
    return (mask & ~FUN_FFFF49CC(unit)) != 0;
}
