#include "types.h"

extern volatile u32 DAT_1000CD00;

u32 FUN_FFFF1BCC()
{
    return DAT_1000CD00 & 1;
}
