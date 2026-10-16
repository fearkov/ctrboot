#include "types.h"

extern u8 DAT_FFF0009C;
extern u8 DAT_FFF0009D;
extern u32 (*DAT_FFF000AC)(volatile u16 *fifo);
extern u32 DAT_FFF000B4;
extern u32 DAT_FFF000B8;

extern "C" u32 FUN_FFFF2904(u32 numerator, u32 denominator);
extern "C" void FUN_FFFF2920(u32 time);
extern "C" u16 FUN_FFFF4974(u32 unit);
extern "C" bool FUN_FFFF4C8C(u32 unit);
extern "C" void FUN_FFFF57F4();
extern "C" void FUN_FFFF5CAC(u32 bits);

// Callback of the transfer timer started by FUN_FFFF2920: if enough blocks went through the FIFO since
// the last check, restarts the timer with the same time; otherwise reports a timeout (0x200) and
// recovers.
void FUN_FFFF4FE8(u32 time)
{
    if (DAT_FFF0009C && !DAT_FFF000AC && FUN_FFFF4C8C(DAT_FFF000B8) && DAT_FFF000B4) {
        u32 now = FUN_FFFF4974(DAT_FFF000B8);
        u32 elapsed = DAT_FFF000B4 - now;
        u32 limit;
        if (DAT_FFF0009D) {
            limit = FUN_FFFF2904(time - 500, 150);
        } else {
            limit = FUN_FFFF2904(time - 500, 300);
        }
        if (elapsed >= limit) {
            DAT_FFF000B4 = now;
            FUN_FFFF2920(time);
            return;
        }
    }
    FUN_FFFF5CAC(0x200);
    FUN_FFFF57F4();
}
