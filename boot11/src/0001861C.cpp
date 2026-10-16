#include "types.h"

extern volatile u32 DAT_10202240;
extern volatile u32 DAT_10202A40;

u32 FUN_0001861C(u32 which)
{
    volatile u32* reg;
    if (which & 1) {
        reg = &DAT_10202240;
    } else if (which & 2) {
        reg = &DAT_10202A40;
    } else {
        return 0xFFFF;
    }
    return (u16)*reg;
}
