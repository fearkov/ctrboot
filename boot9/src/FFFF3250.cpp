// Built for space: the 8-byte local comes from pushing r2 and r3 along with the saved registers.
#pragma Ospace
#include "types.h"

extern "C" void *FUN_FFFF25F0(void *dst, const void *src, u32 size);
extern "C" void FUN_FFFF31D0(u32 channel, u32 *dst);
extern "C" void FUN_FFFF344C(u32 *dst, u32 size, void *command, void (*callback)(u32, u32 *));

void FUN_FFFF3250(u32 address, u32 *dst, u32 size, void *command)
{
    u64 data = (u64)(((address >> 9) << 1) + 0xB7000000) << 32;

    FUN_FFFF25F0(command, &data, 8);
    FUN_FFFF344C(dst, size, command, FUN_FFFF31D0);
}
