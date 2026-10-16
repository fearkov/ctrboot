// Built for space: with -Otime armcc checks the pointer before push {r4, lr}.
#pragma Ospace
#include "types.h"

extern "C" void FUN_FFFFACF8();
extern "C" void FUN_FFFFAD18();
extern "C" void FUN_FFFFAC60(const void *data, u32 size);
extern "C" u32 FUN_FFFFAC56(const u8 *hash);

// Hashes the first 0xE0 bytes of data and compares the result with the 0x20 bytes after them.
u32 FUN_FFFFAC34(const u8 *data)
{
    if (data == 0)
        return 0;
    FUN_FFFFACF8();
    FUN_FFFFAD18();
    FUN_FFFFAC60(data, 0xE0);
    return FUN_FFFFAC56(data + 0xE0);
}
