#include "types.h"

extern volatile u8 DAT_10161001;
extern volatile u8 DAT_10144001;

void FUN_00011E30(u32 which)
{
    volatile u8* a = &DAT_10161001;
    volatile u8* b = &DAT_10144001;
    volatile u8* p;
    do {
        p = (which == 0) ? a : b;
    } while (*p & 0x80);
}
