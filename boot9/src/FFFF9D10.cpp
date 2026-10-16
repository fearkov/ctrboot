// Built for space, like the rest of this ROM's crypto drivers.
#pragma Ospace
#include "types.h"

// Copies size bytes from src to dst in reverse order.
void FUN_FFFF9D10(u8 *dst, const u8 *src, u32 size)
{
    const u8 *end = src + size;
    while (size--) {
        *dst++ = *--end;
    }
}
