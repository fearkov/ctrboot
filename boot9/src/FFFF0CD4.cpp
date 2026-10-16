#pragma arm
#include "types.h"

extern "C" u64 FUN_FFFF25D8(u64 a, u64 b);

u64 FUN_FFFF0CD4(u64 a, u32 b)
{
    return FUN_FFFF25D8(a, b);
}
