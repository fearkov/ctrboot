#include "types.h"

extern "C" u32 FUN_0001391C(u32 reg, u8* buffer, u32 count);

bool FUN_00013A7C(u8* buffer)
{
    return FUN_0001391C(0xF, buffer, 1) != 0;
}
