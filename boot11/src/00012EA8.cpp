// FUN_00012ECC is in this file, after FUN_00012EA8: armcc then knows that one only uses r0, so FUN_00012ECC keeps
// its argument in r1 and needs no stack alignment (push {lr}).
#include "types.h"

extern volatile u32 DAT_10163000;

u32 FUN_00012EA8()
{
    return (u8)DAT_10163000;
}

// Waits until the sync byte reads value.
void FUN_00012ECC(u32 value)
{
    while (FUN_00012EA8() != value) {
    }
}
