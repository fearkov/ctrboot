#include "types.h"

extern "C" void FUN_FFFF483C(u32 bank, u16 value);

void FUN_FFFF4818(u32 bank, u16 value)
{
    FUN_FFFF483C(bank, value);
}
