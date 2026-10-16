#include "types.h"

extern u16 DAT_FFF00240;

void FUN_FFFFACC8()
{
    DAT_FFF00240 |= 0x100;
}
