// The zero for the final write-buffer drain is in ip, which armcc only picks by itself once r0-r3 are all live, so it
// is a global register variable on r12.
#pragma arm
#include "types.h"

register u32 gZero __asm("r12");

// Cleans the data cache lines that cover [start, start + size) and waits for the writes to finish.
void FUN_FFFF0884(u32 start, s32 size)
{
    volatile register u32 clean __asm("cp15:0:c7:c10:1");
    volatile register u32 drain_write_buffer __asm("cp15:0:c7:c10:4");
    s32 end = start + size;
    s32 line = start & ~0x1Fu;
    do {
        clean = line;
        line += 0x20;
    } while (line < end);
    gZero = 0;
    drain_write_buffer = gZero;
}
