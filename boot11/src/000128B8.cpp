#include "types.h"

struct Unk_17E00600 {
    u32 unk0;
    u32 unk4;
    u32 unk8;
    u32 unkC;
    u8 unk10[0x10];
};

extern volatile Unk_17E00600 DAT_17E00600[];
extern u8 DAT_1FFE80CA[];

void FUN_000128B8(s32 index, u32 load, u32 period)
{
    u32 prescaler = period >> 1;
    if (prescaler != 0)
        prescaler = (prescaler - 1) & 0xFF;
    volatile Unk_17E00600* timers = DAT_17E00600;
    volatile Unk_17E00600* timer = timers + index;
    timer->unk0 = load;
    timer->unk8 = DAT_1FFE80CA[index] | (prescaler << 8) | 5;
}
