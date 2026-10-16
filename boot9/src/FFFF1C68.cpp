#include "types.h"

extern volatile u32 DAT_10002000;

void FUN_FFFF1C68(u32 mode, u32 value)
{
    if (mode == 0x80000000) {
        DAT_10002000 = value | 0x80000001;
    } else {
        DAT_10002000 = 1;
    }
}
