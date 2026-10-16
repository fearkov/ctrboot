#include "types.h"

extern u8 DAT_10200100[];

u32 FUN_00012320(u32 id)
{
    volatile u32* reg = (volatile u32*)(DAT_10200100 + id * 8);
    return *reg & 0xF;
}
