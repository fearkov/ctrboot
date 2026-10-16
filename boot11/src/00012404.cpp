#include "types.h"

extern volatile u32 DAT_10200D00;

u32 FUN_00012404()
{
    return DAT_10200D00 & 1;
}
