#include "types.h"

struct Unk_1000C100 {
    u32 unk00;
    u32 unk04;
};

// Low four bits of the first word of the 8-byte register pair of this index. The base is an absolute address: with an
// extern array armcc would index it with a register offset instead of adding first.
u32 FUN_FFFF1A9C(u32 index)
{
    return ((volatile Unk_1000C100 *)0x1000C100)[index].unk00 & 0xF;
}
