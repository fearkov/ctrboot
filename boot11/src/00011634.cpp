#pragma arm
#include "types.h"

// Fills size bytes at dst with the halfword value, two bytes at a time.
void FUN_00011634(u16 value, u8 *dst, s32 size)
{
    for (s32 i = 0; i < size; i += 2) {
        *(u16 *)(dst + i) = value;
    }
}
