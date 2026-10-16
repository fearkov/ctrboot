#include "types.h"

extern "C" void FUN_FFFF03A4(u32 value, void *dst, u32 size);
extern "C" void FUN_FFFF08A8(void *addr, u32 size);

void FUN_FFFF95BC(void *dst, u32 size)
{
    FUN_FFFF03A4(0, dst, size);
    FUN_FFFF08A8(dst, size);
}
