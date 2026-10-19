#pragma arm
#include "types.h"

// Invalidates the data cache lines that cover [start, start + size).
void FUN_00011358(u32 start, s32 size)
{
    volatile register u32 invalidate __asm("cp15:0:c7:c6:1");
    s32 end = start + size;
    s32 line = start & ~0x1Fu;
    do {
        invalidate = line;
        line += 0x20;
    } while (line < end);
}
