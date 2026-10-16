#include "types.h"

extern u8 DAT_FFF00138[];

void FUN_FFFF19C8(u32 index)
{
    DAT_FFF00138[index] = 1;
}
