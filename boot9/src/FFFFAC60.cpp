#include "types.h"

extern "C" void FUN_FFFF9EF0(u16 mode);
extern "C" void FUN_FFFF9D78(const void *data, u32 size);

void FUN_FFFFAC60(const void *data, u32 size)
{
    FUN_FFFF9EF0(0);
    FUN_FFFF9D78(data, size);
}
