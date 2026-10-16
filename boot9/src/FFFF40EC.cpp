#include "types.h"

struct Unk_FFF000C0 {
    u8 pad00[0x3C];
    u16 unk3C;
    u16 unk3E;
};

struct Unk_FFF0009C {
    u8 pad00[0x1C];
    u32 unk1C;
    u32 unk20;
    Unk_FFF000C0 *unk24;
};

struct Unk_07FFCD80 {
    u8 pad00[0x5C];
    u32 unk5C;
    u32 unk60;
};

extern Unk_FFF0009C DAT_FFF0009C;
extern Unk_07FFCD80 DAT_07FFCD80;

extern "C" void FUN_FFFF4CA4(u32 unit, u16 *out);
extern "C" void FUN_FFFF4CB4(u32 unit, u16 *out);
extern "C" void FUN_FFFF05E0(const void *src, void *dst, u32 size);

// Saves the controller's clock and option registers into the card state, copies its first 0x64 bytes to
// 0x07FFCD80 with the unit, and records whether the unit is another than 0x200.
u32 FUN_FFFF40EC()
{
    Unk_07FFCD80 *out = &DAT_07FFCD80;
    Unk_FFF0009C *g = &DAT_FFF0009C;
    FUN_FFFF4CA4(g->unk1C, &g->unk24->unk3C);
    FUN_FFFF4CB4(g->unk1C, &g->unk24->unk3E);
    FUN_FFFF05E0(g->unk24, out, 0x64);
    out->unk5C = g->unk1C;
    u32 other;
    if (g->unk20 == 0x200) {
        other = 0;
    } else {
        other = 1;
    }
    out->unk60 = other;
    return 0;
}
