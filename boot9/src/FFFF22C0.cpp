#include "types.h"

extern volatile u32 DAT_10008000;

void FUN_FFFF22C0(u32 value)
{
    DAT_10008000 = (DAT_10008000 & ~0xFF00u) | (value << 8);
}
