#include "types.h"

// Address of a register of one of the two controller blocks: 1 selects 0x10006000, anything else 0x10007000.
volatile u16 *FUN_FFFF4FD4(u32 unit, u32 offset)
{
    u32 base = 0x10006000;
    if (unit != 1)
    {
        base = 0x10007000;
    }
    return (volatile u16 *)(base + offset);
}
