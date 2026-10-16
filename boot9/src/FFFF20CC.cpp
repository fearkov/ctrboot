#pragma O2
#pragma no_inline
#include "types.h"

struct Unk_10003000 {
    u16 unk0;
    u16 unk2;
};

extern u32 DAT_FFF00134;
extern volatile Unk_10003000 DAT_10003000[];

extern "C" u32 FUN_FFFF1F38();
extern "C" void FUN_FFFF2128(u32 state);

// One translation unit: armcc knows which registers FUN_FFFF21F8 leaves alone (FUN_FFFF20CC keeps
// a value in r3 across it) and that its callees need no stack alignment (it saves only lr).
void FUN_FFFF21E8(u32 index)
{
    DAT_10003000[index].unk2 = 0;
}

void FUN_FFFF21F8()
{
    FUN_FFFF21E8(3);
    FUN_FFFF21E8(2);
    FUN_FFFF21E8(1);
    FUN_FFFF21E8(0);
}

void FUN_FFFF20CC()
{
    if (DAT_FFF00134 == 0) {
        u32 state = FUN_FFFF1F38();
        DAT_FFF00134 = 1;
        FUN_FFFF21F8();
        FUN_FFFF2128(state);
    }
}
