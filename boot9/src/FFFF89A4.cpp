#include "types.h"

struct Unk_FFFFB0D0
{
    u32 unk0;
    u32 unk4;
    u32 unk8;
    u32 unkC;
};

extern Unk_FFFFB0D0 DAT_FFFFB0D0;

extern "C" void FUN_FFFF1138(u32 mode, u32 index, u32 src, u32 dst, u32 a4, u32 size, void (*callback)(u32),
                             u32 callbackArg, Unk_FFFFB0D0 *entry, u32 a9, u32 flags);

void FUN_FFFF89A4(u32 index, u32 size, void (*callback)(u32), u32 callbackArg)
{
    FUN_FFFF1138(4, index, 0x1000900C, 0x1000A080, 0, size, callback, callbackArg, &DAT_FFFFB0D0, 0x0F000010,
                 0x80000000);
}
