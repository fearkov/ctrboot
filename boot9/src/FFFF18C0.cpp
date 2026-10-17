#include "types.h"

struct Unk_FFF01838 {
    void (*unk00)(u32);
    u32 unk04;
    u32 unk08;
};

extern Unk_FFF01838 DAT_FFF01838[];
extern "C" u32 FUN_FFFF2184(u32 bit);

// Runs the handler in this slot once: the slot is cleared before the call.
static inline void RunHandler(u32 index)
{
    void (*handler)(u32) = DAT_FFF01838[index].unk00;
    DAT_FFF01838[index].unk00 = 0;
    if (handler != 0) {
        handler(DAT_FFF01838[index].unk08);
    }
}

// The XDMA interrupt (0x1C): acknowledges each pending event of the four channels and runs its handler (slots 14-17).
// The interrupt number is a local that armcc keeps in a stack slot. The handler part is an inline function and the bit
// a local computed before the status read: written in place, or with 1 << i inside the test, armcc keeps the register
// block's address in a register and loads 0 or 1 inside the loop instead of the address.
void FUN_FFFF18C0()
{
    u32 irq = 0x1C;
    for (s32 i = 0; i < 4; i++) {
        u32 bit = 1 << i;
        if (*(volatile u32 *)0x1000C028 & bit) {
            *(volatile u32 *)0x1000C02C = bit;
            RunHandler(i + 14);
        }
    }
    FUN_FFFF2184(irq);
}
