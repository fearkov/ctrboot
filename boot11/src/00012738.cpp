// Initializes the tick counter (the timer 0 interrupt, IRQ 0x1D, handled by FUN_00012048) once: zeroes the 64-bit
// count, starts the timer, snapshots the performance monitor counters on core 0 and enables the interrupt.
// The counters are reached through a pointer taken before the call that tests the core: that makes armcc load the
// address first, where the dump does.
#include "types.h"

struct Unk_1FFE80D0 {
    u16 unk0;
    u16 pad2;
    u32 unk4;
    u8 unk8[8];
};

struct Unk_1FFFE000 {
    u32 unk0;
    u32 unk4;
    u32 unk8;
};

typedef void (*Handler)();

extern Unk_1FFE80D0 DAT_1FFE80D0;
extern Unk_1FFFE000 DAT_1FFFE000;

extern "C" void *FUN_00013254(void *dst, const void *src, u32 size);
extern "C" u32 FUN_000124EC(s32 irq);
extern "C" void FUN_0001267C();
extern "C" void FUN_000127C8();
extern "C" void FUN_00012250(u32 index);
extern "C" void FUN_000128E4(s32 index);
extern "C" void FUN_000125C8(u32 index);
extern "C" void FUN_000128B8(s32 index, u32 load, u32 period);
extern "C" u32 FUN_00011A18();
extern "C" u32 FUN_00011A54(s32 counter);
extern "C" void FUN_00012048();
extern "C" void FUN_00012870(u32 irq, Handler handler);
extern "C" u32 FUN_00012590(u32 irq);

void FUN_00012738()
{
    if (DAT_1FFE80D0.unk0 == 0) {
        DAT_1FFE80D0.unk0 = 1;
        FUN_000124EC(0x1d);
        FUN_0001267C();
        FUN_000127C8();
        FUN_00013254(DAT_1FFE80D0.unk8, "\0\0\0\0\0\0\0", 8);
        FUN_00012250(0);
        FUN_000128E4(0);
        FUN_000125C8(0);
        FUN_000128B8(0, -1, 2);
        Unk_1FFFE000 *counters = &DAT_1FFFE000;
        if (FUN_00011A18() == 0 && counters->unk0 == 0) {
            counters->unk0 = FUN_00011A54(0);
            counters->unk4 = FUN_00011A54(1);
            counters->unk8 = FUN_00011A54(2);
        }
        FUN_00012870(0x1d, FUN_00012048);
        FUN_00012590(0x1d);
        DAT_1FFE80D0.unk4 = 0;
    }
}
