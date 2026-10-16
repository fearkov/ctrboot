#include "types.h"

u8 FUN_FFFF5A56(u8 *p)
{
    u8 v = *p & 0xf;
    if (v != 0)
    {
        v = 1;
    }
    return v;
}
