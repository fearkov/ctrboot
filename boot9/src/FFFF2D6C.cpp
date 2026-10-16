#include "types.h"

extern u32 DAT_FFF000B4;
extern u32 (*DAT_FFF000AC)(void);
extern u32 DAT_FFF000B8;
extern "C" u32 FUN_FFFF06EC(void);
extern "C" void FUN_FFFF0700(u32 state);
extern "C" void FUN_FFFF2954(void);
extern "C" void FUN_FFFF4896(u32 unit, u16 bits);
extern "C" void FUN_FFFF48CA(u32 unit, u16 bits);
extern "C" void FUN_FFFF48B4(u32 unit);
extern "C" void FUN_FFFF489E(u32 unit);
extern "C" void FUN_FFFF488E(u32 unit, u16 bits);

void FUN_FFFF2D6C(void)
{
    u32 state = FUN_FFFF06EC();
    DAT_FFF000B4 = 0;
    DAT_FFF000AC = 0;
    FUN_FFFF2954();
    FUN_FFFF4896(DAT_FFF000B8, 0x807F);
    FUN_FFFF48CA(DAT_FFF000B8, 4);
    FUN_FFFF48B4(DAT_FFF000B8);
    FUN_FFFF489E(DAT_FFF000B8);
    FUN_FFFF488E(DAT_FFF000B8, 0x300);
    FUN_FFFF0700(state);
}
