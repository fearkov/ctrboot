#include "types.h"

struct Unk_FFF01728 {
    u8 unk0[8];
    u32 unk8;
    u8 unkC[8];
    u32 *unk14;
    u8 unk18[0xC8];
    u32 unkE0;
};
extern Unk_FFF01728 DAT_FFF01728;

extern "C" u32 FUN_FFFF3134(u32 x);
extern "C" void FUN_FFFF3250(u32 a, u32 b, u32 size, Unk_FFF01728 *p);
extern "C" void FUN_FFFF35C0(u32 x);

void FUN_FFFF46CC(u32 a, u32 b, s32 size)
{
    Unk_FFF01728 *p = &DAT_FFF01728;
    p->unk14 = &p->unkE0;
    s32 left = size;
    u32 chunk = FUN_FFFF3134(*p->unk14);
    while (left > 0) {
        FUN_FFFF3250(a, b, chunk, p);
        a += chunk;
        b += chunk;
        left -= chunk;
    }
    FUN_FFFF35C0(p->unk8);
}
