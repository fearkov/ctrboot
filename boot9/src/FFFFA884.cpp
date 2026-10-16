#include "types.h"

u32 FUN_FFFFA884(u32 index)
{
    if (index >= 4) {
        return 0;
    }
    volatile u32 *reg = (volatile u32 *)(0x1000B100 + index * 0x10);
    return *reg & 1;
}
