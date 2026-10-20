// Built with the optimizer's O1 (#pragma O1): the dump keeps "add ip, ip, #0x40000000 / cmp ip, #0 / bne" apart,
// which -O3 fuses into adds/bne. Like the other cache test loops, the dump keeps the way in ip, the line in r2 and
// the index in r3, and never touches r1. The way is a global register variable on r12, and r1 is held by an unused
// one (gUnused), so that armcc gives the line r2 and the index r3 (by itself it picks r1 and r2).
#pragma arm
#pragma O1
#include "types.h"

register u32 gUnused __asm("r1");
register u32 gWay __asm("r12");

// Writes the same value to the tag of every instruction cache line, in each of the four ways.
void FUN_FFFF0B70(u32 value)
{
    register u32 index __asm("cp15:3:c15:c0:0");
    register u32 tag __asm("cp15:3:c15:c1:0");
    gWay = 0;
    do {
        s32 line = 0;
        do {
            index = line | gWay;
            tag = value;
            line += 0x20;
        } while (line < 0x800);
        gWay += 0x40000000;
    } while (gWay != 0);
}
