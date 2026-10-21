// Built with the optimizer's O1 (#pragma O1): the dump keeps "add ip, ip, #0x40000000 / cmp ip, #0 / bne" apart,
// which -O3 fuses into adds/bne. Like the other cache test loops, the dump keeps the segment in ip, the offset in r2
// and the index in r3, and never touches r1. The segment is a global register variable on r12, and r1 is held by
// an unused one (gUnused), so that armcc gives the offset r2 and the index r3 (by itself it picks r1 and r2).
#pragma arm
#pragma O1
#include "types.h"

register u32 gUnused __asm("r1");
register u32 gSegment __asm("r12");

// Writes the same value to every word of the data cache's data RAM, in each of the four segments.
void FUN_FFFF09C4(u32 value)
{
    register u32 index __asm("cp15:3:c15:c0:0");
    register u32 ram __asm("cp15:3:c15:c4:0");
    gSegment = 0;
    do {
        s32 offset = 0;
        do {
            index = offset | gSegment;
            ram = value;
            offset += 0x4;
        } while (offset < 0x400);
        gSegment += 0x40000000;
    } while (gSegment != 0);
}
