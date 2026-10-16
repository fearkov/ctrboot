#include "types.h"

extern "C" u8 *FUN_FFFF3D78(u32 id);
extern "C" void FUN_FFFF05E0(const void *src, void *dst, u32 size);
extern "C" void FUN_FFFF056C(void *dst, u32 value, u32 size);

// Copies the CID of the device with this id (kept at offset 4 of its context) to out; zeroes out when there is none.
void FUN_FFFF5660(u32 id, u8 *out)
{
    u8 *ctx = FUN_FFFF3D78(id);
    if (ctx != 0) {
        FUN_FFFF05E0(ctx + 4, out, 0x10);
    } else {
        FUN_FFFF056C(out, 0, 0x10);
    }
}
