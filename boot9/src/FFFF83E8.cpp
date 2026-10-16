#include "types.h"

struct Unk_FFF0064C
{
    u8 pad00[0x18];
    u32 unk18;
    u8 pad1C[0x38];
    u8 unk54[0x1048];
};

struct Unk_FFF01728
{
    u32 unk00;
    u32 unk04;
    u32 unk08;
    u32 unk0C;
    u32 unk10;
    u32 *unk14;
};

extern Unk_FFF0064C DAT_FFF0064C;

extern "C" void FUN_FFFF8438(void *ctx, u32 *xl, u32 *xr);
extern "C" void FUN_FFFF4740(Unk_FFF01728 *p);
extern "C" void FUN_FFFF0198(u32 count);

// The dump reaches the state at 0xFFF0064C and the word at 0xFFF00628 from one literal, the Blowfish context's
// address (subs #0x54, subs #0x78), as it does for variables of one section. Here the word is reached from the
// context's address and both come from the state's symbol, which gives that literal: separate symbols would each
// load their own.
void FUN_FFFF83E8(Unk_FFF01728 *p)
{
    void *ctx = DAT_FFF0064C.unk54;
    Unk_FFF0064C *state = &DAT_FFF0064C;
    s32 *flag = (s32 *)((u32)ctx - 0x78);
    p->unk00 = (state->unk18 & 0xFFFFF) | p->unk00;
    state->unk18++;
    FUN_FFFF8438(ctx, &p->unk04, &p->unk00);
    if (*flag < 0) {
        u32 *saved = p->unk14;
        p->unk14 = (u32 *)((u8 *)p + 0x40);
        FUN_FFFF4740(p);
        p->unk14 = saved;
        FUN_FFFF0198(0x3D5DB0);
    }
}
