#include "types.h"

struct Unk_FFF01728 {
    u32 unk00;
    u32 unk04;
    u32 unk08;
    u32 unk0c;
    u32 unk10;
    u32 *unk14;
};

extern s32 DAT_FFF00628;

extern "C" void FUN_FFFF8580(Unk_FFF01728 *p);
extern "C" void FUN_FFFF83E8(Unk_FFF01728 *p);
extern "C" void FUN_FFFF4740(Unk_FFF01728 *p);

void FUN_FFFF9C9C(Unk_FFF01728 *p)
{
    FUN_FFFF8580(p);
    FUN_FFFF83E8(p);
    if (DAT_FFF00628 >= 0) {
        *p->unk14 |= 0x10000000;
    }
    FUN_FFFF4740(p);
}
