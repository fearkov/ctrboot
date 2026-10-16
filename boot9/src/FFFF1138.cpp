#include "types.h"

// The NDMA registers: a global control register, then eight channels.
struct Unk_10002004 {
    u32 unk0;  // source address
    u32 unk4;  // destination address
    u32 unk8;  // total word count
    u32 unkC;  // word count
    u32 unk10; // block interval
    u32 unk14; // fill data
    u32 unk18; // control
};

struct Unk_10002000 {
    u32 unk0;
    Unk_10002004 unk4[8];
};

extern volatile Unk_10002000 DAT_10002000;

struct Unk_FFFF1138 {
    u32 unk0;
    u32 unk4;
    u32 unk8;
    u32 unkC;
};

extern "C" u32 FUN_FFFF1F38();
extern "C" void FUN_FFFF2128(u32 state);
extern "C" u32 FUN_FFFF1BA8(u32 index);
extern "C" void FUN_FFFF1694(u32 index, void (*callback)(u32), u32 callbackArg);
extern "C" void FUN_FFFF11EC(u32 index, u32 count);
extern "C" u32 FUN_FFFF1098(u32 mode);

void FUN_FFFF1138(u32 mode, u32 index, u32 src, u32 dst, u32 fill, u32 size, void (*callback)(u32), u32 callbackArg,
                  const Unk_FFFF1138 *config, u32 startup, u32 flags)
{
    if (size == 0) {
        if (callback != 0) {
            callback(callbackArg);
        }
        return;
    }
    u32 state = FUN_FFFF1F38();
    while (FUN_FFFF1BA8(index) == 1) {
    }
    if (callback != 0) {
        FUN_FFFF1694(index, callback, callbackArg);
    }
    if (mode != 0) {
        DAT_10002000.unk4[index].unk0 = src;
    }
    DAT_10002000.unk4[index].unk4 = dst;
    DAT_10002000.unk4[index].unk10 = config->unk0 | config->unk4;
    if (mode == 0) {
        DAT_10002000.unk4[index].unk14 = fill;
    }
    if (startup == 0xFFFFFFFF) {
        FUN_FFFF11EC(index, size / 4);
    } else {
        DAT_10002000.unk4[index].unk8 = size / 4;
        FUN_FFFF11EC(index, config->unkC == 0xFFFFFFFF ? size / 4 : config->unkC);
    }
    u32 control = config->unk8 | (flags & 0x80000000);
    control |= FUN_FFFF1098(mode);
    control |= startup != 0xFFFFFFFF ? startup : 0x10000000;
    if (callback != 0) {
        control |= 0x40000000;
    }
    DAT_10002000.unk4[index].unk18 = control;
    FUN_FFFF2128(state);
}
