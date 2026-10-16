#include "types.h"

struct Unk_FFF001A8 {
    u8 unk0;
    u8 pad1[3];
    u8 *unk4;
    u32 unk8;
};

extern Unk_FFF001A8 DAT_FFF001A8;
extern u32 (*DAT_FFF000A8)();
extern u32 (*DAT_FFF000AC)(volatile u32 *fifo);
extern void (*DAT_FFF000B0)();

extern "C" u32 FUN_FFFF3AA0();
extern "C" u32 FUN_FFFF39D0(volatile u32 *fifo);
extern "C" void FUN_FFFF39C8();
extern "C" u32 FUN_FFFF2E38(u32 address, u32 count);
extern "C" void FUN_FFFFAC8C();

u32 FUN_FFFF3970(u8 cmd, u32 flag, u32 address, u32 count, u8 *buf)
{
    DAT_FFF001A8.unk0 = cmd;
    DAT_FFF001A8.unk4 = buf;
    DAT_FFF001A8.unk8 = count << 9;
    DAT_FFF000A8 = FUN_FFFF3AA0;
    DAT_FFF000AC = FUN_FFFF39D0;
    DAT_FFF000B0 = FUN_FFFF39C8;
    u32 ret = FUN_FFFF2E38(address, count);
    if (ret == 0 && flag) {
        FUN_FFFFAC8C();
    }
    return ret;
}
