// Hook run just before the jump to the loaded entry point: with an entry point it calls FUN_000182F4, without one it
// prints the error screen (the error code and the four words after it, from 0x1FFFE00C).
// The error words are reached through a pointer built from their address, not through an extern object: knowing
// 0x1FFFE000, armcc loads it first and derives 0xFFFF from it (asrs r0, r4, #13), as the dump does. Passing 0xFFFF
// through a local gives the dump's order of the argument copies (r3, r2, r1).
#include "types.h"

struct Unk_1FFFE000 {
    u32 pad0[3];
    u32 unkC;
    u32 unk10;
    u32 unk14;
    u32 unk18;
    u32 unk1C;
};

extern "C" void FUN_000182F4(void);
extern "C" void FUN_00018C20(u32 a, u32 b, u32 c, u32 d);
extern "C" u32 FUN_00018FD8(void);
extern "C" void FUN_00018EBC(u32 flags);
extern "C" s32 FUN_0001901C(u32 x, u32 y, u32 color, const char* format, ...);
extern "C" void FUN_00018ED0(void);

void FUN_000181F4(u32 entry)
{
    if (entry != 0) {
        FUN_000182F4();
        return;
    }
    Unk_1FFFE000* error = (Unk_1FFFE000*)0x1FFFE000;
    u32 color = 0xFFFF00FF;
    u32 value = 0xFFFF;
    FUN_00018C20(value, value, value, value);
    FUN_00018FD8();
    FUN_00018EBC(3);
    FUN_0001901C(10, 10, color, "BOOTROM %X", 0x8046);
    FUN_0001901C(10, 18, color, "ERRCODE: %08X", error->unkC);
    FUN_0001901C(10, 24, color, "         %08X %08X", error->unk10, error->unk14);
    FUN_0001901C(10, 30, color, "         %08X %08X", error->unk18, error->unk1C);
    FUN_00018ED0();
}
