#include "types.h"

struct Unk_FFF002E4 {
    u8 pad00[0x3C];
    u16 unk3C;
    u16 unk3E;
};

struct Unk_FFF0009C {
    u8 pad00[0x1C];
    u32 unk1C;
    u32 unk20;
    Unk_FFF002E4 *unk24;
};

extern "C" u32 FUN_FFFF06EC();
extern "C" void FUN_FFFF0700(u32 state);
extern "C" void FUN_FFFF5730(u32 id);
extern "C" void FUN_FFFF4CC4(u32 unit);
extern "C" void FUN_FFFF4ECC(u32 unit, u16 value);
extern "C" void FUN_FFFF4EDA(u32 unit, u16 value);
extern "C" void FUN_FFFF4D84(u32 unit, u32 mode);
extern Unk_FFF0009C DAT_FFF0009C;
extern Unk_FFF002E4 DAT_FFF002E4;

void FUN_FFFF5BBC()
{
    u32 state = FUN_FFFF06EC();
    FUN_FFFF5730(0x200);
    FUN_FFFF5730(0x201);
    FUN_FFFF4CC4(DAT_FFF0009C.unk1C);
    DAT_FFF0009C.unk20 = 0x201;
    DAT_FFF0009C.unk24 = &DAT_FFF002E4;
    FUN_FFFF4ECC(DAT_FFF0009C.unk1C, DAT_FFF0009C.unk24->unk3C);
    FUN_FFFF4EDA(DAT_FFF0009C.unk1C, DAT_FFF0009C.unk24->unk3E);
    FUN_FFFF4D84(DAT_FFF0009C.unk1C, 1);
    FUN_FFFF0700(state);
}
