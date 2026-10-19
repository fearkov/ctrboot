#include "types.h"

extern "C" void FUN_FFFF19F8(u64 ticks);

void FUN_FFFF19D4(u64 value)
{
    FUN_FFFF19F8(value * 1000);
}
