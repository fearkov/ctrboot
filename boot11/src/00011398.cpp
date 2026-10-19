// Built with the optimizer's O1 (#pragma O1) so that the "mov ip, #0" stays in front of the add and the bic. The zero
// for the write-buffer drain is in ip, which armcc only picks by itself once r0-r3 are all live, so it is a global
// register variable on r12.
#pragma arm
#pragma O1
#include "types.h"

register u32 gZero __asm("r12");

// Cleans and invalidates the data cache lines that cover [start, start + size).
void FUN_00011398(u32 start, s32 size)
{
    volatile register u32 clean_invalidate __asm("cp15:0:c7:c14:1");
    volatile register u32 drain_write_buffer __asm("cp15:0:c7:c10:4");
    gZero = 0;
    s32 end = start + size;
    s32 line = start & ~0x1Fu;
    do {
        drain_write_buffer = gZero;
        clean_invalidate = line;
        line += 0x20;
    } while (line < end);
    drain_write_buffer = gZero;
}
