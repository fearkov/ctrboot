#pragma arm
#include "types.h"

void FUN_FFFF02F4(u16 value, u8 *dst, s32 size)
{
    for (s32 i = 0; i < size; i += 2) {
        *(u16 *)(dst + i) = value;
    }
}
