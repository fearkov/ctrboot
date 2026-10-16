#include "types.h"

extern "C" u16 FUN_FFFF49A8(u32 unit);

bool FUN_FFFF4C7C(u32 unit, u32 mask)
{
    return (FUN_FFFF49A8(unit) & mask) != 0;
}
