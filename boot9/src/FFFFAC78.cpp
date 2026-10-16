#include "types.h"

extern u16 DAT_FFF00240;

void FUN_FFFFAC78()
{
    DAT_FFF00240 &= ~0x404;
}
