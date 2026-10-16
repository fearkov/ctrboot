#include "types.h"

struct Unk_FFF0009C {
    u8 pad0[4];
    u16 unk4;
    u8 pad6[2];
    u8 *unk8;
};

extern Unk_FFF0009C DAT_FFF0009C;

extern "C" void FUN_FFFF0344(u16 *src, u8 *dst, s32 size);

u32 FUN_FFFF2974(u16 *src)
{
    u8 *dst = DAT_FFF0009C.unk8;
    s32 size = DAT_FFF0009C.unk4;
    FUN_FFFF0344(src, dst, size);
    return 0;
}
