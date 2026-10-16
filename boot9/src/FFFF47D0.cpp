#include "types.h"

struct Unk_FFF016F0 {
    u8 unk0[0x40];
    u32 unk40;
    u32 unk44;
};
extern Unk_FFF016F0 DAT_FFF016F0;

extern "C" void FUN_FFFF35D8();
extern "C" u32 FUN_FFFF1F38();
extern "C" void FUN_FFFF1F10(u32 irq);
extern "C" void FUN_FFFF2128(u32 state);

void FUN_FFFF47D0()
{
    FUN_FFFF35D8();
    Unk_FFF016F0 *p = &DAT_FFF016F0;
    u32 state = FUN_FFFF1F38();
    p->unk40 = p->unk44;
    FUN_FFFF1F10(0x1B);
    FUN_FFFF2128(state);
}
