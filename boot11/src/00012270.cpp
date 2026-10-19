#include "types.h"

extern "C" u64 FUN_00011DFC(u64 a, u32 b);
extern "C" u64 FUN_00012F4C(u64 dividend, u64 divisor);
extern "C" void FUN_00011A38(u32 count);

// Nanoseconds to cycles of the 268.112 MHz ARM11. An inline function: written in place, the two halves of the time
// swap registers.
static inline u64 ToCycles(u64 ns)
{
    return FUN_00012F4C(FUN_00011DFC(ns, 0x41750), 1000000);
}

// Waits ns nanoseconds, 2^32 - 1 cycles at a time and then the rest.
void FUN_00012270(u64 ns)
{
    if (ns != 0) {
        u64 cycles = ToCycles(ns);
        for (u32 i = 0; i < (cycles >> 32); i++) {
            FUN_00011A38(0xFFFFFFFF);
        }
        FUN_00011A38((u32)cycles);
    }
}
