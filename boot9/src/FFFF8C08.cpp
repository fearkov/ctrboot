#include "types.h"

extern "C" void FUN_FFFF8C18(u32 *dst, u32 a, u32 b, u32 c);

void FUN_FFFF8C08(u32 *dst, u32 b, u32 c)
{
    FUN_FFFF8C18(dst, c, b, c);
}
