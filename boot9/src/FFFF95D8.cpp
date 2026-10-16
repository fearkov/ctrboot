#include "types.h"

struct Unk_FFF000C8 {
    u8 pad00[4];
    u32 (*unk4)(void *, u32, u32);
    u8 pad08[0xC];
    void *unk14;
};
extern Unk_FFF000C8 DAT_FFF000C8;
extern u32 DAT_07FFBB00[];

extern "C" void FUN_FFFF898C(u32 a);
extern "C" void FUN_FFFF95BC(void *p, u32 n);
extern "C" u32 FUN_FFFF8C8C(void *p, u32 b);
extern "C" u32 FUN_FFFFA408(void *p, u32 a);

s32 FUN_FFFF95D8(u32 a, u32 b)
{
    u32 *buf = DAT_07FFBB00;
    DAT_FFF000C8.unk14 = 0;
    FUN_FFFF898C(6);
    FUN_FFFF95BC(buf, 0x200);
    if (!DAT_FFF000C8.unk4(buf, a, 0x200)) return -0x21;
    if (buf[0] != 0x4D524946) return -8;
    if (!FUN_FFFF8C8C(buf, b)) return -0x22;
    if (!FUN_FFFFA408(buf, a)) return -0x31;
    DAT_FFF000C8.unk14 = buf;
    return 0;
}
