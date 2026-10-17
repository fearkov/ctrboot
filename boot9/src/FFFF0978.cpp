// The dump keeps the load and the pointer increment apart ("ldr r2, [r0]" then "add r0, r0, #0x20"), which only
// -O1 does: at -O3 armcc folds them into "ldr r2, [r0], #0x20".
#pragma arm
#pragma O1
#include "types.h"

// Reads one word from every data cache line that covers [start, start + size), which pulls the lines in.
void FUN_FFFF0978(u32 start, s32 size)
{
    s32 end = start + size;
    s32 line = start & ~0x1Fu;
    do {
        u32 touch = *(volatile u32 *)line;
        line += 0x20;
    } while (line < end);
}
