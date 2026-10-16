#include "types.h"

u16 FUN_FFFF5684(u8 *p)
{
    return (u16)((p[0] << 8) | p[1]);
}
