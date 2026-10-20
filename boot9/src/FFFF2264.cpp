// One translation unit with FUN_FFFF2264: armcc then knows it only touches r0, so FUN_FFFF22D8 keeps the value in
// r1 across the call and saves nothing but lr.
#include "types.h"

extern volatile u32 DAT_10008000;

u8 FUN_FFFF2264()
{
    return (u8)DAT_10008000;
}

// Waits until the other processor's sync byte reads value.
void FUN_FFFF22D8(u32 value)
{
    while (FUN_FFFF2264() != value) {
    }
}
