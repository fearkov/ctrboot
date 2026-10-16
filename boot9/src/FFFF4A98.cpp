#include "types.h"

extern "C" u16 FUN_FFFF49A8(u32 unit);
extern "C" volatile u16 *FUN_FFFF4FD4(u32 unit, u32 offset);

bool FUN_FFFF4A98(u32 unit, u32 type)
{
    s32 bits;
    switch (type) {
    case 0:
        bits = FUN_FFFF49A8(unit) << 26;
        break;
    case 1:
        bits = *FUN_FFFF4FD4(unit, 0xf8) << 29;
        break;
    default:
        return false;
    }
    if (bits < 0) {
        return true;
    }
    return false;
}
