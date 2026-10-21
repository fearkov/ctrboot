// Built at -O0 (#pragma O0): the dump builds both ends of the first region and subtracts them ("mov r1, #0x8000000 /
// mov r2, #0x8000000 / sub r2, r2, r1"), which armcc folds to zero at every other level, and it calls the fill
// routine with bl both times, where armcc makes the second call a tail call. The value, the start and the size are
// global register variables on r0, r1 and r2, the registers the fill routine (FUN_FFFF8204) takes them in: at -O0
// armcc keeps locals in callee-saved registers in a function that calls and copies arguments through temporaries,
// whereas the dump builds each argument in its own register, in order, and keeps the value in r0 across the first
// call (the fill routine leaves r0 alone). The size is assigned the end and then has the start taken off, as the
// dump does in r2 ("size = end - start" loads the end into r3, or takes a constant end with rsb). The second
// region's ends are symbols: from two constants armcc builds the end from the start ("add r2, r1, #0x10"), where the
// dump loads both from the literal pool.
#pragma arm
#pragma O0
#include "types.h"

extern "C" void FUN_FFFF8204(u32 value, u32 *dst, u32 size);

extern u32 DAT_08000030[];
extern u32 DAT_08000040[];

register u32 gFillValue __asm("r0");
register u32 *gFillDst __asm("r1");
register u32 gFillSize __asm("r2");

// Zeroes two regions of ARM9 RAM with the fill routine: the one at 0x08000000, which is empty, and the 16 bytes at
// 0x08000030.
void FUN_FFFF81B8()
{
    gFillValue = 0;
    gFillDst = (u32 *)0x08000000;
    gFillSize = 0x08000000;
    gFillSize -= (u32)gFillDst;
    FUN_FFFF8204(gFillValue, gFillDst, gFillSize);
    gFillDst = DAT_08000030;
    gFillSize = (u32)DAT_08000040;
    gFillSize -= (u32)gFillDst;
    FUN_FFFF8204(gFillValue, gFillDst, gFillSize);
}
