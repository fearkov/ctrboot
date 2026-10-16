#include "types.h"

extern "C" void FUN_000185FC(u32 which);
extern u32 DAT_1FFE80C4;

void FUN_00018ED0()
{
    if (DAT_1FFE80C4 & 1) {
        FUN_000185FC(0);
    }
    if (DAT_1FFE80C4 & 2) {
        FUN_000185FC(1);
    }
}
