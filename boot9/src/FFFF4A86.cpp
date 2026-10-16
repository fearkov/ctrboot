#include "types.h"

extern "C" u16 FUN_FFFF49C0(u32 unit);

bool FUN_FFFF4A86(u32 unit)
{
    if (FUN_FFFF49C0(unit) & 0x4000) {
        return true;
    }
    return false;
}
