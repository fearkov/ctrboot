#include "types.h"

extern volatile u8 DAT_10161000;
extern volatile u8 DAT_10144000;

void FUN_00013734(u32 which, u8 data)
{
    volatile u8* p = (which == 0) ? &DAT_10161000 : &DAT_10144000;
    *p = data;
}
