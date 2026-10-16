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

extern Unk_FFF0009C DAT_FFF0009C;
extern u8 DAT_FFF00250;
extern "C" void FUN_FFFF2920(u32 t);
extern "C" void FUN_FFFF1E40(void *timer);

extern "C" void FUN_FFFF556C(u32 a);
extern "C" void FUN_FFFF5440(u16 a);
extern "C" void FUN_FFFF4E38(u32 a, u32 b);

void FUN_FFFF4134(u32 a, u16 b)
{
    u32 v;
    switch (a) {
    case 0:
        v = 0;
        break;
    case 1:
        v = 1;
        break;
    default:
        return;
    }
    FUN_FFFF2920(1000);
    FUN_FFFF556C(a);
    if (DAT_FFF0009C.unk24->unk34 != 0) {
        FUN_FFFF1E40(&DAT_FFF00250);
        return;
    }
    FUN_FFFF5440(b);
    if (DAT_FFF0009C.unk24->unk34 != 0) {
        FUN_FFFF1E40(&DAT_FFF00250);
        return;
    }
    FUN_FFFF1E40(&DAT_FFF00250);
    FUN_FFFF4E38(DAT_FFF0009C.unk1C, v);
}
