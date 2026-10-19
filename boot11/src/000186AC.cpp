#include "types.h"

extern "C" u32 FUN_00018E30(u32 mask, u32 reg, u32 value);
extern "C" bool FUN_00018702(u32 mask, u32 on);

bool FUN_000186AC(u32 on)
{
    if (FUN_00018E30(3, 0x11, 0x10) == 0)
        return false;
    if (FUN_00018E30(1, 0x50, 1) == 0)
        return false;
    if (FUN_00018E30(3, 0x60, 0) == 0)
        return false;
    if (!FUN_00018702(3, on))
        return false;
    return true;
}
