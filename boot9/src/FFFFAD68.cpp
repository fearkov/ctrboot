#include "types.h"

extern volatile u32 DAT_1000A000;

u32 FUN_FFFFAD68()
{
    return (DAT_1000A000 >> 9) & 1;
}
