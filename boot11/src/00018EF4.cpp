#include "types.h"

struct Unk_10400400 {
    u8 pad0[0x68];
    u32 unk68[2];
    u8 pad70[8];
    u32 unk78;
    u8 pad7C[0x84];
};

struct Unk_1FFE805C {
    u8 pad0[0x14];
    u8 unk14;
};

extern volatile Unk_10400400 DAT_10400400[];
extern Unk_1FFE805C* DAT_1FFE805C[];

u32 FUN_00018EF4(u32 index)
{
    volatile Unk_10400400* regs = &DAT_10400400[index];
    Unk_1FFE805C* info = DAT_1FFE805C[index];
    u32 value = regs->unk68[0];
    if (info->unk14 != 0) {
        value = regs->unk68[~regs->unk78 & 1];
    }
    return value;
}
