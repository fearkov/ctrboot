// States 1 and 2 store their own state back (p->unkC = state), which armcc drops only after register allocation:
// state 1 keeps its load of a, and in state 2 b stays live past the or, so the or goes into a's register and the
// zero stored gets a register of its own, as in the dump. Without these stores armcc ors into r1 and stores that
// as the zero. Named directly instead of through p, DAT_1FFE8048 goes to r1 and the stored value to r0.
#include "types.h"

struct Unk_1FFE8048 {
    u32 unk0;
    u32 unk4;
    u32 unk8;
    u32 unkC;
};

extern "C" bool FUN_00013A26(u32 *flag);
extern "C" u32 FUN_000139B0(u32 *flag);
extern Unk_1FFE8048 DAT_1FFE8048;

// Reads two flags from MCU register 0x0F (FUN_00013A26: bit 7; FUN_000139B0: bits 5 and 6) and moves the state at
// 0x1FFE8054 on: 2 becomes 0 when both are clear, 5 becomes 1 when both are set. Returns the state.
u32 FUN_00018F20()
{
    u32 a;
    u32 b;
    if (FUN_00013A26(&a))
        FUN_000139B0(&b);
    Unk_1FFE8048 *p = &DAT_1FFE8048;
    u32 state = p->unkC;
    switch (state) {
    case 1:
        if (a)
            p->unkC = state;
        break;
    case 2:
        if (!a && !b)
            p->unkC = 0;
        else if (!b)
            p->unkC = state;
        break;
    case 3:
    case 4:
        break;
    case 5:
        if (a && b)
            p->unkC = 1;
        break;
    }
    return p->unkC;
}
