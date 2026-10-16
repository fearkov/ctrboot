#include "types.h"

struct Unk_FFF00048 {
    u16 unk00;
    u16 pad02;
    u32 unk04;
    u8 unk08[8];
};

struct Unk_10003000 {
    u16 unk0;
    u16 unk2;
};

typedef void (*Handler)();

extern Unk_FFF00048 DAT_FFF00048;
extern "C" void *FUN_FFFF25F0(void *dst, const void *src, u32 size);
extern "C" void FUN_FFFF1F10(u32 irq);
extern "C" void FUN_FFFF2028();
extern "C" void FUN_FFFF20CC();
extern "C" void FUN_FFFF19C8(u32 index);
extern "C" void FUN_FFFF21AC(u32 irq, Handler handler);
extern "C" u32 FUN_FFFF1F40(u32 bit);
extern "C" void FUN_FFFF1664();

void FUN_FFFF2064()
{
    if (DAT_FFF00048.unk00 == 0) {
        DAT_FFF00048.unk00 = 1;
        FUN_FFFF1F10(8);
        FUN_FFFF2028();
        FUN_FFFF20CC();
        FUN_FFFF25F0(DAT_FFF00048.unk08, "\0\0\0\0\0\0\0", 8);
        FUN_FFFF19C8(0);
        u16 *regs = (u16 *)0x10003000;
        regs[0] = 0;
        regs[1] = 0xc1;
        u16 *second = (u16 *)0x10003000 + 6;
        second[0] = 0;
        second[1] = 0xc3;
        FUN_FFFF21AC(8, FUN_FFFF1664);
        FUN_FFFF1F40(8);
        DAT_FFF00048.unk04 = 0;
    }
}
