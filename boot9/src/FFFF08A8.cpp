// The zero for the write-buffer drains is in ip; armcc gives it r2, so it is a global register variable on r12. The
// schedule barrier keeps "mov ip, #0" first, where the dump has it (armcc moves it after the add).
#pragma arm
#include "types.h"

register u32 gZero __asm("r12");

// Cleans and invalidates the data cache lines that cover [start, start + size), draining the write buffer before
// each line and once more at the end.
void FUN_FFFF08A8(u32 start, s32 size)
{
    volatile register u32 clean_invalidate __asm("cp15:0:c7:c14:1");
    volatile register u32 drain_write_buffer __asm("cp15:0:c7:c10:4");
    gZero = 0;
    __schedule_barrier();
    s32 end = start + size;
    s32 line = start & ~0x1Fu;
    do {
        drain_write_buffer = gZero;
        clean_invalidate = line;
        line += 0x20;
    } while (line < end);
    drain_write_buffer = gZero;
}
