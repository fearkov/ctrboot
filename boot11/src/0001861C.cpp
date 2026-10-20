// FUN_00018870 and FUN_000184CC are in this file with FUN_0001861C: armcc then knows that the two read functions use
// only r0 and r1, and FUN_000184CC keeps 0x3FF in r2 across its second FUN_0001861C call, and 0x20000 and 0x10000 in
// r2 and r3 across its second FUN_00018870 call, as the dump does. In FUN_000184CC, the (void)0 keeps the case 0 and
// case 4 labels: written right on default, armcc folds them into it and compiles the four cases left as compares,
// where the dump has the __ARM_common_switch8 table.
#include "types.h"

struct Unk_10202240 {
    u32 unk0;
    u32 unk4;
};

extern "C" u32 FUN_00018F20();
extern "C" void FUN_00018C64(u32 value);
extern "C" u32 FUN_00018F6C(u32 flags);
extern "C" void FUN_0001919C(u32 flags, u32 arg);
extern "C" u32 FUN_000186EE(u32 which);
extern "C" void FUN_0001225C(u64 ms);
extern "C" u32 FUN_00018E60(s32 index);
extern "C" bool FUN_00013A90(u32 flag);
extern volatile Unk_10202240 DAT_10202240;
extern volatile Unk_10202240 DAT_10202A40;
extern volatile u32 DAT_10202200;
extern volatile u32 DAT_10202A00;

// Returns the low half of 0x10202240 when bit 0 of which is set, else of 0x10202A40 when bit 1 is, else 0xFFFF.
u32 FUN_0001861C(u32 which)
{
    volatile u32* reg;
    if (which & 1) {
        reg = &DAT_10202240.unk0;
    } else if (which & 2) {
        reg = &DAT_10202A40.unk0;
    } else {
        return 0xFFFF;
    }
    return (u16)*reg;
}

// Returns bit 0 of 0x10202200 when bit 0 of which is set, else of 0x10202A00 when bit 1 is, else 0.
u32 FUN_00018870(u32 which)
{
    volatile u32* reg;
    if (which & 1) {
        reg = &DAT_10202200;
    } else if (which & 2) {
        reg = &DAT_10202A00;
    } else {
        return 0;
    }
    return *reg & 1;
}

// Returns 0 when FUN_00018F20 returns 2 or 3, and 1 at once when it returns 1 or 5. Otherwise sets 0x1FFE8054 to 5,
// sets both screens to 0xAC through FUN_0001919C when either reads 0x3FF or FUN_00018F6C differs between them (else
// to the first one's value), waits up to ten times 17 ms for FUN_000186EE(3), sets bit 16 at 0x10202244 and
// 0x10202A44, with bit 17 where FUN_00018870 is set, and returns 1.
u32 FUN_000184CC()
{
    switch (FUN_00018F20()) {
    case 1:
    case 5:
        break;
    case 2:
    case 3:
        return 0;
    case 0:
    case 4:
        (void)0;
    default:
        FUN_00018C64(5);
        if (FUN_0001861C(1) == 0x3FF || FUN_0001861C(2) == 0x3FF || FUN_00018F6C(1) != FUN_00018F6C(2)) {
            FUN_0001919C(3, 0xAC);
        } else {
            u32 value = FUN_00018F6C(1);
            FUN_0001919C(1, value);
            FUN_0001919C(2, value);
        }
        for (int i = 0; i < 10; i++) {
            if (FUN_000186EE(3))
                break;
            FUN_0001225C(17);
        }
        FUN_00018E60(0);
        FUN_00018E60(1);
        DAT_10202240.unk4 |= 0x10000 | (FUN_00018870(1) ? 0x20000 : 0);
        DAT_10202A40.unk4 |= 0x10000 | (FUN_00018870(2) ? 0x20000 : 0);
        FUN_00013A90(1);
        break;
    }
    return 1;
}
