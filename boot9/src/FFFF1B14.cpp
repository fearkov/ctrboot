#include "types.h"

extern u32 DAT_FFF0018C;
extern "C" void FUN_FFFF1DBC(u32 channel);
extern "C" void FUN_FFFF1B58();
extern "C" void FUN_FFFF13D8(u32 index, s32 arg);
extern "C" u32 FUN_FFFF1A9C(u32 index);

// Runs once: sets up channels 0 to 3, then sends four commands to unit 0, waiting each time until it is idle.
void FUN_FFFF1B14()
{
    if (DAT_FFF0018C == 0) {
        s32 i;
        for (i = 0; i < 4; i++) {
            FUN_FFFF1DBC(i);
        }
        FUN_FFFF1B58();
        // A variable, not a constant: the dump keeps this argument in a register.
        s32 arg = 0;
        for (; i < 8; i++) {
            FUN_FFFF13D8(0, arg);
            while (FUN_FFFF1A9C(0) != 0) {
            }
        }
        DAT_FFF0018C = 1;
    }
}
