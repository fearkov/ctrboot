#include "types.h"

struct Unk_10164000 {
    u8 unk0[4];
    volatile u32 unk4;
};
extern Unk_10164000 DAT_10164000;

void FUN_FFFF35A0()
{
    while ((s32)DAT_10164000.unk4 < 0) {}
}
