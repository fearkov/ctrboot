// Copies words out of a byte buffer, reading them big-endian. The dump is what armcc makes of
// (src[0] << 24) | (src[1] << 16) | (src[2] << 8) | src[3] when it builds for space without
// unaligned access: a call to the unaligned read helper (FUN_00013260 is __aeabi_uread4), rev,
// clear the low byte, or in src[3]. The build flags allow unaligned access, so that is written out.
#include "types.h"

extern "C" u32 FUN_00013260(const u8* p);

void FUN_000122FC(const u8* src, u32* dst, u32 size)
{
    const u8* end = src + size;
    while (src < end) {
        *dst++ = (__rev(FUN_00013260(src)) & ~0xFFu) | src[3];
        src += 4;
    }
}
