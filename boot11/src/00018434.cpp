#include "types.h"

struct Unk_10147020 {
    u16 unk0;
    u16 unk2;
};

extern volatile Unk_10147020 DAT_10147020;

void FUN_00018434(u32 bit, u32 enable)
{
    if (enable)
        DAT_10147020.unk0 |= 1 << bit;
    else
        DAT_10147020.unk0 &= ~(1 << bit);
}
