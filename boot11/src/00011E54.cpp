#include "types.h"

u32 FUN_00011E54(u32 id, s32 count, u8* buffer)
{
    buffer[0] = 0x35;
    buffer[1] = (u8)(count << 3);
    buffer[2] = 0;
    return 3;
}
