// Built for space (armcc's default), like the other one-shot initialisers of this ROM.
#pragma Ospace
#include "types.h"

struct Unk_FFF00040 {
    u32 unk0;
    u32 unk4;
};

extern Unk_FFF00040 DAT_FFF00040;

extern "C" void FUN_FFFF20CC();
extern "C" void FUN_FFFF2028();
extern "C" void FUN_FFFF2064();
extern "C" void FUN_FFFF1FCC();
extern "C" void FUN_FFFF1AB0();
extern "C" void FUN_FFFF4F64();

void FUN_FFFF1FF8()
{
    if (DAT_FFF00040.unk4 == 0) {
        DAT_FFF00040.unk4 = 1;
        FUN_FFFF20CC();
        FUN_FFFF2028();
        FUN_FFFF2064();
        FUN_FFFF1FCC();
        FUN_FFFF1AB0();
        FUN_FFFF4F64();
    }
}
