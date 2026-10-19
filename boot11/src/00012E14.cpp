#include "types.h"

// The PXI registers: sync, control, send and receive.
struct Unk_10163000 {
    u32 unk0;
    u16 unk4;
    u16 unk6;
    u32 unk8;
    u32 unkC;
};

extern u16 DAT_1FFE8030;

extern "C" u32 FUN_00012564();
extern "C" void FUN_0001282C(u32 state);
extern "C" u32 FUN_00012EA8();
extern "C" void FUN_00012EB4(u32 value);

// Sets PXI up once: enables the sync interrupt and the FIFOs, then sends the sync byte 0xB and waits for the other
// side to answer 9.
void FUN_00012E14()
{
    u32 state = FUN_00012564();
    if (DAT_1FFE8030 == 0) {
        DAT_1FFE8030 = 1;
        // The registers are reached by absolute address, not through a DAT_ symbol: knowing 0x10163000, armcc forms
        // 0x80000000 from it with one shift (lsls r2, r0, #19).
        volatile Unk_10163000* pxi = (volatile Unk_10163000*)0x10163000;
        pxi->unk0 |= 0x80000000;
        pxi->unk4 = 0xC008;
        FUN_00012EB4(0xB);
        while (FUN_00012EA8() != 9) {
        }
    }
    FUN_0001282C(state);
}
