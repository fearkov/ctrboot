#include "types.h"

extern "C" void FUN_FFFF1DFC(u32 channel);
extern "C" void FUN_FFFFAE58();
extern "C" void FUN_FFFFAC8C();

struct Unk_FFF00240 {
    u16 unk0;
    u8 unk2;
    u8 unk3;
    u8 unk4;
    u8 unk5;
    u8 unk6;
    u8 unk7;
    u8 unk8;
    u8 unk9;
};
extern Unk_FFF00240 DAT_FFF00240;
extern volatile u32 DAT_1000A000;

void FUN_FFFFAE64()
{
    // taking the address first gives the dump's order of the two literals
    Unk_FFF00240 *state = &DAT_FFF00240;
    if (DAT_1000A000 & 0x4)
        FUN_FFFF1DFC(state->unk8);
    if (DAT_1000A000 & 0x400)
        FUN_FFFF1DFC(state->unk9);
    FUN_FFFFAE58();
    if (state->unk2 != 0)
        FUN_FFFFAC8C();
}
