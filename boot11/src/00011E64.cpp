// Switches the GPU's power and clock bits on (enable != 0) or off with interrupts masked, and returns the previous
// value of the flag at 0x1FFE80E4 that records which it is. Switching on sets the bit in the byte at +0x204 and the
// clock bit of the word at +0x200 of the controller, releases bit 0 of that word after a short wait when it was clear,
// then clears bits 8 to 11 of the GPU register at 0x10400030; switching off reverses it. The GPU register is read back
// once after each write.
#pragma arm
#include "types.h"

struct Unk_10141000 {
    u8 unk0[0x200];
    u32 unk200;
    u8 unk204;
};

struct Unk_10400000 {
    u8 unk0[0x30];
    u32 unk30;
};

extern "C" u32 FUN_00012564();
extern "C" void FUN_00011A38(u32 count);
extern "C" void FUN_0001282C(u32 state);

extern u32 DAT_1FFE80E4;

u32 FUN_00011E64(s32 enable)
{
    u32 state = FUN_00012564();
    u32 old = DAT_1FFE80E4;
    volatile Unk_10141000 *pdn = (volatile Unk_10141000 *)0x10141000;
    volatile Unk_10400000 *gpu = (volatile Unk_10400000 *)0x10400000;
    if (enable) {
        pdn->unk204 |= 1;
        pdn->unk200 |= 0x10000;
        if (!(pdn->unk200 & 1)) {
            FUN_00011A38(0x86);
            pdn->unk200 |= 1;
        }
        gpu->unk30 &= ~0xF00u;
        u32 readback = gpu->unk30;
        (void)readback;
        DAT_1FFE80E4 = 1;
    } else {
        gpu->unk30 |= 0xF00;
        u32 readback = gpu->unk30;
        (void)readback;
        pdn->unk200 &= ~0x10000u;
        pdn->unk204 &= ~1;
        DAT_1FFE80E4 = 0;
    }
    FUN_0001282C(state);
    return old;
}
