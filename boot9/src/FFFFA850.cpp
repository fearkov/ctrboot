#include "types.h"

// The handler at 0xFFFF9D28 is not in boot9.functions: reached by its address, with the Thumb bit.
extern u8 DAT_FFFF9D28;
extern "C" void FUN_FFFF21AC(u32 irq, void (*handler)());

struct Unk_1000B0C0 {
    u8 unk00[0x30];
    volatile u32 unk30;
};
extern Unk_1000B0C0 DAT_1000B0C0;

struct Unk_FFF0007C {
    u8 unk0[8];
    u32 unk8;
};
extern Unk_FFF0007C DAT_FFF0007C;

void FUN_FFFFA850()
{
    DAT_1000B0C0.unk30 = 0;
    FUN_FFFF21AC(0x16, (void (*)())((u32)&DAT_FFFF9D28 + 1));
    DAT_FFF0007C.unk8 = 1;
}
