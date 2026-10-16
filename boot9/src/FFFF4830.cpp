#include "types.h"

extern "C" void FUN_FFFF4FB8(u32 bank, u32 offset, u16 value);

void FUN_FFFF4830(u32 bank, u16 value)
{
    FUN_FFFF4FB8(bank, 0x1c, value);
}
