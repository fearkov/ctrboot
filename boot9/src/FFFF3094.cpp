#include "types.h"

struct Unk_10164000 {
    volatile u16 unk0;
    u8 pad2[2];
    volatile s32 unk4;
};

extern Unk_10164000 DAT_10164000;

extern "C" u32 FUN_FFFF1F38();
extern "C" void FUN_FFFF2128(u32 state);

void FUN_FFFF3094()
{
    u32 state = FUN_FFFF1F38();
    while (DAT_10164000.unk4 < 0) {
    }
    DAT_10164000.unk0 |= 0xC000;
    FUN_FFFF2128(state);
}
