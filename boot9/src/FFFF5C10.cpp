#include "types.h"

struct Unk_FFF00280 {
    u8 pad00[0x3C];
    u16 unk3C;
    u16 unk3E;
    u8 pad40[0x24];
};

struct Unk_FFF0009C {
    u8 pad00[0x1C];
    u32 unk1C;
    u32 unk20;
    Unk_FFF00280 *unk24;
};

extern "C" u32 FUN_FFFF06EC();
extern "C" void FUN_FFFF0700(u32 state);
extern "C" u32 FUN_FFFF4998(u32 unit);
extern "C" void FUN_FFFF4CA4(u32 unit, u16 *out);
extern "C" void FUN_FFFF4CB4(u32 unit, u16 *out);
extern "C" void FUN_FFFF19D4(u64 value);
extern "C" void FUN_FFFF4EB8(u32 unit);
extern "C" void FUN_FFFF4ECC(u32 unit, u16 value);
extern "C" void FUN_FFFF4EDA(u32 unit, u16 value);
extern "C" void FUN_FFFF4D84(u32 unit, u32 mode);
extern Unk_FFF0009C DAT_FFF0009C;

// Switches the card controller to unit id (0x200 or 0x201, its low byte the port): saves the clock and option
// registers into the current unit's state, then loads the new unit's. The two states are named by their fixed
// addresses: armcc then loads the shared literal in each branch as the ROM does (with a DAT_ symbol it hoists it).
u32 FUN_FFFF5C10(u32 id)
{
    Unk_FFF0009C *g = &DAT_FFF0009C;
    u32 cur = g->unk20;
    if (id == cur) {
        return 0;
    }
    u32 count = FUN_FFFF4998(g->unk1C);
    u32 slot = id;
    if (count == 0 || *(u8 *)&slot > count) {
        return 1 << 24;
    }
    FUN_FFFF4CA4(g->unk1C, &g->unk24->unk3C);
    FUN_FFFF4CB4(g->unk1C, &g->unk24->unk3E);
    FUN_FFFF19D4(0x3E);
    FUN_FFFF4EB8(g->unk1C);
    u32 state = FUN_FFFF06EC();
    g->unk20 = id;
    Unk_FFF00280 *ctx;
    if (id == 0x200) {
        ctx = (Unk_FFF00280 *)0xFFF00280;
    } else {
        ctx = (Unk_FFF00280 *)0xFFF002E4;
    }
    g->unk24 = ctx;
    FUN_FFFF4ECC(g->unk1C, g->unk24->unk3C);
    FUN_FFFF4EDA(g->unk1C, g->unk24->unk3E);
    u32 mode;
    if (g->unk20 == 0x200) {
        mode = 0;
    } else {
        mode = 1;
    }
    FUN_FFFF4D84(g->unk1C, mode);
    FUN_FFFF0700(state);
    return 0;
}
