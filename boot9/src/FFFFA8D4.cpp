// One translation unit with FUN_FFFFA8A0 (not inlined): armcc then knows it only touches r0 and r1, so
// FUN_FFFFA8D4 keeps the index in r2 across the call and saves nothing but lr.
#pragma no_inline
#include "types.h"

u32 FUN_FFFFA8A0(u32 index)
{
    if (index >= 4) {
        return 0;
    }
    volatile u32 *reg = (volatile u32 *)(0x1000B100 + index * 0x10);
    return *reg >> 31;
}

u32 FUN_FFFFA8D4(u32 index)
{
    if (index >= 4 || FUN_FFFFA8A0(index) != 0) {
        return 0;
    }
    volatile u32 *reg = (volatile u32 *)(0x1000B100 + index * 0x10);
    *reg &= ~1;
    return 1;
}
