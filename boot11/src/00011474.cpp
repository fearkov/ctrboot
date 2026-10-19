#pragma arm
#include "types.h"

// Prefetches the instruction cache lines that cover [start, start + size).
void FUN_00011474(u32 start, s32 size)
{
    volatile register u32 prefetch __asm("cp15:0:c7:c13:1");
    s32 end = start + size;
    s32 line = start & ~0x1Fu;
    do {
        prefetch = line;
        line += 0x20;
    } while (line < end);
}
