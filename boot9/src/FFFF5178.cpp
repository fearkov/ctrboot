#include "types.h"

struct Unk_FFF000C0
{
    u8 pad00[0x34];
    u32 unk34;
};

struct Unk_FFF0009C
{
    u8 pad00[0x24];
    Unk_FFF000C0 *unk24;
};

extern "C" u32 FUN_FFFF06EC();
extern "C" u32 FUN_FFFF0700(u32 state);
extern Unk_FFF0009C DAT_FFF0009C;

void FUN_FFFF5178(u32 bits)
{
    u32 state = FUN_FFFF06EC();
    DAT_FFF0009C.unk24->unk34 &= ~bits;
    FUN_FFFF0700(state);
}
