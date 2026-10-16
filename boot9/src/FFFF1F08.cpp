#include "types.h"

struct Unk_FFFF1F08 {
    u32 unk0;
    u8 unk4[4];
    u32 unk8;
};

void FUN_FFFF1F08(Unk_FFFF1F08 *state)
{
    state->unk0 = 0;
    state->unk8 = 0;
}
