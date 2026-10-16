#include "types.h"

struct Unk_10164000 {
    u8 unk0[4];
    volatile u32 unk4;
};
extern Unk_10164000 DAT_10164000;

void FUN_FFFF355C(const u32 *flags)
{
    DAT_10164000.unk4 = flags[0] | flags[2] | flags[3];
}
