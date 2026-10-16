#include "types.h"

extern "C" void FUN_FFFF1A84(u32 channel, void *out);
extern "C" void FUN_FFFF1E10(u32 channel);
extern "C" void FUN_FFFFAE58();
extern "C" void FUN_FFFFAC8C();

struct Unk_FFF00240 {
    u8 unk0[2];
    u8 unk2;
    u8 unk3;
    u8 unk4;
    u8 unk5;
};
extern Unk_FFF00240 DAT_FFF00240;
extern volatile u32 DAT_1000A000;

// A channel's 0x2C-byte descriptor, as FUN_FFFF1A84 copies it out.
struct Unk_FFF01990 {
    u8 unk00[0x1E];
    u8 unk1E;
    u8 unk1F[0x0D];
};

void FUN_FFFFAEB4()
{
    Unk_FFF01990 channel;
    FUN_FFFF1A84(DAT_FFF00240.unk4, &channel);
    if (DAT_1000A000 & 0x4)
        FUN_FFFF1E10(DAT_FFF00240.unk4);
    if (DAT_1000A000 & 0x400)
        FUN_FFFF1E10(DAT_FFF00240.unk5);
    FUN_FFFFAE58();
    if (DAT_FFF00240.unk2 != 0 && channel.unk1E == 0)
        FUN_FFFFAC8C();
}
