#include "types.h"

extern volatile u32 DAT_10163000;

void FUN_00012EB4(u32 value)
{
    DAT_10163000 = (DAT_10163000 & ~0xFF00u) | (value << 8);
}
