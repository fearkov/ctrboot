// Built with the optimizer's O1 (#pragma O1): the dump keeps "add r1, r1, #0x40000000 / cmp r1, #0 / bne" apart,
// which -O3 fuses into adds/bne. The zero for the final write-buffer drain is in ip, which armcc only picks by
// itself once r0-r3 are all live, so it is a global register variable on r12.
#pragma arm
#pragma O1
#include "types.h"

register u32 gZero __asm("r12");

// Cleans the whole data cache, way by way and set by set, and waits for the writes to finish.
void FUN_000112EC()
{
    register u32 clean __asm("cp15:0:c7:c10:2");
    register u32 drain_write_buffer __asm("cp15:0:c7:c10:4");
    u32 way = 0;
    do {
        s32 set = 0;
        do {
            clean = way | set;
            set += 0x20;
        } while (set < 0x1000);
        way += 0x40000000;
    } while (way != 0);
    gZero = 0;
    drain_write_buffer = gZero;
}
