// Starts DMA channel id on the microcode at buffer: cleans the buffer from the data cache, sets the channel's bit in the
// controller's interrupt registers (and takes it out of the enable register again when the channel's table entry asks
// for no interrupt), then issues a DMAGO (0xA2) through the debug instruction registers once the debug interface is idle.
// The locals are declared in this order because it decides the order of the early computations and which stack slot
// each spilled local gets.
#include "types.h"

struct Unk_1FFE83C0 {
    u8 unk0[0x1C];
    u8 unk1C;
    u8 unk1D[0xF];
};

struct Unk_1FFE8118 {
    u32 unk0;
    u32 unk4;
};

struct Unk_10200D00 {
    u32 unk0;
    u32 unk4;
    u32 unk8;
    u32 unkC;
};

extern Unk_1FFE83C0 DAT_1FFE83C0[];
extern Unk_1FFE8118 DAT_1FFE8118;

extern "C" void FUN_00011398(const void *start, u32 size);
extern "C" u32 FUN_00012564();
extern "C" u32 FUN_00012474(s32 irq);
extern "C" u32 FUN_00012404();
extern "C" void FUN_0001282C(u32 state);

void FUN_00011F74(u32 id, u8 *buffer, u32 size)
{
    u32 state;
    Unk_1FFE83C0 *channel = &DAT_1FFE83C0[id];
    u32 irq = id + 0x30;
    u32 mask = 1 << id;
    u8 *bytes = (u8 *)&DAT_1FFE8118;
    FUN_00011398(buffer, size + 0x20);
    state = FUN_00012564();
    volatile u32 *regs = (volatile u32 *)0x10200000;
    regs[8] |= mask;
    regs[11] |= mask;
    if (channel->unk1C == 0)
        regs[8] &= ~mask;
    FUN_00012474(irq);
    while (FUN_00012404() != 0) {
    }
    DAT_1FFE8118.unk0 = 0;
    DAT_1FFE8118.unk4 = (u32)buffer;
    bytes[2] = 0xA2;
    bytes[3] = id;
    volatile Unk_10200D00 *dma = (volatile Unk_10200D00 *)0x10200D00;
    dma->unk8 = DAT_1FFE8118.unk0;
    dma->unkC = DAT_1FFE8118.unk4;
    dma->unk4 = 0;
    FUN_0001282C(state);
}
