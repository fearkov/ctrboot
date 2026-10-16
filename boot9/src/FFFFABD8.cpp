// Built for space: with -Otime armcc puts the null checks ahead of push {r4, lr}.
// The destination of the second call is computed into a local first, as the dump does (otherwise the
// add comes after the two constant arguments).
#pragma Ospace
#include "types.h"

extern "C" void FUN_FFFF05E0(const void *src, void *dst, u32 size);
extern "C" void FUN_FFFF056C(void *dst, u32 value, u32 size);

// Copies the first 0x90 bytes of src to dst and clears the 0x70 bytes after them.
u32 FUN_FFFFABD8(const void *src, u8 *dst)
{
    if (src == 0 || dst == 0)
        return 0;
    FUN_FFFF05E0(src, dst, 0x90);
    u8 *rest = dst + 0x90;
    FUN_FFFF056C(rest, 0, 0x70);
    return 1;
}
