#include "types.h"

struct Unk_FFF001A0 {
    u32 *unk0;
    u32 unk4;
};

extern Unk_FFF001A0 DAT_FFF001A0;

extern "C" u32 FUN_FFFF8950();
extern "C" void FUN_FFFF89E4();
extern "C" void FUN_FFFF8A00(u32 mode, u32 a, u32 b, u32 blkcnt, u32 blklen, u32 c, u32 d);

u32 FUN_FFFF3B9C()
{
    if (FUN_FFFF8950()) {
        return 0x80000;
    }
    FUN_FFFF89E4();
    FUN_FFFF8A00(2, 5, 5, 0, DAT_FFF001A0.unk4 >> 4, 0, 0);
    return 0;
}
