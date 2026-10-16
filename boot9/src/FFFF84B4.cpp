#include "types.h"

struct Unk_FFFF84B4_38
{
    u8 pad00[0x10];
    u32 unk10;
    u32 *unk14;
};

struct Unk_FFF016F0
{
    u8 pad00[0x2C];
    u32 unk2C;
    u8 pad30[8];
    Unk_FFFF84B4_38 unk38;
};

extern Unk_FFF016F0 DAT_FFF016F0;
extern s32 DAT_FFF00628;

extern "C" void FUN_FFFF25F0(void *dst, const void *src, u32 size);
extern "C" u32 FUN_FFFF3134(u32 x);
extern "C" void FUN_FFFF8678(u64 *block);
extern "C" void FUN_FFFF83E8(Unk_FFFF84B4_38 *s);

void FUN_FFFF84B4(u32 addr)
{
    u64 block;
    Unk_FFF016F0 *g = &DAT_FFF016F0;
    Unk_FFFF84B4_38 *s = &g->unk38;
    if (DAT_FFF00628 < 0) {
        *s->unk14 &= ~0x07000000u;
        *s->unk14 |= 0x01000000u;
    }
    block = (u64)((addr & ~0xFFFu) | 0x20000000u) << 32;
    FUN_FFFF25F0(s, &block, 8);
    g->unk2C = FUN_FFFF3134(*s->unk14);
    FUN_FFFF8678((u64 *)s);
    FUN_FFFF83E8(s);
    if (DAT_FFF00628 >= 0) {
        s->unk10 = 1;
    }
}
