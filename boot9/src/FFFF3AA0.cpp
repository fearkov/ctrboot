#include "types.h"

struct Unk_FFF001A8 {
    u8 unk0;
    u8 pad1[3];
    u8 *unk4;
    u32 unk8;
};

extern Unk_FFF001A8 DAT_FFF001A8;

extern "C" u32 FUN_FFFF8950();
extern "C" u32 FUN_FFFFAD58();
extern "C" void FUN_FFFF89E4();
extern "C" void FUN_FFFFAE3C();
extern "C" void FUN_FFFFACC8();
extern "C" void FUN_FFFFAC78();
extern "C" void FUN_FFFFAD88();
extern "C" void FUN_FFFFADA0();
extern "C" void FUN_FFFF8A00(u32 mode, u32 a, u32 b, u32 blkcnt, u32 blklen, u32 c, u32 d);

u32 FUN_FFFF3AA0()
{
    if (FUN_FFFF8950()) {
        return 0x80000;
    }
    if (FUN_FFFFAD58()) {
        return 0x100000;
    }
    FUN_FFFF89E4();
    FUN_FFFFAE3C();
    FUN_FFFFACC8();
    FUN_FFFFAC78();
    if (DAT_FFF001A8.unk0) {
        FUN_FFFFAD88();
    } else {
        FUN_FFFFADA0();
    }
    FUN_FFFF8A00(2, 5, 5, 0, DAT_FFF001A8.unk8 >> 4, 0, 0);
    return 0;
}
