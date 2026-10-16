#include "types.h"

extern u32 DAT_FFF000B4;
extern u32 (*DAT_FFF000AC)(volatile u32 *);
extern u32 DAT_FFF000B8;
extern "C" void FUN_FFFF2920(u32 time);
extern "C" void FUN_FFFF48B4(u32 unit);
extern "C" volatile u32 *FUN_FFFF4984(u32 unit);
extern "C" void FUN_FFFF5CAC(u32 bits);

void FUN_FFFF2F48(void)
{
    if (DAT_FFF000B4 == 1)
        FUN_FFFF48B4(DAT_FFF000B8);
    volatile u32 *fifo = FUN_FFFF4984(DAT_FFF000B8);
    u32 r = DAT_FFF000AC(fifo);
    if (r == 0) {
        u32 t;
        if (--DAT_FFF000B4 != 0)
            t = 0x96;
        else
            t = 500;
        FUN_FFFF2920(t);
    } else {
        FUN_FFFF5CAC(r);
    }
}
