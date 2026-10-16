#include "types.h"

extern "C" u32 FUN_00013626(u32 dev, u32 reg, u8* buffer, u32 count);

bool FUN_0001391C(u32 reg, u8* buffer, u32 count)
{
    return FUN_00013626(3, reg, buffer, count) != 0;
}
