// One translation unit with FUN_FFFFAD58 (not inlined): armcc then knows it is a leaf function, so
// FUN_FFFFAE9C saves only lr; with FUN_FFFFAD58 declared extern it pushes {r4, lr}.
#pragma no_inline
#include "types.h"

extern volatile u32 DAT_1000A000;

u32 FUN_FFFFAD58()
{
    return DAT_1000A000 & 1;
}

// Waits until bit 1 of the control register clears, then until FUN_FFFFAD58 (bit 0) reads 0.
void FUN_FFFFAE9C()
{
    while (DAT_1000A000 & 2) {
    }
    while (FUN_FFFFAD58() != 0) {
    }
}
