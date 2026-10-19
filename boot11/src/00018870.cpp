#include "types.h"

extern volatile u32 DAT_10202200;
extern volatile u32 DAT_10202A00;

u32 FUN_00018870(u32 which)
{
    volatile u32* reg;
    if (which & 1) {
        reg = &DAT_10202200;
    } else if (which & 2) {
        reg = &DAT_10202A00;
    } else {
        return 0;
    }
    return *reg & 1;
}
