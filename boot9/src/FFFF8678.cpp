#include "types.h"

struct Unk_FFF0064C
{
    u8 pad00[0x14];
    u32 unk14;
    u32 unk18;
    u32 unk1C;
};

extern Unk_FFF0064C DAT_FFF0064C;

// ORs the low 24 bits of the field at 0xFFF00660 into bits 20-43 of the 64-bit block. The mask comes after the shift:
// masking the value first compiles to a different (equivalent) sequence of shifts.
void FUN_FFFF8678(u64 *block)
{
    *block |= ((u64)DAT_FFF0064C.unk14 << 20) & 0xFFFFFFFFFFFull;
}
