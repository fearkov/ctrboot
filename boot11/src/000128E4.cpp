#include "types.h"

struct Unk_17E00600 {
    u32 unk0;
    u32 unk4;
    u32 unk8;
    u32 unkC;
    u8 unk10[0x10];
};

extern volatile Unk_17E00600 DAT_17E00600[];

void FUN_000128E4(s32 index)
{
    DAT_17E00600[index].unk8 = 0;
    DAT_17E00600[index].unkC = 1;
}
