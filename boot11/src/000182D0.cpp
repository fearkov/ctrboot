#include "types.h"

extern "C" void FUN_00011730(const void* src, u32 dst, u32 size);
extern "C" void FUN_00011398(u32 start, u32 size);

extern u8 DAT_0001B498[];

void FUN_000182D0(void)
{
    u32 size = 0x1000;
    u32 dst = 0x1FFFD000;
    FUN_00011730(DAT_0001B498, dst, size);
    FUN_00011398(dst, size);
}
