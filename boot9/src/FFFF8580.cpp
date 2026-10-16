#include "types.h"

struct Unk_FFF0064C
{
    u8 pad00[0x14];
    u32 unk14;
    u32 unk18;
    u32 unk1C;
};

extern Unk_FFF0064C DAT_FFF0064C;

// ORs the low 16 bits of the field at 0xFFF00668 into bits 44-59 of the 64-bit block.
void FUN_FFFF8580(u64 *block)
{
    *block |= (u64)(DAT_FFF0064C.unk1C & 0xFFFF) << 44;
}
