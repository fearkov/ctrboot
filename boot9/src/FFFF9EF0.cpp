#include "types.h"

extern u16 DAT_FFF00240;

void FUN_FFFF9EF0(u16 mode)
{
    DAT_FFF00240 &= ~0x30;
    DAT_FFF00240 |= mode;
}
