#include "types.h"

struct Unk_FFFF8C8C
{
    u32 magic;
    u8 pad04[0xFC];
    u8 unk100[0x100];
};

extern "C" u32 FUN_FFFFAB50(u32 bits, const void *sig);
extern "C" u32 FUN_FFFFA900(u32 a, u32 b, u32 c);
extern "C" void FUN_FFFFAC60(const void *data, u32 size);
extern "C" void FUN_FFFFACEC(u8 *hash);
extern "C" void FUN_FFFFABCC();
extern "C" u32 FUN_FFFFA818(s32 bits, u8 *dst);
extern "C" u8 *FUN_FFFFA7E0(u8 *p, s32 len);
extern "C" u32 FUN_FFFFA784(u8 *p, u8 **out);

u32 FUN_FFFF8C8C(Unk_FFFF8C8C *firm, u32 key)
{
    u32 ok = 1;
    __align(8) u8 hash[0x20];
    __align(8) u8 sig[0x100];
    u8 *p;
    if (firm == 0 || firm->magic != 0x4D524946) {
        return 0;
    }
    if (!FUN_FFFFAB50(0x800, firm->unk100)) {
        return 0;
    }
    if (!FUN_FFFFA900(key, 0, 0)) {
        return 0;
    }
    FUN_FFFFAC60(firm, 0x100);
    FUN_FFFFACEC(hash);
    FUN_FFFFABCC();
    if (!FUN_FFFFA818(0x800, sig)) {
        return 0;
    }
    p = FUN_FFFFA7E0(sig, 0x100);
    if (p == 0) {
        return 0;
    }
    if (!FUN_FFFFA784(p, &p)) {
        return 0;
    }
    for (s32 i = 0; i < 0x20; i++) {
        ok &= (hash[i] == p[i]);
    }
    return ok;
}
