// The acknowledge loop compares the ID field shifted to the top of the word against a local holding the spurious ID
// (0x3FF) in the same place: armcc loads such a local where it is declared, before the CPU interface pointer, as
// the dump does (a constant written in the loop condition is hoisted after the pointer).
#include "types.h"

struct Unk_1FFFFF80 {
    u32 unk0[9];
    void (*unk24)();
};

// The GIC CPU interface: control, priority mask, binary point, acknowledge, end of interrupt.
struct Unk_17E00100 {
    u32 unk0;
    u32 unk4;
    u32 unk8;
    u32 unkC;
    u32 unk10;
};

extern "C" u32 FUN_00011AC4();
extern "C" u32 FUN_00011AB0();
extern "C" void FUN_000120FC();
extern "C" void FUN_00012528(u32 *out);
extern "C" void FUN_000124B0(u32 *out);
extern "C" void FUN_00011D90();

extern u32 DAT_1FFE80E0;
extern Unk_1FFFFF80 DAT_1FFFFF80;
extern volatile u32 DAT_17E01000;
extern volatile Unk_17E00100 DAT_17E00100;

// Sets the interrupt controller up once: installs the IRQ handler, enables the distributor and the CPU interface,
// sends all 0x7E interrupts to core 0 at priority 0x80, makes them all edge-triggered, acknowledges whatever is
// pending, ends interrupts 0-15, then sets the priority mask to 0xF0 and the binary point to 3.
void FUN_0001267C()
{
    u32 saved[4];
    if (DAT_1FFE80E0 != 0)
        return;
    DAT_1FFE80E0 = 1;
    FUN_00011AC4();
    FUN_000120FC();
    DAT_1FFFFF80.unk24 = FUN_00011D90;
    DAT_17E01000 = 1;
    DAT_17E00100.unk0 = 1;
    u32 mask = 0;
    u32 count = 0x7E;
    for (u32 i = 0; i < count; i++) {
        *(volatile u8 *)(0x17E01800 + i) = 1;
        *(volatile u8 *)(0x17E01400 + i) = 0x80;
    }
    for (s32 i = 0; i < 0x20; i += 2)
        mask |= 3 << i;
    for (u32 i = 0; i < (count + 15) / 16; i++)
        *(volatile u32 *)(0x17E01C00 + i * 4) = mask;
    const u32 spurious = 0x3FFu << 22;
    volatile Unk_17E00100 *cpu = &DAT_17E00100;
    while ((cpu->unkC << 22) != spurious) {
    }
    for (s32 i = 0; i < 0x10; i++)
        cpu->unk10 = i;
    FUN_00012528(saved);
    FUN_000124B0(saved);
    cpu->unk4 = 0xF0;
    cpu->unk8 = 3;
    FUN_00011AB0();
}
