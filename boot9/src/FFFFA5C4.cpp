#include "types.h"

struct Unk_10000000 {
    u8 unk00[0x10];
    volatile u8 unk10;
};

u32 FUN_FFFFA5C4()
{
    volatile struct Unk_10000000 *reg = (volatile struct Unk_10000000 *)0x10000000;
    return (reg->unk10 & 0xf) >> 2;
}
