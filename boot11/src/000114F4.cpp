#pragma arm
#include "types.h"

// Flushes the branch target cache entries for every halfword in [start, start + size).
void FUN_000114F4(u32 start, s32 size)
{
    volatile register u32 flush_entry __asm("cp15:0:c7:c5:7");
    s32 end = start + size;
    s32 address = start & ~1u;
    do {
        flush_entry = address;
        address += 2;
    } while (address < end);
}
