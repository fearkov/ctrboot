#include "types.h"

struct Unk_FFF00150 {
    u8 unk00[0x10];
    u32 unk10;
};

extern struct Unk_FFF00150 DAT_FFF00150;

void FUN_FFFF5CF8(u32 value)
{
    DAT_FFF00150.unk10 = value;
}
