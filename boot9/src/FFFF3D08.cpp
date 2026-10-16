#include "types.h"

struct Unk_FFF000C0 {
    u8 pad00[0x34];
    u32 unk34;
};

struct Unk_FFF0009C {
    volatile u8 unk0;
    u8 unk1;
    u8 pad2[2];
    u16 unk4;
    u8 pad6[2];
    u8 *unk8;
    u32 unkC;
    u32 (*unk10)(u16 *);
    void (*unk14)();
    u32 unk18;
    u32 unk1C;
    u32 unk20;
    Unk_FFF000C0 *unk24;
};

extern Unk_FFF0009C DAT_FFF0009C;

extern "C" u32 FUN_FFFF06EC();
extern "C" void FUN_FFFF0700(u32 state);
extern "C" void FUN_FFFF4DB0(u32 unit, u32 b);
extern "C" void FUN_FFFF4E1C(u32 unit, u16 size);
extern "C" void FUN_FFFF2920(u32 time);
extern "C" void FUN_FFFF536C();
extern "C" u16 FUN_FFFF3BF4();
extern "C" u32 FUN_FFFF2974(u16 *src);

// Reads one 512-byte data block into buf: sets up the transfer (the FIFO copy callback, one block), issues the
// command, waits for the busy flag to clear and recovers the card on an error.
void FUN_FFFF3D08(u8 *buf)
{
    u32 state = FUN_FFFF06EC();
    FUN_FFFF4DB0(DAT_FFF0009C.unk1C, 1);
    DAT_FFF0009C.unk8 = buf;
    DAT_FFF0009C.unk4 = 0x200;
    FUN_FFFF4E1C(DAT_FFF0009C.unk1C, 0x200);
    DAT_FFF0009C.unk18 = 1;
    DAT_FFF0009C.unkC = 0;
    DAT_FFF0009C.unk10 = FUN_FFFF2974;
    DAT_FFF0009C.unk14 = 0;
    DAT_FFF0009C.unk1 = 1;
    DAT_FFF0009C.unk0 = 1;
    FUN_FFFF0700(state);
    FUN_FFFF2920(0x28A);
    FUN_FFFF536C();
    while (DAT_FFF0009C.unk0) {
    }
    if (DAT_FFF0009C.unk24->unk34) {
        FUN_FFFF3BF4();
    }
    FUN_FFFF4E1C(DAT_FFF0009C.unk1C, 0x200);
}
