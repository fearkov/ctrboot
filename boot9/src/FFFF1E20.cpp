#include "types.h"

struct Unk_FFF00058 {
    void (*unk0)(u32);
    void (*unk4)(u32);
};

extern Unk_FFF00058 DAT_FFF00058;

extern "C" u32 FUN_FFFF1710();
extern "C" void FUN_FFFF15D0(u32 arg);

void FUN_FFFF1E20()
{
    u32 arg = FUN_FFFF1710();
    if (DAT_FFF00058.unk0 != 0) {
        DAT_FFF00058.unk0(arg);
    }
    FUN_FFFF15D0(arg);
}
