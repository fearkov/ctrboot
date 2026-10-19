#include "types.h"

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

extern "C" void FUN_FFFF1CB4(u32 channel, u32 size, u32 a, u32 b, u32 c, u32 d, u32 e, u32 f);

// Sets up two DMA channels with FUN_FFFF1CB4: the channel at +4 (size at +6) from the first four arguments, the
// channel at +5 (size at +7) from the last four.
void FUN_FFFFADF4(u32 a, u32 b, u32 c, u32 d, u32 e, u32 f, u32 g, u32 h)
{
    Unk_FFF00240 *s = &DAT_FFF00240;
    FUN_FFFF1CB4(s->unk4, s->unk6, a, b, c, d, 0, 0);
    FUN_FFFF1CB4(s->unk5, s->unk7, e, f, g, h, 0, 0);
}
