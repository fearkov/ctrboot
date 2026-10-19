#include "types.h"

extern "C" u32 FUN_0001370C(u32 dev);
extern "C" u32 FUN_000136E0(u32 dev, u8 data);
extern "C" u32 FUN_000136B4(u32 dev, u8 data);
extern "C" u32 FUN_00013688(u32 dev);
extern "C" u8 FUN_00013858(u32 dev);
extern "C" u8 FUN_00013838(u32 dev);
extern "C" void FUN_00013784(u32 dev);

// Bus transaction with up to eight attempts; FUN_00013784 runs after each failed one. An attempt
// succeeds when every step passes and the byte read back equals arg, and the result is then the
// byte the last step reads. Returns 0xFF when all eight attempts failed.
u8 FUN_000135CC(u32 dev, u8 reg, u8 arg)
{
    u8 result = 0xFF;
    for (s32 i = 0; i < 8; i++) {
        if (FUN_0001370C(dev) && FUN_000136E0(dev, reg) && FUN_000136B4(dev, arg) && FUN_00013688(dev)
            && FUN_00013858(dev) == arg) {
            result = FUN_00013838(dev);
            break;
        }
        FUN_00013784(dev);
    }
    return result;
}
