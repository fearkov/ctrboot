#include "types.h"

extern "C" u32 FUN_FFFFAB50(u32 bits, const void *data);
extern "C" u32 FUN_FFFFA900(u32 a, u32 b, u32 c);
extern "C" void FUN_FFFFAC60(const void *data, u32 size);
extern "C" void FUN_FFFFACEC(u8 *hash);
extern "C" void FUN_FFFFABCC();
extern "C" u32 FUN_FFFFA818(s32 bits, u8 *dst);
extern "C" u8 *FUN_FFFFA7E0(u8 *p, s32 len);
extern "C" u32 FUN_FFFFA784(u8 *p, u8 **end);

// Checks the RSA-2048 signature at the start of an NCSD image (its header follows at 0x100).
u32 FUN_FFFFA4C4(u8 *image, u32 key)
{
    __align(8) u8 hash[0x20];
    __align(8) u8 block[0x100];
    u8 *digest;
    u32 equal = 1;
    if (image == 0) {
        return 0;
    }
    u8 *header = image + 0x100;
    if (*(u32 *)header != 0x4453434E) {
        return 0;
    }
    if (FUN_FFFFAB50(0x800, image) == 0) {
        return 0;
    }
    if (FUN_FFFFA900(key, 0, 0) == 0) {
        return 0;
    }
    FUN_FFFFAC60(header, 0x100);
    FUN_FFFFACEC(hash);
    FUN_FFFFABCC();
    if (FUN_FFFFA818(0x800, block) == 0) {
        return 0;
    }
    digest = FUN_FFFFA7E0(block, 0x100);
    if (digest == 0) {
        return 0;
    }
    if (FUN_FFFFA784(digest, &digest) == 0) {
        return 0;
    }
    for (int i = 0; i < 0x20; i++) {
        equal &= hash[i] == digest[i];
    }
    return equal;
}
