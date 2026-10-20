// One translation unit with FUN_FFFFA874 (not inlined): armcc then knows it is a leaf function that
// needs no stack alignment, so FUN_FFFFABCC saves only lr.
#pragma no_inline
#include "types.h"

extern volatile u32 DAT_1000B000;

u32 FUN_FFFFA874()
{
    return DAT_1000B000 & 1;
}

// Waits for the RSA engine: until FUN_FFFFA874 (bit 0 of its control register) reads 0.
void FUN_FFFFABCC()
{
    while (FUN_FFFFA874() != 0) {
    }
}
