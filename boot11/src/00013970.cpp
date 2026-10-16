// The state is reached through a pointer built from its address, not through an extern
// object: only then does armcc form &unk1 as &unk2 - 1 (subs r0, r1, #1), as the dump does.
// "return unk3 != 0" after the if is what gives the dump's per-path returns.
#include "types.h"

struct Unk_1FFE80E8 {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
};

extern "C" u32 FUN_00013A00(u8* a, u8* b);

u32 FUN_00013970()
{
    Unk_1FFE80E8* s = (Unk_1FFE80E8*)0x1FFE80E8;
    if (!s->unk0) {
        s->unk0 = 1;
        FUN_00013A00(&s->unk1, &s->unk2);
        if ((s->unk1 & 0xF) == 0 && s->unk2 < 9)
            s->unk3 = 0;
        else
            s->unk3 = 1;
    }
    return s->unk3 != 0;
}
