#include "types.h"

extern u8 DAT_1FFFA000[];
extern u8 DAT_1FFFD000[];

extern "C" void FUN_000116E4(u32 value, void* dst, u32 size);

void FUN_000121FC()
{
    FUN_000116E4(0, DAT_1FFFA000, 0x3000);
    FUN_000116E4(0, DAT_1FFFD000, 0x1000);
}
