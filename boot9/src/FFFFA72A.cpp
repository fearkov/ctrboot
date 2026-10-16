#include "types.h"

struct Unk_10000000 {
    u8 unk00[0x10];
    volatile u8 unk10;
};

void FUN_FFFFA72A(u32 value)
{
    volatile struct Unk_10000000 *reg = (volatile struct Unk_10000000 *)0x10000000;
    u32 old = reg->unk10;
    reg->unk10 = (value << 2) | (old & 0xf3);
}
