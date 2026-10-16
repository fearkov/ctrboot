#include "types.h"

extern volatile u32 DAT_1000A000;

void FUN_FFFFAC98()
{
    DAT_1000A000 = (DAT_1000A000 & ~1) | 2;
}
