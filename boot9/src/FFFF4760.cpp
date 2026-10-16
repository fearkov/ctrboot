// One translation unit with FUN_FFFF3134 (not inlined): armcc then knows it only touches r0 and r1, so
// FUN_FFFF4760 keeps the structure pointer in r2 and the old value in r3 across the call.
#pragma no_inline
#include "types.h"

struct Unk_FFFF4760_38
{
    u8 pad00[8];
    u32 unk08;
    u32 unk0C;
    u8 pad10[4];
    u32 *unk14;
};

struct Unk_FFFF4760
{
    u8 pad00[0x20];
    u32 unk20;
    u32 unk24;
    u32 unk28;
    u32 unk2C;
    u8 unk30;
    u8 unk31;
    u8 pad32[6];
    Unk_FFFF4760_38 unk38;
};

typedef void (*Handler)();

extern "C" void FUN_FFFF35C0(u32 a);
extern "C" void FUN_FFFF1F38();
extern "C" void FUN_FFFF21AC(u32 irq, Handler handler);
extern "C" void FUN_FFFF1ED4(u32 irq);
extern "C" void FUN_FFFF1F40(u32 irq);
extern "C" void FUN_FFFF08A8(u32 a, u32 b);
extern "C" void FUN_FFFF1F68();
extern "C" void FUN_FFFF06D8();

u32 FUN_FFFF3134(u32 x)
{
    u32 field = (x << 5) >> 29;
    u32 size = 0x200u;
    return size << (field - 1);
}

void FUN_FFFF4760(u32 a, u32 b, u32 c, Unk_FFFF4760 *q)
{
    Unk_FFFF4760_38 *r = &q->unk38;
    u32 irq = 0x1B;
    // 0xFFFF3145 is the Thumb function at 0xFFFF3144, which is not in the list yet (no FUN_FFFF3144 to name).
    Handler handler = (Handler)0xFFFF3145;
    u32 x = r->unk08;
    q->unk24 = b;
    q->unk20 = a;
    q->unk28 = c;
    q->unk2C = FUN_FFFF3134(*r->unk14);
    r->unk0C = r->unk08;
    if (x > 7) {
        r->unk08 = 3;
    }
    FUN_FFFF35C0(x);
    FUN_FFFF1F38();
    FUN_FFFF21AC(irq, handler);
    q->unk31 = 1;
    q->unk30 = 0;
    FUN_FFFF1ED4(irq);
    FUN_FFFF1F40(irq);
    FUN_FFFF08A8(b, c);
    FUN_FFFF1F68();
    FUN_FFFF06D8();
}
