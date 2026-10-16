#include "types.h"

extern "C" u64 FUN_FFFF0CD4(u64 value, u32 factor);
extern "C" void FUN_FFFF19F8(u64 ticks);

void FUN_FFFF19D4(u64 value)
{
    FUN_FFFF19F8(FUN_FFFF0CD4(value, 1000));
}
