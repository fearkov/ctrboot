// Handler of the timer 0 overflow interrupt (IRQ 8, registered by FUN_FFFF2064): counts the overflow in the 64-bit
// tick counter (read by FUN_FFFF1F70) and, when the flag is set, restarts the timer and clears the flag.
// As in boot11's twin FUN_00012048 the halves are volatile and zero and one are locals of their own, which puts the
// high word first; zero is a u64 here, which is what puts it in front of the one on the ARM9.
#include "types.h"

struct Unk_FFF00048 {
    u16 unk00;
    u16 pad02;
    u32 unk04;
    volatile u32 lo;
    volatile u32 hi;
};

extern Unk_FFF00048 DAT_FFF00048;

void FUN_FFFF1664()
{
    u64 zero = 0;
    u64 one = 1;
    u32 hi = DAT_FFF00048.hi;
    u32 lo = DAT_FFF00048.lo;
    u64 ticks = (((u64)hi << 32) | lo) + one;
    DAT_FFF00048.hi = (u32)(ticks >> 32);
    DAT_FFF00048.lo = (u32)ticks;
    if (DAT_FFF00048.unk04 != 0) {
        u16 *regs = (u16 *)0x10003000;
        regs[0] = (u16)zero;
        regs[1] = 0xc1;
        DAT_FFF00048.unk04 = (u32)zero;
    }
}
