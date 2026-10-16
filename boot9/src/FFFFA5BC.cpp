#include "types.h"

extern "C" void FUN_FFFF03F0(u32 *dst, u32 *src, u32 size);

void FUN_FFFFA5BC(u32 *dst, u32 *src, u32 size)
{
    FUN_FFFF03F0(dst, src, size);
}
