#include "types.h"

struct Unk_FFF01910 {
    u32 unk0;
    u32 unk4;
    u32 unk8;
    u32 unkC;
};

extern Unk_FFF01910 DAT_FFF01910[];

extern "C" void FUN_FFFF1138(u32 mode, u32 index, u32 a2, u32 a3, u32 a4, u32 a5, void (*callback)(u32),
                             u32 callbackArg, Unk_FFF01910 *entry, u32 a9, u32 flags);

void FUN_FFFF1C2C(u32 index, u32 a1, u32 a2, u32 a3, void (*callback)(u32), u32 callbackArg, u32 a6)
{
    FUN_FFFF1138(3, index, a1, a2, 0, a3, callback, callbackArg, &DAT_FFF01910[index], a6, 0x80000000);
}
