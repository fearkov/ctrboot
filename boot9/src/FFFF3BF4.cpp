#include "types.h"

struct Unk_FFF000C0 {
    u8 pad00[0x30];
    u16 unk30;
    u8 pad32[2];
    u32 unk34;
    u32 unk38;
};

struct Unk_FFF0009C {
    u8 pad00[0x14];
    void (*unk14)();
    u32 unk18;
    u32 unk1C;
    u32 unk20;
    Unk_FFF000C0 *unk24;
};

extern Unk_FFF0009C DAT_FFF0009C;
extern u8 DAT_FFF00250;

extern "C" void FUN_FFFF2D6C();
extern "C" u32 FUN_FFFF06EC();
extern "C" void FUN_FFFF0700(u32 state);
extern "C" void FUN_FFFF4820(u32 unit, u16 value);
extern "C" void FUN_FFFF2920(u32 time);
extern "C" u32 FUN_FFFF4A86(u32 unit);
extern "C" void FUN_FFFF47F4(u32 unit);
extern "C" void FUN_FFFF1E40(void *timer);
extern "C" void FUN_FFFF54F0();
extern "C" void FUN_FFFF5440(u16 rca);

// Recovers the card after a failed command: runs the pending completion callback, resets the controller's
// interrupt state, waits for the busy card to finish, then reissues the reset commands. The error bits in
// unk34 and the last response in unk38 are kept across the recovery; returns the low half of the error bits.
u16 FUN_FFFF3BF4()
{
    u32 state;
    u32 response;
    u32 error;
    if (DAT_FFF0009C.unk24->unk34 & 0x800000) {
        FUN_FFFF2D6C();
    }
    if (DAT_FFF0009C.unk14) {
        DAT_FFF0009C.unk14();
        DAT_FFF0009C.unk14 = 0;
    }
    state = FUN_FFFF06EC();
    response = DAT_FFF0009C.unk24->unk38;
    error = DAT_FFF0009C.unk24->unk34;
    DAT_FFF0009C.unk24->unk34 = 0;
    FUN_FFFF4820(DAT_FFF0009C.unk1C, 0x807F);
    FUN_FFFF0700(state);
    FUN_FFFF2920(500);
    if (FUN_FFFF4A86(DAT_FFF0009C.unk1C)) {
        FUN_FFFF47F4(DAT_FFF0009C.unk1C);
        while (FUN_FFFF4A86(DAT_FFF0009C.unk1C)) {
            if (DAT_FFF0009C.unk24->unk34) {
                break;
            }
        }
    }
    FUN_FFFF1E40(&DAT_FFF00250);
    for (s32 i = 0; i < 3; i++) {
        DAT_FFF0009C.unk24->unk34 = 0;
        FUN_FFFF2920(500);
        FUN_FFFF54F0();
        FUN_FFFF1E40(&DAT_FFF00250);
    }
    DAT_FFF0009C.unk24->unk34 = 0;
    FUN_FFFF2920(500);
    FUN_FFFF5440(DAT_FFF0009C.unk24->unk30);
    FUN_FFFF1E40(&DAT_FFF00250);
    DAT_FFF0009C.unk24->unk34 = error;
    DAT_FFF0009C.unk24->unk38 = response;
    return DAT_FFF0009C.unk24->unk34;
}
