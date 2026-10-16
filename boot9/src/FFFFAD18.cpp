// Built for space: room for the 16 bytes of outgoing stack arguments comes from pushing r0-r3 along
// with r4 (-Otime allocates it with sub sp).
#pragma Ospace
#include "types.h"

extern "C" void FUN_FFFFADF4(u32 a, u32 b, u32 c, u32 d, u32 e, u32 f, u32 g, u32 h);

struct Unk_FFF00240 {
    u16 unk0;
    u8 unk2;
    u8 unk3;
    u8 unk4;
    u8 unk5;
    u8 unk6;
    u8 unk7;
    u8 unk8;
    u8 unk9;
};
extern Unk_FFF00240 DAT_FFF00240;

void FUN_FFFFAD18()
{
    DAT_FFF00240.unk0 = 8;
    DAT_FFF00240.unk2 = 1;
    DAT_FFF00240.unk4 = 2;
    DAT_FFF00240.unk5 = 3;
    DAT_FFF00240.unk6 = 0x40;
    DAT_FFF00240.unk7 = 0x40;
    DAT_FFF00240.unk8 = 6;
    DAT_FFF00240.unk9 = 7;
    FUN_FFFFADF4(3, 7, 3, 7, 3, 7, 3, 7);
}
