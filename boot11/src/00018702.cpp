#include "types.h"

extern "C" u32 FUN_00018E30(u32 mask, u32 reg, u32 value);

bool FUN_00018702(u32 mask, u32 on)
{
    return FUN_00018E30(mask, 1, on ? 0x11 : 0x10) != 0;
}
