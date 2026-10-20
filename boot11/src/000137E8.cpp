// TICKS_TO_NS is a macro that writes its argument twice: armcc computes 0xBC - elapsed twice and merges the
// copies only after register allocation, which leaves r5 saved but unused, as in the dump. With the argument
// evaluated once (a temporary or an inline function) armcc saves only r4-r6, and "* 2" written in the same
// expression as "* 1000000" folds into one multiply by 2000000.
#include "types.h"

extern "C" u64 FUN_000125E4();
extern "C" void FUN_00012270(u64 ns);
extern u64 DAT_1FFE8E50[];

// MPCore private timer ticks to nanoseconds: the timer counts at half the 268.112 MHz CPU clock.
#define TICKS_TO_NS(ticks) (((ticks) + (ticks)) * 1000000 / 268112)

// Waits until 0xBC timer ticks have passed since the last access to I2C bus which (FUN_000137B4 records it).
void FUN_000137E8(u32 which)
{
    u64 elapsed = FUN_000125E4() - DAT_1FFE8E50[which];
    if (elapsed < 0xBC) {
        FUN_00012270((u32)TICKS_TO_NS(0xBC - elapsed));
    }
}
