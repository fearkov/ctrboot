// Unlike the rest of the ROM, built for speed: -Ospace gives other code.
#pragma Otime
#include "types.h"

struct Unk_FFF000C0
{
    u8 pad00[0x34];
    u32 unk34;
};

struct Unk_FFF0009C
{
    u8 pad00[0x1C];
    u32 unk1C;
    u8 pad20[4];
    Unk_FFF000C0 *unk24;
};

struct Unk_FFF00250
{
    u32 unk0;
};

extern Unk_FFF0009C DAT_FFF0009C;
extern u8 DAT_FFF00388[];
extern Unk_FFF00250 DAT_FFF00250;

extern "C" void FUN_FFFF4244(u32 mode, u8 *status);
extern "C" u32 FUN_FFFF5A96(u8 *status);
extern "C" bool FUN_FFFF5A48(u8 *status);
extern "C" bool FUN_FFFF5A74(u8 *status);
extern "C" u16 FUN_FFFF5684(u8 *status);
extern "C" void FUN_FFFF5178(u32 bits);
extern "C" void FUN_FFFF2920(u32 time);
extern "C" void FUN_FFFF5204();
extern "C" void FUN_FFFF5334(u16 rca, u8 *out);
extern "C" void FUN_FFFF52FC(u16 rca);
extern "C" void FUN_FFFF1E40(Unk_FFF00250 *timer);
extern "C" void FUN_FFFF19D4(u64 value);
extern "C" void FUN_FFFF4EB8(u32 unit);
extern "C" void FUN_FFFF5CE6(u32 unit, u8 *csd);
extern "C" void FUN_FFFF4EA4(u32 unit);

// Switches the card to high speed when it supports it and draws no more than 200 mA there,
// then reads its CSD again, selects it and sets the clock from the CSD.
void FUN_FFFF4398(u16 rca, u8 *csd)
{
    FUN_FFFF4244(0, DAT_FFF00388);
    if (DAT_FFF0009C.unk24->unk34 != 0)
    {
        FUN_FFFF5178(~0x200);
        return;
    }
    if (!FUN_FFFF5A96(DAT_FFF00388))
    {
        return;
    }
    FUN_FFFF4244(2, DAT_FFF00388);
    if (DAT_FFF0009C.unk24->unk34 != 0)
    {
        FUN_FFFF5178(~0x200);
        return;
    }
    if (!FUN_FFFF5A48(DAT_FFF00388) || FUN_FFFF5684(DAT_FFF00388) > 200)
    {
        return;
    }
    FUN_FFFF4244(3, DAT_FFF00388);
    if (DAT_FFF0009C.unk24->unk34 != 0)
    {
        FUN_FFFF5178(~0x200);
        return;
    }
    if (!FUN_FFFF5A74(DAT_FFF00388))
    {
        return;
    }
    FUN_FFFF2920(1500);
    FUN_FFFF5204();
    if (DAT_FFF0009C.unk24->unk34 != 0)
    {
        FUN_FFFF1E40(&DAT_FFF00250);
        return;
    }
    FUN_FFFF5334(rca, csd);
    if (DAT_FFF0009C.unk24->unk34 != 0)
    {
        FUN_FFFF1E40(&DAT_FFF00250);
        return;
    }
    FUN_FFFF52FC(rca);
    if (DAT_FFF0009C.unk24->unk34 != 0)
    {
        FUN_FFFF1E40(&DAT_FFF00250);
        return;
    }
    FUN_FFFF1E40(&DAT_FFF00250);
    FUN_FFFF19D4(62);
    FUN_FFFF4EB8(DAT_FFF0009C.unk1C);
    FUN_FFFF5CE6(DAT_FFF0009C.unk1C, csd);
    FUN_FFFF4EA4(DAT_FFF0009C.unk1C);
}
