#include "types.h"

struct Unk_10010000 {
    u8 unk00[0x10];
    volatile u8 unk10;
};
extern Unk_10010000 DAT_10010000;

extern u32 DAT_FFFFD730[4];
extern u32 DAT_FFFFD750[4];

extern "C" void FUN_FFFF8C80();
extern "C" void FUN_FFFF89E4();
extern "C" void FUN_FFFF8AA0(u32 slot, u32 mode, const u32 *key);
extern "C" void FUN_FFFF898C(u32 slot);
extern "C" void FUN_FFFF8A64(u32 mode, const u32 *data);

void FUN_FFFFA050(u32 a, u32 b, u32 c)
{
    u32 data[4];
    FUN_FFFF8C80();
    FUN_FFFF89E4();
    FUN_FFFF8AA0(0x3F, 5, DAT_10010000.unk10 == 0 ? DAT_FFFFD730 : DAT_FFFFD750);
    FUN_FFFF8C80();
    FUN_FFFF898C(0x3F);
    data[0] = b;
    data[1] = a;
    data[2] = c;
    data[3] = c;
    FUN_FFFF8A64(5, data);
}
