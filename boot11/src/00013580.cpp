#include "types.h"

extern "C" void FUN_000137CC(u32 which);
extern "C" void FUN_000137B4(u32 which);
extern volatile u8 DAT_10161000;
extern volatile u8 DAT_10144000;

u8 FUN_00013580(u32 which)
{
    FUN_000137CC(which);
    FUN_000137B4(which);
    return *((which == 0) ? &DAT_10161000 : &DAT_10144000);
}
