// Built with the optimizer's O1 (#pragma O1): the dump keeps "add r1, r1, #0x40000000 / cmp r1, #0 / bne" apart,
// which -O3 fuses into adds/bne. The zero for the write-buffer drain is in ip, which armcc only picks by itself
// once r0-r3 are all live, so it is a global register variable on r12.
#pragma arm
#pragma O1
#include "types.h"

register u32 gZero __asm("r12");

// Cleans and invalidates the whole data cache, set by set and way by way.
void FUN_00011320()
{
    volatile register u32 clean_invalidate __asm("cp15:0:c7:c14:2");
    volatile register u32 drain_write_buffer __asm("cp15:0:c7:c10:4");
    gZero = 0;
    u32 way = 0;
    do {
        s32 index = 0;
        do {
            u32 set = way | index;
            drain_write_buffer = gZero;
            clean_invalidate = set;
            index += 0x20;
        } while (index < 0x1000);
        way += 0x40000000;
    } while (way != 0);
    drain_write_buffer = gZero;
}
