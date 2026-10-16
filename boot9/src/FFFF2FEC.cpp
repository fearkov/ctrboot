#include "types.h"

extern u32 DAT_FFF000B4;
extern u32 (*DAT_FFF000AC)(volatile u16 *);
extern u32 DAT_FFF000B8;
extern "C" void FUN_FFFF2920(u32 time);
extern "C" void FUN_FFFF488E(u32 unit, u16 bits);
extern "C" volatile u16 *FUN_FFFF495C(u32 unit);
extern "C" void FUN_FFFF5CAC(u32 bits);

void FUN_FFFF2FEC(void)
{
    if (DAT_FFF000B4 == 1)
        FUN_FFFF488E(DAT_FFF000B8, DAT_FFF000B4 << 9);
    volatile u16 *fifo = FUN_FFFF495C(DAT_FFF000B8);
    u32 r = DAT_FFF000AC(fifo);
    if (r == 0) {
        u32 t;
        if (--DAT_FFF000B4 != 0)
            t = 0x12C;
        else
            t = 0x320;
        FUN_FFFF2920(t);
    } else {
        FUN_FFFF5CAC(r);
    }
}
