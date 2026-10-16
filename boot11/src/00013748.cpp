#include "types.h"

extern "C" void FUN_000137E8(u32 which);
extern volatile u8 DAT_10161001;
extern volatile u8 DAT_10144001;

void FUN_00013748(u32 which)
{
    FUN_000137E8(which);
    *((which == 0) ? &DAT_10161001 : &DAT_10144001) = 0xC2;
}
