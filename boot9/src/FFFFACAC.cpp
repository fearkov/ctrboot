#include "types.h"

extern u16 DAT_FFF00240;

void FUN_FFFFACAC(u16 value)
{
    DAT_FFF00240 &= ~0x404;
    DAT_FFF00240 |= value;
}
