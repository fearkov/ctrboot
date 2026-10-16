// Built for space (armcc's default for this ROM): with -Otime the arguments are kept in r4-r6 in parameter
// order (out in r4); the original has out in r6 and the other two in r4 and r5.
#pragma Ospace
#include "types.h"

extern "C" void FUN_FFFFACF8();
extern "C" void FUN_FFFFAD18();
extern "C" void FUN_FFFFAC60(const void *data, u32 size);
extern "C" void FUN_FFFFACEC(u8 *hash);
extern "C" void FUN_FFFF05E0(const void *src, void *dst, u32 size);
extern "C" void FUN_FFFF056C(void *dst, u32 value, u32 size);

void FUN_FFFFA55C(u8 *out, const void *data, u32 size)
{
    u8 hash[0x20];
    FUN_FFFFACF8();
    FUN_FFFFAD18();
    FUN_FFFFAC60(data, size);
    FUN_FFFFACEC(hash);
    FUN_FFFF05E0(hash, out, 0x10);
    FUN_FFFF056C(hash, 0, 0x20);
}
