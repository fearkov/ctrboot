#include "types.h"

struct FirmHeader
{
    u32 magic;          // "FIRM"
    u8 pad04[0xFC];
    u8 signature[0x100]; // RSA-2048 over the first 0x100 bytes
};

extern "C" u32 FUN_FFFFAB50(u32 bits, const void *data);
extern "C" u32 FUN_FFFFA900(u32 a, u32 b, u32 c);
extern "C" void FUN_FFFFAC60(const void *data, u32 size);
extern "C" void FUN_FFFFACEC(u8 *hash);
extern "C" void FUN_FFFFABCC();
extern "C" u32 FUN_FFFFA818(s32 bits, u8 *dst);
extern "C" u8 *FUN_FFFFA7E0(u8 *p, s32 len);
extern "C" u32 FUN_FFFFA784(u8 *p, u8 **end);

// Checks the RSA-2048 signature of a FIRM header with RSA key slot key. The 8-byte alignment of both buffers
// gives the dump's frame (sub sp, #0x12c with the digest pointer at sp+4).
u32 FUN_FFFF8C8C(FirmHeader *firm, u32 key)
{
    u32 equal = 1;
    __align(8) u8 hash[0x20];
    __align(8) u8 block[0x100];
    u8 *digest;
    if (firm == 0 || firm->magic != 0x4D524946) {
        return 0;
    }
    if (!FUN_FFFFAB50(0x800, firm->signature)) {
        return 0;
    }
    if (!FUN_FFFFA900(key, 0, 0)) {
        return 0;
    }
    FUN_FFFFAC60(firm, 0x100);
    FUN_FFFFACEC(hash);
    FUN_FFFFABCC();
    if (!FUN_FFFFA818(0x800, block)) {
        return 0;
    }
    digest = FUN_FFFFA7E0(block, 0x100);
    if (digest == 0) {
        return 0;
    }
    if (!FUN_FFFFA784(digest, &digest)) {
        return 0;
    }
    for (s32 i = 0; i < 0x20; i++) {
        equal &= (hash[i] == digest[i]);
    }
    return equal;
}
