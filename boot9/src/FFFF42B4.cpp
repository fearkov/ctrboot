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

extern "C" void FUN_FFFF51CC(u16 a);
extern "C" void FUN_FFFF54A8(u32 a);
extern "C" void FUN_FFFF5440(u16 a);
extern "C" void FUN_FFFF5178(u32 a);

void FUN_FFFF42B4(u16 a)
{
    FUN_FFFF2920(0x5DC);
    FUN_FFFF51CC(a);
    if (DAT_FFF0009C.unk24->unk34 == 0) {
        FUN_FFFF54A8(0);
        if (DAT_FFF0009C.unk24->unk34 != 0) {
            FUN_FFFF5178(~0x200u);
        } else {
            FUN_FFFF5440(a);
            if (DAT_FFF0009C.unk24->unk34 != 0) {
                FUN_FFFF5178(~0x200u);
            }
        }
    }
    FUN_FFFF1E40(&DAT_FFF00250);
}
