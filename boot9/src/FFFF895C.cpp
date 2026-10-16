#include "types.h"

extern volatile u32 DAT_10009000;

// AES_CNT bits 0-4: words in the write FIFO; true when it is full (16).
u32 FUN_FFFF895C()
{
    if ((DAT_10009000 & 0x1f) == 0x10)
    {
        return 1;
    }
    return 0;
}
