// Built for space like the rest of the SD/MMC driver around it: only -Ospace keeps the address argument
// in the pushed r0 slot and merges the two calls of FUN_FFFF2920 and the "FUN_FFFF3BF4(); return" tails.
#include "types.h"

struct Unk_FFF000C0 {
    u8 pad00[3];
    u8 unk3;
    u8 pad04[0x2C];
    u16 unk30;
    u8 pad32[2];
    u32 unk34;
    u32 unk38;
};

struct Unk_FFF0009C {
    volatile u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
    u8 pad04[8];
    u32 (*unkC)(volatile u32 *fifo);
    u32 (*unk10)(u8 *dst);
    void (*unk14)();
    u32 unk18;
    u32 unk1C;
    u32 unk20;
    Unk_FFF000C0 *unk24;
};

extern Unk_FFF0009C DAT_FFF0009C;
extern u8 DAT_FFF00250;

extern "C" u32 FUN_FFFF06EC();
extern "C" void FUN_FFFF0700(u32 state);
extern "C" void FUN_FFFF493C(u32 unit);
extern "C" void FUN_FFFF4E84(u32 unit, u16 first, u16 second);
extern "C" void FUN_FFFF4DB0(u32 unit, u32 mode);
extern "C" void FUN_FFFF490A(u32 unit, u32 value);
extern "C" volatile u32 *FUN_FFFF4984(u32 unit);
extern "C" void FUN_FFFF5CAC(u32 bits);
extern "C" void FUN_FFFF2920(u32 time);
extern "C" void FUN_FFFF5278(u32 address, u32 block);
extern "C" void FUN_FFFF3BF4();
extern "C" void FUN_FFFF5440(u16 rca);
extern "C" void FUN_FFFF1E40(void *timer);

// Starts a transfer of count 512-byte blocks at address: programs the controller, lets the callback at
// unkC prepare the FIFO, issues the command and waits for the interrupt handler to clear unk0, then
// waits for the card to return to the transfer state (CURRENT_STATE 4). Returns the error bits.
u32 FUN_FFFF2E38(u32 address, u32 count)
{
    u32 state = FUN_FFFF06EC();
    if (DAT_FFF0009C.unk3) {
        DAT_FFF0009C.unk24->unk34 = 0x800000;
        FUN_FFFF0700(state);
        return DAT_FFF0009C.unk24->unk34;
    }
    DAT_FFF0009C.unk24->unk34 = 0;
    if (DAT_FFF0009C.unk10) {
        FUN_FFFF493C(DAT_FFF0009C.unk1C);
    }
    FUN_FFFF4E84(DAT_FFF0009C.unk1C, 0x200, count);
    FUN_FFFF4DB0(DAT_FFF0009C.unk1C, 0);
    FUN_FFFF490A(DAT_FFF0009C.unk1C, count);
    DAT_FFF0009C.unk18 = count;
    FUN_FFFF0700(state);
    if (DAT_FFF0009C.unkC) {
        u32 error = DAT_FFF0009C.unkC(FUN_FFFF4984(DAT_FFF0009C.unk1C));
        if (error) {
            FUN_FFFF5CAC(error);
            return DAT_FFF0009C.unk24->unk34;
        }
    }
    state = FUN_FFFF06EC();
    if (DAT_FFF0009C.unk3 || DAT_FFF0009C.unk24->unk34) {
        FUN_FFFF0700(state);
        DAT_FFF0009C.unk14();
        DAT_FFF0009C.unk14 = 0;
        return DAT_FFF0009C.unk24->unk34;
    }
    DAT_FFF0009C.unk1 = 1;
    DAT_FFF0009C.unk0 = 1;
    FUN_FFFF0700(state);
    if (DAT_FFF0009C.unk10) {
        FUN_FFFF2920(650);
    } else {
        FUN_FFFF2920(2000);
    }
    FUN_FFFF5278(address, DAT_FFF0009C.unk24->unk3);
    while (DAT_FFF0009C.unk0) {
    }
    if (DAT_FFF0009C.unk24->unk34 != 0) {
        FUN_FFFF3BF4();
        return DAT_FFF0009C.unk24->unk34;
    }
    FUN_FFFF2920(500);
    FUN_FFFF5440(DAT_FFF0009C.unk24->unk30);
    FUN_FFFF1E40(&DAT_FFF00250);
    if (DAT_FFF0009C.unk24->unk34 == 0 && ((DAT_FFF0009C.unk24->unk38 >> 9) & 0xF) != 4) {
        FUN_FFFF5CAC(0x80);
        FUN_FFFF3BF4();
        return DAT_FFF0009C.unk24->unk34;
    }
    return DAT_FFF0009C.unk24->unk34;
}
