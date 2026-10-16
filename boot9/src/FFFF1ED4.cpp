#include "types.h"

struct Unk_10001000 {
    u32 unk0;
    u32 unk4;
};

extern Unk_10001000 DAT_10001000;

extern "C" u32 FUN_FFFF06EC();
extern "C" u32 FUN_FFFF0700(u32 state);

u32 FUN_FFFF1ED4(u32 bit)
{
    u32 state = FUN_FFFF06EC();
    u32 old = (DAT_10001000.unk4 >> bit) & 1;
    DAT_10001000.unk4 = 1u << bit;
    FUN_FFFF0700(state);
    return old;
}
