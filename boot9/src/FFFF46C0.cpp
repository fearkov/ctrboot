#include "types.h"

u32 FUN_FFFF46C0()
{
    return ~*(volatile u8 *)0x10000010 & 1;
}
