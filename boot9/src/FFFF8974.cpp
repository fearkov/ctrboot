#include "types.h"

extern volatile u32 DAT_10009000;

// AES_CNT bits 5-9: words in the read FIFO; true when it is empty.
u32 FUN_FFFF8974()
{
    if (((DAT_10009000 & 0x3ff) >> 5) == 0)
    {
        return 1;
    }
    return 0;
}
