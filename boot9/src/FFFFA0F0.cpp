#include "types.h"

extern "C" u32 FUN_FFFF5628(u32 first, u32 last, u32 sector, u32 count, void *buf);

// A copy callback for the table at DAT_FFF000C8 (called as copy(dst, src, size), see FUN_FFFFA408): reads size bytes
// from the byte offset src into dst, through the sector reader, and returns 1 when that worked.
u32 FUN_FFFFA0F0(void *dst, u32 src, u32 size)
{
    if (FUN_FFFF5628(1, 1, src >> 9, size >> 9, dst) != 0) {
        return 0;
    }
    return 1;
}
