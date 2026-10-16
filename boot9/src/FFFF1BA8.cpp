#include "types.h"

u32 FUN_FFFF1BA8(u32 index)
{
    volatile u32 *reg = (volatile u32 *)(0x1000201C + index * 0x1C);
    return *reg >> 31;
}
