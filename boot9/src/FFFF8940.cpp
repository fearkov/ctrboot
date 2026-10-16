#include "types.h"

extern volatile u32 DAT_10009000;

u32 FUN_FFFF8940()
{
    return (DAT_10009000 >> 5) & 0x1f;
}
