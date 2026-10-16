#include "types.h"

struct Unk_FFF002E4 {
    u8 pad00[0x34];
    u32 unk34;
    u8 pad38[0x14];
    u32 unk4C;
    u32 unk50;
};

struct Unk_FFF0009C {
    u8 pad00[0x20];
    u32 unk20;
    Unk_FFF002E4 *unk24;
};

extern "C" u32 FUN_FFFF5C10(u32 id);
extern "C" u32 FUN_FFFF5A2C(u32 id);
extern "C" void FUN_FFFF19D4(u64 value);
extern "C" u32 FUN_FFFF2988();
extern "C" void FUN_FFFF40EC();
extern Unk_FFF0009C DAT_FFF0009C;

u32 FUN_FFFF5774(u32 id)
{
    u32 result = FUN_FFFF5C10(id);
    if (result != 0) {
        return result;
    }
    if (DAT_FFF0009C.unk20 == 0x200 && FUN_FFFF5A2C(DAT_FFF0009C.unk20) == 0) {
        FUN_FFFF19D4(32000);
    }
    if (FUN_FFFF5A2C(id) == 0) {
        DAT_FFF0009C.unk24->unk34 = 1 << 21;
        return 1 << 21;
    }
    for (s32 i = 0; i < 10; i++) {
        u32 status = FUN_FFFF2988();
        if (status == 0 || ((status << 21) >> 30) != 0) {
            break;
        }
        Unk_FFF002E4 *e = DAT_FFF0009C.unk24;
        e->unk4C++;
        e->unk50 |= status;
    }
    if (id == 0x201 && DAT_FFF0009C.unk24->unk34 == 0) {
        FUN_FFFF40EC();
    }
    return DAT_FFF0009C.unk24->unk34;
}
