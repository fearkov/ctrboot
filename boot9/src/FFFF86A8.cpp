#include "types.h"

struct Unk_FFF0064C
{
    u8 pad00[0x14];
    u32 unk14;
    u32 unk18;
    u32 unk1C;
};

extern Unk_FFF0064C DAT_FFF0064C;

// ORs the field at 0xFFF00664 into the low word of the block, then shifts the field right by 8.
void FUN_FFFF86A8(u32 *block)
{
    block[0] = DAT_FFF0064C.unk18 | block[0];
    DAT_FFF0064C.unk18 = DAT_FFF0064C.unk18 >> 8;
}
