#include "types.h"

struct Unk_10008000 {
    u32 unk00;
    u16 unk04;
    u16 pad06;
    u32 unk08;
};

extern volatile Unk_10008000 DAT_10008000;
extern "C" u32 FUN_FFFF1F38(void);
extern "C" void FUN_FFFF2128(u32 state);

// Sends one word through the register at 0x10008008 (0x10008004 is its status): -1 if the error flag (bit 14) is set (it is
// acknowledged), -2 if bit 1 is set (no room), else 0.
s32 FUN_FFFF1A44(u32 value)
{
    if (DAT_10008000.unk04 & 0x4000) {
        DAT_10008000.unk04 |= 0xC000;
        return -1;
    }
    u32 state = FUN_FFFF1F38();
    if (DAT_10008000.unk04 & 2) {
        FUN_FFFF2128(state);
        return -2;
    }
    DAT_10008000.unk08 = value;
    FUN_FFFF2128(state);
    return 0;
}
