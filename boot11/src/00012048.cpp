// Handler of the timer 0 overflow interrupt (IRQ 0x1D, registered by FUN_00012738): counts the overflow in the 64-bit
// tick counter and, when the flag is set, restarts the timer and clears the flag.
// The halves are volatile and zero and one are locals of their own: that is what puts the high word first and the
// constants in front of the loads the way the dump has them (a plain u64 increment orders them the other way round).
#include "types.h"

struct Unk_1FFE80D0 {
    u16 unk0;
    u16 pad2;
    u32 unk4;
    volatile u32 lo;
    volatile u32 hi;
};

extern Unk_1FFE80D0 DAT_1FFE80D0;

extern "C" void FUN_000128E4(u32 index);
extern "C" void FUN_000128B8(u32 index, s32 load, u32 prescale);

void FUN_00012048()
{
    u32 zero = 0;
    u64 one = 1;
    u32 hi = DAT_1FFE80D0.hi;
    u32 lo = DAT_1FFE80D0.lo;
    u64 ticks = (((u64)hi << 32) | lo) + one;
    DAT_1FFE80D0.hi = (u32)(ticks >> 32);
    DAT_1FFE80D0.lo = (u32)ticks;
    if (DAT_1FFE80D0.unk4 != 0) {
        FUN_000128E4(0);
        FUN_000128B8(0, -1, 2);
        DAT_1FFE80D0.unk4 = zero;
    }
}
