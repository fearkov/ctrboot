#include "types.h"

struct Unk_10400400 {
    u8 pad0[0x24];
    u32 unk24;
    u8 pad28[0x50];
    u32 unk78;
    u8 pad7C[0x84];
};

struct Unk_1FFE805C {
    u8 pad0[4];
    u16 unk4;
    u16 unk6;
    u8 pad8[0xA];
    u8 unk12;
    u8 unk13;
};

extern "C" u32 FUN_00012834(s32 irq);
extern volatile Unk_10400400 DAT_10400400[];
extern Unk_1FFE805C* DAT_1FFE805C[];

void FUN_00018DD0(s32 index)
{
    volatile Unk_10400400* regs = &DAT_10400400[index];
    Unk_1FFE805C* state = DAT_1FFE805C[index];
    u32 total = state->unk4 + state->unk6;
    regs->unk78 |= 0x20000;
    if (state->unk13) {
        regs->unk78 ^= 1;
        state->unk13 = 0;
    }
    if (state->unk12) {
        regs->unk24 = total - 1;
        state->unk12 = 0;
    }
    FUN_00012834(index + 0x2A);
}
