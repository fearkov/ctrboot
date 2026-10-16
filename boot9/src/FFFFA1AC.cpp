#include "types.h"

extern "C" u32 FUN_FFFF5AA4(u32 first, u32 last, u32 sector, u32 count, void *buf);

// Runs the one-chunk sector transfer FUN_FFFF5AA4 (both first and last set) on size / 0x200 sectors starting at
// byte offset offset; 1 when it reports no error. FUN_FFFFA26C is the same with FUN_FFFF5D04.
u32 FUN_FFFFA1AC(void *buf, u32 offset, u32 size)
{
    if (FUN_FFFF5AA4(1, 1, offset >> 9, size >> 9, buf) != 0) {
        return 0;
    }
    return 1;
}
