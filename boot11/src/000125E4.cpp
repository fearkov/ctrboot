// Three details here only steer armcc's scheduling and register allocation (found with a permuter, then reduced):
// the count is read into a signed local, so that ~count widens by sign extension (the read then lands in r1); the
// u64 counter is zeroed where it is declared (that zero stays in r6 for the increment's high word); and the copy's
// size is a reference bound to a temporary, which puts the 8 in r2 before the read. A plain 8 or u32 local schedules
// it after the read or swaps r5 and r6.
#include "types.h"

// The MPCore private timer and watchdog, 0x20 bytes apart.
struct Unk_17E00600 {
    u32 unk0;
    u32 unk4;
    u32 unk8;
    u32 unkC;
    u8 unk10[0x10];
};

// The tick count FUN_00012738 zeroes and the timer interrupt handler FUN_00012048 advances.
struct Unk_1FFE80D0 {
    u16 unk0;
    u16 pad2;
    u32 unk4;
    u8 unk8[8];
};

extern volatile Unk_17E00600 DAT_17E00600[];
extern Unk_1FFE80D0 DAT_1FFE80D0;

extern "C" u32 FUN_00012564();
extern "C" void FUN_0001282C(u32 state);
extern "C" u32 FUN_00012808(s32 irq);
extern "C" void *FUN_00013254(void *dst, const void *src, u32 size);

// Reads the 64-bit tick count: the overflow count of the timer (kept by the interrupt handler FUN_00012048) in the
// high word and the time since the last overflow, the timer counting down from 0xFFFFFFFF, in the low word. When the
// overflow interrupt is pending but not yet handled (and the counter has just wrapped), it counts that overflow too.
u64 FUN_000125E4()
{
    u32 state = FUN_00012564();
    u64 ticks;
    u64 counter = 0;
    const u32 &size = sizeof(ticks);
    s32 count = DAT_17E00600[0].unk4;
    counter = ~count;
    FUN_00013254(&ticks, DAT_1FFE80D0.unk8, size);
    if (FUN_00012808(0x1d) != 0 && (counter & 0x80000000) == 0) {
        ticks++;
    }
    ticks <<= 32;
    FUN_0001282C(state);
    return (u32)counter | ticks;
}
