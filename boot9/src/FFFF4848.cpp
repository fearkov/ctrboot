#include "types.h"

extern "C" u16 *FUN_FFFF4FD4(u32 bank, u32 offset);

void FUN_FFFF4848(u32 bank, u16 value)
{
    *FUN_FFFF4FD4(bank, 0) = value;
}
