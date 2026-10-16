#include "types.h"

struct Unk_FFF016F0 {
    u8 unk0[0x20];
    u32 unk20;
    u32 unk24;
    u32 unk28;
};
extern Unk_FFF016F0 DAT_FFF016F0;

extern "C" u32 FUN_FFFF46C0();
extern "C" u32 FUN_FFFF34B4(u32 a, s32 b, s32 c);
extern "C" void FUN_FFFF46CC(u32 a, u32 b, s32 size);
extern "C" u32 FUN_FFFF34E0();

void FUN_FFFF470C(u32 a, s32 b, s32 c)
{
    Unk_FFF016F0 *p = &DAT_FFF016F0;
    if (FUN_FFFF46C0() && FUN_FFFF34B4(a, b, c)) {
        FUN_FFFF46CC(p->unk20, p->unk24, p->unk28);
        FUN_FFFF34E0();
    }
}
