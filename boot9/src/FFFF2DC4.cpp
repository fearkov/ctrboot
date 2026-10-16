#include "types.h"

extern u32 DAT_FFF000B4;
extern u32 DAT_FFF000B8;
extern u32 (*DAT_FFF000AC)(volatile u16 *fifo);

extern "C" void FUN_FFFF2920(u32 time);
extern "C" void FUN_FFFF488E(u32 unit, u16 bits);
extern "C" bool FUN_FFFF4C7C(u32 unit, u32 mask);
extern "C" volatile u16 *FUN_FFFF495C(u32 unit);
extern "C" void FUN_FFFF5CAC(u32 bits);

void FUN_FFFF2DC4()
{
    if (DAT_FFF000B4 == 1) {
        FUN_FFFF488E(DAT_FFF000B8, DAT_FFF000B4 << 8);
        u32 i = 0;
        while (!FUN_FFFF4C7C(DAT_FFF000B8, 1)) {
            if (++i > 0x28E970) {
                FUN_FFFF5CAC(0x800);
                break;
            }
        }
    }
    u32 result = DAT_FFF000AC(FUN_FFFF495C(DAT_FFF000B8));
    if (result == 0) {
        FUN_FFFF2920(--DAT_FFF000B4 != 0 ? 0x96 : 500);
    } else {
        FUN_FFFF5CAC(result);
    }
}
