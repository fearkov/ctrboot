#include "types.h"

extern "C" u16 FUN_FFFF49C0(u32 unit);

bool FUN_FFFF4B8A(u32 unit, u32 mask)
{
    return (FUN_FFFF49C0(unit) & mask) != 0;
}
