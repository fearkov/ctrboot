#include "types.h"

struct Unk_1FFE8338 {
    void (*unk0)(u32);
    u32 unk4;
    u32 unk8;
};

extern u16 DAT_1FFE80FC[];
extern Unk_1FFE8338 DAT_1FFE8338[];

extern "C" void FUN_00012834(u32 irq);
extern "C" void FUN_000124EC(u32 irq);

void FUN_0001215C(u32 index)
{
    u16 irq = DAT_1FFE80FC[index];
    void (*handler)(u32) = DAT_1FFE8338[index].unk0;
    u32 persistent = DAT_1FFE8338[index].unk4;
    DAT_1FFE8338[index].unk0 = 0;
    if (handler != 0)
        handler(DAT_1FFE8338[index].unk8);
    FUN_00012834(irq);
    if (persistent == 0)
        FUN_000124EC(irq);
}
