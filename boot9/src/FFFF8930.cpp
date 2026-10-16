#include "types.h"

extern volatile u32 DAT_10009000;

u32 FUN_FFFF8930()
{
    return DAT_10009000 & 0x1f;
}
