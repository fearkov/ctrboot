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

struct Unk_FFFF5A8A
{
    u8 unk00[0xc4];
    u8 unkC4;
};

struct Unk_FFFF5CD0
{
    u8 pad00[0xc4];
    u8 unkC4;
};

extern Unk_FFF0009C DAT_FFF0009C;
extern u8 DAT_FFF00250;
extern Unk_FFFF5A8A DAT_FFF003C8;

extern "C" void FUN_FFFF1E40(void *timer);
extern "C" void FUN_FFFF2920(u32 t);
extern "C" void FUN_FFFF3D08(void *p);
extern "C" bool FUN_FFFF5A8A(Unk_FFFF5A8A *p);
extern "C" void FUN_FFFF55B4(u32 a);
extern "C" void FUN_FFFF5440(u16 a);
extern "C" void FUN_FFFF5178(u32 a);
extern "C" void FUN_FFFF19D4(u64 a);
extern "C" void FUN_FFFF4EB8(u32 a);
extern "C" void FUN_FFFF5CD0(u32 a, Unk_FFFF5A8A *p);
extern "C" void FUN_FFFF4EA4(u32 a);

void FUN_FFFF4308(u16 a)
{
    FUN_FFFF3D08(&DAT_FFF003C8);
    if (DAT_FFF0009C.unk24->unk34 != 0) {
        FUN_FFFF5178(~0x200u);
        return;
    }
    if (!FUN_FFFF5A8A(&DAT_FFF003C8)) {
        return;
    }
    FUN_FFFF2920(1000);
    FUN_FFFF55B4(1);
    if (DAT_FFF0009C.unk24->unk34 != 0) {
        FUN_FFFF5178(~0x200u);
        FUN_FFFF1E40(&DAT_FFF00250);
        return;
    }
    FUN_FFFF5440(a);
    if (DAT_FFF0009C.unk24->unk34 != 0) {
        FUN_FFFF5178(~0x200u);
        FUN_FFFF1E40(&DAT_FFF00250);
        return;
    }
    FUN_FFFF1E40(&DAT_FFF00250);
    FUN_FFFF19D4(0x3E);
    FUN_FFFF4EB8(DAT_FFF0009C.unk1C);
    FUN_FFFF5CD0(DAT_FFF0009C.unk1C, &DAT_FFF003C8);
    FUN_FFFF4EA4(DAT_FFF0009C.unk1C);
}
