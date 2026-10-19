#pragma arm
#include "types.h"

// Prefetches the data cache lines that cover [start, start + size).
void FUN_000113CC(u32 start, s32 size)
{
    s32 end = start + size;
    s32 line = start & ~0x1Fu;
    do {
        __pld((const void *)line);
        line += 0x20;
    } while (line < end);
}
