#include "types.h"

struct Unk_FFF000E8 {
    u32 unk00;
    void (*unk04)();
    void (*unk08)(u32);
    void (*unk0c)(void *);
    void (*unk10)();
    u8 pad14[0x14];
    u32 unk28;
};

extern Unk_FFF000E8 DAT_FFF000E8;

extern "C" void FUN_FFFF9A08();
extern "C" void FUN_FFFF9A50(u32 arg);
extern "C" void FUN_FFFF9C9C(void *command);
extern "C" void FUN_FFFF98E8();

void FUN_FFFF96EC()
{
    DAT_FFF000E8.unk28 = 1;
    DAT_FFF000E8.unk04 = FUN_FFFF9A08;
    DAT_FFF000E8.unk08 = FUN_FFFF9A50;
    DAT_FFF000E8.unk0c = FUN_FFFF9C9C;
    DAT_FFF000E8.unk10 = FUN_FFFF98E8;
}
