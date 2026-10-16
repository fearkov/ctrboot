// Built for space (armcc's default), like the other one-shot initialisers of this ROM.
// The two variables are reached as absolute addresses: armcc then reloads the same literal after the call
// and adds 4 for the second one, as the dump does; a DAT_ symbol is kept in r4 over the calls instead.
#pragma Ospace
#include "types.h"

extern "C" void FUN_FFFF19C8(u32 index);
extern "C" u32 FUN_FFFF1F10(u32 bit);

void FUN_FFFF1FCC()
{
    u16 *initialized = (u16 *)0xFFF0013C;
    if (*initialized == 0) {
        *initialized = 1;
        FUN_FFFF19C8(1);
        u32 *ticks = (u32 *)0xFFF00140;
        ticks[0] = 0;
        ticks[1] = 0;
        FUN_FFFF1F10(9);
    }
}
