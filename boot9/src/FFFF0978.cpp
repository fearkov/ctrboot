#pragma arm
#include "types.h"

// Built at -O1: at -O3 armcc folds the pointer increment into the load (ldr r2, [r0], #0x20).
#pragma O1

// Reads one word from every data cache line that covers [start, start + size).
void FUN_FFFF0978(u32 start, s32 size)
{
    s32 end = start + size;
    s32 line = start & ~0x1Fu;
    do {
        u32 touch = *(volatile u32 *)line;
        line += 0x20;
    } while (line < end);
}
