// One translation unit with FUN_FFFF8950: armcc then knows its callee needs no stack alignment, so FUN_FFFF8C80
// saves nothing but lr.
#include "types.h"

extern volatile u32 DAT_10009000;

u32 FUN_FFFF8950()
{
    return DAT_10009000 >> 31;
}

// Waits until the AES unit is idle (AES_CNT bit 31 clear).
void FUN_FFFF8C80()
{
    while (FUN_FFFF8950() != 0) {
    }
}
