#include "types.h"

// The callback at 0xFFFF9F54 is not in boot9.functions: reached by its address, with the Thumb bit.
extern u8 DAT_FFFF9F54;
extern "C" void FUN_FFFF9FC4(u32 a, u32 b, u32 c, u32 d, u32 (*callback)());

void FUN_FFFF9FB0(u32 a, u32 b, u32 c, u32 d)
{
    FUN_FFFF9FC4(a, b, c, d, (u32 (*)())((u32)&DAT_FFFF9F54 + 1));
}
