#include "types.h"

extern "C" u32 FUN_00018B5E(u32 which, u32 reg);

// Reads register 0x62 of the screens in which through FUN_00018B5E; returns the value when it is 0 or 1, else 0.
u32 FUN_000186EE(u32 which)
{
    u32 result = FUN_00018B5E(which, 0x62);
    if (result != 0 && result != 1) {
        result = 0;
    }
    return result;
}
