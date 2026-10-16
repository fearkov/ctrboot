#include "types.h"

struct Unk_FFF00250 {
    u32 unk0;
};

extern Unk_FFF00250 DAT_FFF00250;
extern u8 DAT_FFFF4FE8;

extern "C" void FUN_FFFF1E40(Unk_FFF00250 *timer);
extern "C" void FUN_FFFF2130(Unk_FFF00250 *timer, u64 ticks, void (*callback)(u32), u32 param);
extern "C" u64 FUN_FFFF3088(u32 a, u32 b);

void FUN_FFFF2920(u32 time)
{
    FUN_FFFF1E40(&DAT_FFF00250);
    u64 ticks = FUN_FFFF3088(time, 0x105D4) >> 6;
    // the callback is the Thumb function at 0xFFFF4FE8
    FUN_FFFF2130(&DAT_FFF00250, ticks, (void (*)(u32))((u32)&DAT_FFFF4FE8 + 1), time);
}
