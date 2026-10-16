#include "types.h"

struct Unk_FFF00140 {
    u32 unk00;
    u32 unk04;
    u8 pad08[0x8];
    u64 unk10;
};

struct Unk_10003004 {
    u16 unk0;
    u16 unk2;
};

typedef void (*Handler)();

extern "C" u64 FUN_FFFF1F70();
extern "C" u32 FUN_FFFF1F40(u32 bit);
extern "C" void FUN_FFFF21AC(u32 irq, Handler handler);
extern u8 DAT_FFFF1554;
extern volatile Unk_10003004 DAT_10003004;

u32 FUN_FFFF1964(Unk_FFF00140 *timer)
{
    u64 now = FUN_FFFF1F70();
    s64 diff = timer->unk10 - now;
    DAT_10003004.unk2 = 0;
    FUN_FFFF21AC(9, (Handler)((u32)&DAT_FFFF1554 + 1));
    u16 value;
    if (diff <= 1) {
        value = 0xFFFE;
    } else if ((u64)diff < 0x10000) {
        value = ~diff;
    } else {
        value = 0;
    }
    DAT_10003004.unk0 = value;
    DAT_10003004.unk2 = 0xc1;
    return FUN_FFFF1F40(9);
}
