#include "types.h"

extern "C" void *FUN_FFFF25F0(void *dst, const void *src, u32 size);
extern "C" void FUN_FFFF3198(u32 channel, u32 *dst);
extern "C" void FUN_FFFF344C(u32 *dst, u32 size, void *command, void (*callback)(u32, u32 *));

void FUN_FFFF320C(u32 address, u32 *dst, u32 size, void *command)
{
    u64 data = (u64)(((address >> 9) << 1) + 0xB7000000) << 32;

    FUN_FFFF25F0(command, &data, 8);
    FUN_FFFF344C(dst, size, command, FUN_FFFF3198);
}
