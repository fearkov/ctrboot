#include "types.h"

struct Unk_FFF001A8 {
    u8 unk0;
    u8 pad1[3];
    void *unk4;
    u32 unk8;
};

extern Unk_FFF001A8 DAT_FFF001A8;
extern u32 DAT_FFF000A8;
extern u32 DAT_FFF000AC;
extern u32 DAT_FFF000B0;
extern u32 DAT_FFF00158;

extern "C" void FUN_FFFF08A8(void *buf, u32 size);
extern "C" u32 FUN_FFFF2E38(u32 a, u32 count);
extern "C" u32 FUN_FFFF1BA8(u32 handle);
extern "C" void FUN_FFFF3F70();
extern u8 DAT_FFFF3FA0;
extern "C" void FUN_FFFF5CAC(u32 bits);
extern "C" void FUN_FFFFAC8C();

u32 FUN_FFFF3EDC(u8 cmd, u32 flag, u32 arg, u32 count, void *buf)
{
    Unk_FFF001A8 *g = &DAT_FFF001A8;
    u32 size = count << 9;
    g->unk0 = cmd;
    FUN_FFFF08A8(buf, size);
    g->unk4 = buf;
    g->unk8 = size;
    DAT_FFF000A8 = (u32)&DAT_FFFF3FA0 + 1;
    DAT_FFF000AC = 0;
    DAT_FFF000B0 = (u32)FUN_FFFF3F70;
    u32 ret = FUN_FFFF2E38(arg, count);
    if (ret == 0) {
        u32 i = 0;
        while (FUN_FFFF1BA8(DAT_FFF00158) != 0) {
            if (++i > 0x28E970) {
                FUN_FFFF3F70();
                FUN_FFFF5CAC(ret = 0x4000);
                break;
            }
        }
        if (ret == 0 && flag) {
            FUN_FFFFAC8C();
        }
    }
    return ret;
}
