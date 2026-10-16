// Built for space: armcc then takes the address of the register block again from the literal of
// DAT_1000A000 + 0x40 (subs #0x40) instead of adding a literal for DAT_1000A000.
#pragma Ospace
#include "types.h"

extern "C" void FUN_FFFF05E0(const void *src, void *dst, u32 size);
extern u8 DAT_FFF00240[];

struct Unk_1000A000 {
    u32 unk00;
    u32 unk04;
    u8 unk08[0x38];
    u8 unk40[0x20];
};
extern volatile Unk_1000A000 DAT_1000A000;

struct Unk_FFFFADB4 {
    u8 unk00[0xC];
    u8 unk0C[0x20];
    u32 unk2C;
};

void FUN_FFFFADB4(Unk_FFFFADB4 *out)
{
    FUN_FFFF05E0((const void *)DAT_1000A000.unk40, out->unk0C, 0x20);
    out->unk2C = DAT_1000A000.unk04;
    FUN_FFFF05E0(DAT_FFF00240, out, 0xC);
}
