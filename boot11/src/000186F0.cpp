#include "types.h"

extern "C" u32 FUN_00018B5E(u32 which, u32 arg);

u32 FUN_000186F0(u32 which, u32 arg)
{
    u32 result = FUN_00018B5E(which, arg);
    if (result != 0 && result != 1) {
        result = 0;
    }
    return result;
}
