#include "types.h"

extern "C" void FUN_000137CC(u32 which);
extern "C" void FUN_000137B4(u32 which);
extern volatile u8 DAT_10161001;
extern volatile u8 DAT_10144001;

u32 FUN_000135A4(u32 which)
{
    FUN_000137CC(which);
    FUN_000137B4(which);
    return (*((which == 0) ? &DAT_10161001 : &DAT_10144001) >> 4) & 1;
}
