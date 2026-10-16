#include "types.h"

extern "C" void *FUN_FFFF25F0(void *dst, const void *src, u32 size);
extern u8 DAT_FFF00240[];

void FUN_FFFFADE0(const void *state)
{
    FUN_FFFF25F0(DAT_FFF00240, state, 0xC);
}
