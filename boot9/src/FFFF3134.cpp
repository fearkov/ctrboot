#include "types.h"

u32 FUN_FFFF3134(u32 x)
{
    u32 field = (x << 5) >> 29;
    u32 size = 0x200u;
    return size << (field - 1);
}
