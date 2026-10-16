#include "types.h"

extern "C" u32 FUN_00018894(u32 which, u32 a, u32 b);
extern "C" void FUN_00018C00(u32 mask, u32 value);

void FUN_00018C70(u32 mask, u32 arg, u32 flag)
{
    if (mask & 1) {
        FUN_00018C00(1, FUN_00018894(1, arg, flag));
    }
    if (mask & 2) {
        FUN_00018C00(2, FUN_00018894(2, arg, 0));
    }
}
