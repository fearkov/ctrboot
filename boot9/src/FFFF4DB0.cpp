#include "types.h"

void FUN_FFFF4DB0(u32 unit, u32 mode)
{
    u32 a = 0x10006000;
    if (unit != 1) {
        a = 0x10007000;
    }
    volatile u16 *ctl = (volatile u16 *)(a + 0x100);
    u32 b = 0x10006000;
    if (unit != 1) {
        b = 0x10007000;
    }
    volatile u16 *tim = (volatile u16 *)(b + 0xD8);
    switch (mode) {
    case 0:
        *ctl = *ctl | 0x402;
        *tim = (*tim & ~0x22) + 2;
        break;
    case 1:
        *ctl = *ctl & ~2;
        *tim = *tim & ~0x22;
        break;
    }
}
