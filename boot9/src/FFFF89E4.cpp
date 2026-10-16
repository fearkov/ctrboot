#include "types.h"

extern volatile u32 DAT_10009000;

void FUN_FFFF89E4()
{
    DAT_10009000 = 0x10C00;
    *(volatile u8 *)0x10000008 |= 0xC;
}
