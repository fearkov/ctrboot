// The flag register is volatile: that keeps the read ahead of the constant setup (a plain read is scheduled after "movs r4, #1").
#include "types.h"

struct Unk_10010000
{
    u8 pad00[0x10];
    u8 unk10;
};

extern volatile Unk_10010000 DAT_10010000;
extern u8 DAT_FFFFC3E0;
extern u8 DAT_FFFFC4E0;
extern u8 DAT_FFFFC5E0;
extern u8 DAT_FFFFB0E0;
extern u8 DAT_FFFFB1E0;
extern u8 DAT_FFFFB2E0;

extern "C" void FUN_FFFFAA84(u32 slot, u32 size, const void *data, u32 flags);

void FUN_FFFF8594()
{
    const void *last;
    if (DAT_10010000.unk10) {
        FUN_FFFFAA84(3, 0x800, &DAT_FFFFC3E0, 0x10001);
        FUN_FFFFAA84(1, 0x800, &DAT_FFFFC4E0, 0x10001);
        last = &DAT_FFFFC5E0;
    } else {
        FUN_FFFFAA84(3, 0x800, &DAT_FFFFB0E0, 0x10001);
        FUN_FFFFAA84(1, 0x800, &DAT_FFFFB1E0, 0x10001);
        last = &DAT_FFFFB2E0;
    }
    FUN_FFFFAA84(2, 0x800, last, 0x10001);
}
