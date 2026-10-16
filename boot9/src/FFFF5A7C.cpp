#include "types.h"

u32 FUN_FFFF5A7C(u16 *p)
{
    if ((s32)((u32)*p << 21) < 0)
    {
        return 1;
    }
    return 0;
}
