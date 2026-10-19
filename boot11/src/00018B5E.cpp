#include "types.h"

extern "C" u32 FUN_000135CC(u32 dev, u32 reg, u32 arg);

u32 FUN_00018B5E(u32 which, u32 arg)
{
    if (which == 3) {
        u32 a = FUN_000135CC(5, 0x40, arg);
        u32 b = FUN_000135CC(6, 0x40, arg);
        if (b == a) {
            return a;
        }
        return 0xFE;
    }
    return FUN_000135CC(which == 1 ? 5 : 6, 0x40, arg);
}
