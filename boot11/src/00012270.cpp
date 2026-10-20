#include "types.h"

extern "C" void FUN_00011A38(u32 count);

// Waits ns nanoseconds, 2^32 - 1 cycles at a time and then the rest. The ARM11 runs at 268.112 MHz.
void FUN_00012270(u64 ns)
{
    if (ns != 0) {
        u64 cycles = ns * 268112 / 1000000;
        for (u32 i = 0; i < (cycles >> 32); i++) {
            FUN_00011A38(0xFFFFFFFF);
        }
        FUN_00011A38((u32)cycles);
    }
}
