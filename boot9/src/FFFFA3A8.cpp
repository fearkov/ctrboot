#include "types.h"

extern "C" u32 FUN_FFFF5610(u32 sector, u32 count, void *buf);

// Hands the sector range of the byte range (offset, size) to FUN_FFFF5610; 1 when it reports no error.
u32 FUN_FFFFA3A8(void *buf, u32 offset, u32 size)
{
    if (FUN_FFFF5610(offset >> 9, size >> 9, buf) != 0) {
        return 0;
    }
    return 1;
}
