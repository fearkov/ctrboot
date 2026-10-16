#include "types.h"

volatile u32 *FUN_FFFF4984(u32 unit)
{
    volatile u32 *fifo = (volatile u32 *)0x1000610c;
    if (unit != 1) {
        fifo = (volatile u32 *)0x1000710c;
    }
    return fifo;
}
