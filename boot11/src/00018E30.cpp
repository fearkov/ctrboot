#include "types.h"

extern "C" u32 FUN_00013878(u32 dev, u32 reg, u32 value);

u32 FUN_00018E30(u32 mask, u32 reg, u32 value)
{
    u32 a = (mask & 1) ? FUN_00013878(5, reg, value) : 1;
    u32 b = (mask & 2) ? FUN_00013878(6, reg, value) : 1;
    return a & b;
}
