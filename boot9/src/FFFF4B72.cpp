#include "types.h"

extern "C" volatile u16 *FUN_FFFF4FD4(u32 unit, u32 offset);

bool FUN_FFFF4B72(u32 unit)
{
    if (*FUN_FFFF4FD4(unit, 0x100) & 0x100) {
        return true;
    }
    return false;
}
