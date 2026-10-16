#include "types.h"

struct Unk_FFF00058 {
    u32 unk00;
    void (*unk04)(u32);
};

extern Unk_FFF00058 DAT_FFF00058;
extern "C" u32 FUN_FFFF1F38(void);
extern "C" void FUN_FFFF22C0(u32 x);
extern "C" void FUN_FFFF22D8(u32 x);
extern "C" void FUN_FFFF1618(void);
extern "C" void FUN_FFFF16D4(void);
extern "C" void FUN_FFFF01B0(void);
extern "C" void FUN_FFFF1748(void);
extern "C" void FUN_FFFF01D4(u32 x);

void FUN_FFFF15D0(u32 arg)
{
    void (*callback)(u32) = DAT_FFF00058.unk04;
    FUN_FFFF1F38();
    FUN_FFFF22C0(1);
    FUN_FFFF22D8(1);
    FUN_FFFF22D8(14);
    FUN_FFFF1618();
    FUN_FFFF22C0(14);
    FUN_FFFF16D4();
    if (callback != 0) {
        callback(arg);
    }
    FUN_FFFF01B0();
    FUN_FFFF1748();
    FUN_FFFF01D4(arg);
}
