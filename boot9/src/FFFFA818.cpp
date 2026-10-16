#include "types.h"

extern "C" void FUN_FFFFA850();
extern "C" u32 FUN_FFFFA874();
extern "C" void FUN_FFFF9D10(u8 *dst, const u8 *src, u32 size);

struct Unk_FFF0007C {
    u8 unk0[8];
    u32 unk8;
};
extern Unk_FFF0007C DAT_FFF0007C;

u32 FUN_FFFFA818(s32 bits, u8 *dst)
{
    s32 size = (bits + 7) >> 3;
    if (DAT_FFF0007C.unk8 == 0) {
        FUN_FFFFA850();
    }
    if (FUN_FFFFA874() != 0) {
        return 0;
    }
    FUN_FFFF9D10(dst, (const u8 *)0x1000B800, size);
    return 1;
}
