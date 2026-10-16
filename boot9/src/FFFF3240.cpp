#include "types.h"

extern "C" void FUN_FFFF344C(u32 *dst, u32 size, void *s, void (*cb)(u32, u32 *));
extern "C" void FUN_FFFF3198(u32 index, u32 *dst);

void FUN_FFFF3240(u32 *dst, u32 size, void *s)
{
    FUN_FFFF344C(dst, size, s, FUN_FFFF3198);
}
