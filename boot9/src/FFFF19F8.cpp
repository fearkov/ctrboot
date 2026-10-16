#include "types.h"

extern "C" u64 FUN_FFFF0CD4(u64 a, u32 b);
// The C library's 64-bit division, __pure as armcc knows its own helpers to be.
extern "C" __pure u64 FUN_FFFF22E8(u64 dividend, u64 divisor);
extern "C" void FUN_FFFF0198(u32 cycles);

// Nanoseconds to cycles of the 134.056 MHz ARM9. An inline function: written in place, the two halves of the time
// swap registers.
static inline u64 ToCycles(u64 ns)
{
    return FUN_FFFF22E8(FUN_FFFF0CD4(ns, 134056), 1000000);
}

// Waits ns nanoseconds, 2^32 - 1 cycles at a time and then the rest.
void FUN_FFFF19F8(u64 ns)
{
    if (ns != 0) {
        u64 cycles = ToCycles(ns);
        for (u32 i = 0; i < (cycles >> 32); i++) {
            FUN_FFFF0198(0xFFFFFFFF);
        }
        FUN_FFFF0198((u32)cycles);
    }
}
