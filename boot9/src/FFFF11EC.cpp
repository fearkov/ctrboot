#include "types.h"

struct Unk_10002000 {
    u8 unk0[0x10];
    volatile u32 unk10;
    u8 unk14[8];
};

extern volatile struct Unk_10002000 DAT_10002000[];

void FUN_FFFF11EC(u32 index, u32 value)
{
    DAT_10002000[index].unk10 = value;
}
