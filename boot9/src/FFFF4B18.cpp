#include "types.h"

extern "C" u16 FUN_FFFF49B4(u32 unit);
extern "C" volatile u16 *FUN_FFFF4FD4(u32 unit, u32 offset);

bool FUN_FFFF4B18(u32 unit, u32 type)
{
    u32 bits;
    switch (type) {
    case 0:
        bits = (~FUN_FFFF49B4(unit) >> 3) & 3;
        break;
    case 1:
        bits = ~*FUN_FFFF4FD4(unit, 0xfc) << 30;
        break;
    default:
        return false;
    }
    if (bits) {
        return true;
    }
    return false;
}
