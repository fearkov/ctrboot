#include "types.h"

extern "C" u64 FUN_FFFF0CD4(u64 a, u32 b);
extern "C" void FUN_FFFF19F8(u64 value);

void FUN_FFFF19E4(u64 value)
{
    FUN_FFFF19F8(FUN_FFFF0CD4(value, 1000000));
}
