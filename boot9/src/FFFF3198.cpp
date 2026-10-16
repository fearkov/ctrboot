#include "types.h"

struct Unk_FFFF5D20 {
    u32 unk0;
    u32 unk4;
    u32 unk8;
    u32 unkC;
};

extern const Unk_FFFF5D20 DAT_FFFF5D20;
extern volatile u32 DAT_1016401C;

extern "C" void FUN_FFFF1138(u32 mode, u32 channel, volatile u32 *src, u32 *dst, u32 unk4, u32 size,
                             void (*callback)(u32), u32 callbackArg, const Unk_FFFF5D20 *config,
                             u32 flags, u32 control);

void FUN_FFFF3198(u32 channel, u32 *dst)
{
    FUN_FFFF1138(4, channel, &DAT_1016401C, dst, 0, 4, 0, 0, &DAT_FFFF5D20, 0x2C000000, 0x80000000);
}
