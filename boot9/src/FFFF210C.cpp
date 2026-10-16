#include "types.h"

struct Unk_10001000 {
    u8 unk0[4];
    u32 unk4;
};

extern volatile Unk_10001000 DAT_10001000;

u32 FUN_FFFF210C(u32 bit)
{
    return (DAT_10001000.unk4 >> bit) & 1;
}
