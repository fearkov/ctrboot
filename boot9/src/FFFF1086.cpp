#include "types.h"

u32 FUN_FFFF1086(u32 unused, u32 x, u8 *buf)
{
    buf[0] = 0x35;
    buf[1] = (u8)(x << 3);
    buf[2] = 0;
    return 3;
}
