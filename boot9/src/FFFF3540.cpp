#include "types.h"

struct Unk_10164000 {
    volatile u16 unk0;
};
extern Unk_10164000 DAT_10164000;

extern "C" u32 FUN_FFFF1F38();
extern "C" void FUN_FFFF2128(u32 state);

void FUN_FFFF3540()
{
    u32 state = FUN_FFFF1F38();
    DAT_10164000.unk0 &= ~0x2000;
    FUN_FFFF2128(state);
}
