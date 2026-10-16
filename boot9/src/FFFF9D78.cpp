// Built for space: the local buffer is reserved with push {r1-r3, r4, r5, lr} instead of sub sp.
#pragma Ospace
#include "types.h"

extern "C" void FUN_FFFF9F20(u8 *state);
extern "C" void FUN_FFFF9D90(const u8 *data, u32 size, u8 *state);

void FUN_FFFF9D78(const u8 *data, u32 size)
{
    u8 state[12];
    FUN_FFFF9F20(state);
    FUN_FFFF9D90(data, size, state);
}
