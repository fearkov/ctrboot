// Two lines here only steer armcc's register allocation, as a permuter found: the alias assigned inside the first
// FUN_00018CA4 call and the bottomHeight++/-- pair after the first copy. Without either, registers come out swapped
// against the dump.
#include "types.h"

struct Unk_1FFE8064 {
    u32 unk0;
    u16 unk4;
    u16 unk6;
    u8 pad8[0x10];
    u32 unk18;
    u32 unk1C;
};

struct Unk_1FFE805C {
    Unk_1FFE8064 *unk0[2];
    Unk_1FFE8064 unk8;
};

struct Unk_1FFE8058 {
    u32 unk0;
    Unk_1FFE805C unk4;
};

struct Unk_10141200 {
    u32 unk0;
    u8 unk4;
    u8 pad5[3];
    u8 unk8;
};

struct Unk_10400440 {
    u8 pad0[0xC];
    u32 unkC;
    u8 pad10[0x24];
    u32 unk34;
    u32 unk38;
};

extern "C" void FUN_00011A38(u32 count);
extern "C" void FUN_000116E4(u32 value, u32 start, u32 size);
extern "C" void FUN_00011398(u32 start, s32 size);
extern "C" void FUN_00018CA4(u32 index, Unk_1FFE8064 *state, u32 width, u32 height, u32 x, u32 y);
extern "C" void FUN_00018C2C(u32 n, u32 value);
extern "C" void FUN_00018E26();
extern "C" void FUN_00018E1C();

extern Unk_1FFE8058 DAT_1FFE8058;
extern u32 DAT_1FFE8130[];
extern volatile Unk_10141200 DAT_10141200;
extern volatile Unk_10400440 DAT_10400440;
extern volatile Unk_10400440 DAT_10400540;

// Sets the screens up, once: turns the GPU on, puts the top screen's two framebuffers at 0x18000000 and 0x18300000 and
// the bottom screen's right after them, fills them from the four images DAT_1FFE8130 points at, configures both LCDs
// with FUN_00018CA4 and hands FUN_00018E26 and FUN_00018E1C to FUN_00018C2C.
void FUN_0001871C(Unk_1FFE8064 *top)
{
    Unk_1FFE8064 *alias;
    u32 *init = &DAT_1FFE8058.unk0;
    if (*init == 0) {
        *init = 1;
        Unk_1FFE805C *s = &DAT_1FFE8058.unk4;
        s->unk0[1] = &s->unk8;
        s->unk0[0] = top;
        Unk_1FFE8064 *bottom = &s->unk8;
        Unk_1FFE8064 *screen = s->unk0[1];
        DAT_10141200.unk4 |= 1;
        DAT_10141200.unk0 |= 0x10000;
        FUN_00011A38(0x86);
        DAT_10141200.unk0 |= 0x1007F;
        DAT_10141200.unk8 |= 1;
        *(volatile u32 *)0x10400004 |= 0x300;
        u32 heights[2] = { top->unk4, bottom->unk4 };
        u32 topHeight = heights[0];
        u32 bottomHeight = heights[1];
        u32 dummy = *(volatile u32 *)0x18000000;
        (void)dummy;
        u32 size = 240 * topHeight;
        size *= 4;
        top->unk18 = 0x18000000;
        top->unk1C = 0x18300000;
        FUN_000116E4(DAT_1FFE8130[0], 0x18000000, size);
        bottomHeight++;
        bottomHeight--;
        FUN_00011398(0x18000000, size);
        FUN_000116E4(DAT_1FFE8130[1], 0x18300000, size);
        FUN_00011398(0x18300000, size);
        FUN_00018CA4(0, alias = top, 240, topHeight, 0, 0);
        u32 offset = (size + 0xFFF) & ~0xFFF;
        u32 left = offset + 0x18000000;
        u32 right = offset + 0x18300000;
        size = 240 * bottomHeight;
        size *= 4;
        screen->unk18 = left;
        screen->unk1C = right;
        FUN_000116E4(DAT_1FFE8130[2], left, size);
        FUN_00011398(left, size);
        FUN_000116E4(DAT_1FFE8130[3], right, size);
        FUN_00011398(right, size);
        FUN_00018CA4(1, screen, 240, bottomHeight, 0, 0);
        DAT_10400440.unkC = 0xFF00;
        DAT_10400540.unkC = 0xFF;
        FUN_00018C2C(0, (u32)FUN_00018E26);
        FUN_00018C2C(1, (u32)FUN_00018E1C);
        DAT_10400540.unk38 = 0;
        DAT_10400440.unk38 = 0;
        DAT_10400540.unk34 = 0x10501;
        DAT_10400440.unk34 = 0x10501;
    }
}
