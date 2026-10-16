#include "types.h"

struct Unk_FFF016F0_20 {
    u8 unk0[0x10];
    volatile u8 unk10;
    u8 unk11;
};

struct Unk_FFF016F0 {
    u8 unk0[0x20];
    Unk_FFF016F0_20 unk20;
    u8 unk32[0xE];
    u32 unk40;
};
extern Unk_FFF016F0 DAT_FFF016F0;

extern "C" void FUN_FFFF35C0(u32 n);

void FUN_FFFF35D8()
{
    Unk_FFF016F0 *g = &DAT_FFF016F0;
    Unk_FFF016F0_20 *s = &g->unk20;
    if (s->unk11) {
        while (!s->unk10) {}
    }
    s->unk10 = 0;
    s->unk11 = 0;
    FUN_FFFF35C0(g->unk40);
}
