#include "types.h"

extern "C" void FUN_FFFF0198(u32 cycles);

// Waits ns nanoseconds, 2^32 - 1 cycles at a time and then the rest. The ARM9 runs at 134.056 MHz.
void FUN_FFFF19F8(u64 ns)
{
    if (ns != 0) {
        u64 cycles = ns * 134056 / 1000000;
        for (u32 i = 0; i < (cycles >> 32); i++) {
            FUN_FFFF0198(0xFFFFFFFF);
        }
        FUN_FFFF0198((u32)cycles);
    }
}
