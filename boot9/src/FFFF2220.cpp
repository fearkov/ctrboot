#include "types.h"

struct Unk_10008000 {
    u32 unk00;
    u16 unk04;
    u16 pad06;
    u32 unk08;
};

extern volatile u16 DAT_FFF00060;
extern volatile Unk_10008000 DAT_10008000;
extern "C" u32 FUN_FFFF1F38(void);
extern "C" void FUN_FFFF2128(u32 state);
extern "C" void FUN_FFFF22C0(u32 value);
extern "C" u32 FUN_FFFF2264(void);

void FUN_FFFF2220(void)
{
    u32 state = FUN_FFFF1F38();
    if (DAT_FFF00060 == 0) {
        DAT_FFF00060 = 1;
        volatile Unk_10008000 *r = &DAT_10008000;
        r->unk00 |= (u32)r << 16;
        r->unk04 = 0xC008;
        FUN_FFFF22C0(9);
        while (FUN_FFFF2264() != 11) {
        }
    }
    FUN_FFFF2128(state);
}
