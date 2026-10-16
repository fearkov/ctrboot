#include "types.h"

// One entry of the table at DAT_FFF01990 (0x2C bytes each): how a DMA channel moves data.
struct Unk_FFF01990 {
    u8 pad00[0x1c];
    u8 unk1c;
    u8 pad1d[0xf];
};

// The two instruction words handed to the controller below: the first one's upper bytes are filled in place.
struct Unk_FFF00190 {
    u32 unk00;
    u32 unk04;
};

struct Unk_1000C000 {
    u8 pad00[0x20];
    u32 unk20;
    u8 pad24[8];
    u32 unk2c;
};

struct Unk_1000CD00 {
    u32 unk00;
    u32 unk04;
    u32 unk08;
    u32 unk0c;
};

extern Unk_FFF01990 DAT_FFF01990[];
extern Unk_FFF00190 DAT_FFF00190;
extern volatile Unk_1000C000 DAT_1000C000;
extern volatile Unk_1000CD00 DAT_1000CD00;

extern "C" void FUN_FFFF08A8(const void *addr, u32 size);
extern "C" u32 FUN_FFFF1F38();
extern "C" u32 FUN_FFFF1ED4(u32 bit);
extern "C" u32 FUN_FFFF1BCC();
extern "C" void FUN_FFFF2128(u32 state);

// Writes the channel's program back from the data cache and starts it at program. The interrupt number is a local that
// armcc keeps in a stack slot: state declared first takes the slot above it, and declaring the number between config
// and bit schedules its mov between the two halves of 1 << index.
void FUN_FFFF1424(s32 index, u8 *program, u32 length)
{
    u32 state;
    Unk_FFF01990 *config = &DAT_FFF01990[index];
    u32 irq = 0x1C;
    u32 bit = 1 << index;
    u8 *inst = (u8 *)&DAT_FFF00190;

    FUN_FFFF08A8(program, length + 0x20);
    state = FUN_FFFF1F38();
    DAT_1000C000.unk20 |= bit;
    DAT_1000C000.unk2c |= bit;
    if (config->unk1c == 0) {
        DAT_1000C000.unk20 &= ~bit;
    }
    FUN_FFFF1ED4(irq);
    while (FUN_FFFF1BCC() != 0) {
    }
    DAT_FFF00190.unk00 = 0;
    DAT_FFF00190.unk04 = (u32)program;
    inst[2] = 0xA2;
    inst[3] = index;
    DAT_1000CD00.unk08 = DAT_FFF00190.unk00;
    DAT_1000CD00.unk0c = DAT_FFF00190.unk04;
    DAT_1000CD00.unk04 = 0;
    FUN_FFFF2128(state);
}
