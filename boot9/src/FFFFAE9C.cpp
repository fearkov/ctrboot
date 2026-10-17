// One translation unit with FUN_FFFFAD58 (not inlined): armcc then knows it is a leaf function that
// only uses r0, so FUN_FFFFAE9C saves only lr (with FUN_FFFFAD58 declared extern it pushes {r4, lr}),
// and FUN_FFFF9D44 and FUN_FFFF9DEC keep r1-r3 live across their calls to it.
#pragma no_inline
#include "types.h"

extern volatile u32 DAT_1000A000;
extern volatile u8 DAT_1000A040[0x20];

u32 FUN_FFFFAD58()
{
    return DAT_1000A000 & 1;
}

// Compares the engine's hash with expected: 1 when all size bytes are equal.
u32 FUN_FFFF9D44(const u8 *expected, u32 size)
{
    const u8 *p = expected;
    const volatile u8 *hash = DAT_1000A040;
    u32 equal = 1;
    while (FUN_FFFFAD58()) {
    }
    while (size--) {
        equal &= *p++ == *hash++;
    }
    return equal;
}

// Copies size bytes of the engine's hash to dst.
void FUN_FFFF9DEC(u8 *dst, u32 size)
{
    u8 *p = dst;
    const volatile u8 *hash = DAT_1000A040;
    while (FUN_FFFFAD58()) {
    }
    while (size--) {
        *p++ = *hash++;
    }
}

// Waits until bit 1 of the control register clears, then until FUN_FFFFAD58 (bit 0) reads 0.
void FUN_FFFFAE9C()
{
    while (DAT_1000A000 & 2) {
    }
    while (FUN_FFFFAD58() != 0) {
    }
}
