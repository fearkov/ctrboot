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
    u32 unk14;
    u32 unk18;
    u32 unk1C;
    u32 unk20;
    Unk_FFF000C0 *unk24;
};

extern Unk_FFF0009C DAT_FFF0009C;
extern u8 DAT_FFF00250;

extern "C" void FUN_FFFF2920(u32 time);
extern "C" void FUN_FFFF51CC(u16 rca);
extern "C" void FUN_FFFF1E40(void *timer);
extern "C" u32 FUN_FFFF06EC();
extern "C" void FUN_FFFF0700(u32 state);
extern "C" void FUN_FFFF4DB0(u32 unit, u32 b);
extern "C" void FUN_FFFF4E1C(u32 unit, u16 size);
extern "C" void FUN_FFFF52E0();
extern "C" void FUN_FFFF3BF4();
extern "C" u32 FUN_FFFF2974(u16 *src);

// Reads the 64-byte SD status into status: the application command for the card at rca, then one 0x40-byte
// block through the FIFO copy callback, waiting for the busy flag and recovering the card on an error.
// unk18 is set first: that order puts the constants where the image has them.
void FUN_FFFF3E28(u16 rca, u8 *status)
{
    FUN_FFFF2920(0x1F4);
    FUN_FFFF51CC(rca);
    FUN_FFFF1E40(&DAT_FFF00250);
    if (!DAT_FFF0009C.unk24->unk34) {
        u32 state = FUN_FFFF06EC();
        FUN_FFFF4DB0(DAT_FFF0009C.unk1C, 1);
        DAT_FFF0009C.unk8 = status;
        FUN_FFFF4E1C(DAT_FFF0009C.unk1C, DAT_FFF0009C.unk4 = 0x40);
        DAT_FFF0009C.unk18 = 1;
        DAT_FFF0009C.unkC = 0;
        DAT_FFF0009C.unk10 = FUN_FFFF2974;
        DAT_FFF0009C.unk14 = 0;
        DAT_FFF0009C.unk1 = 1;
        DAT_FFF0009C.unk0 = 1;
        FUN_FFFF0700(state);
        FUN_FFFF2920(0x28A);
        FUN_FFFF52E0();
        while (DAT_FFF0009C.unk0) {
        }
        if (DAT_FFF0009C.unk24->unk34) {
            FUN_FFFF3BF4();
        }
        FUN_FFFF4E1C(DAT_FFF0009C.unk1C, 0x200);
    }
}
