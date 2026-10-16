#include "types.h"

extern "C" u32 FUN_FFFF1F38(void);
extern "C" void FUN_FFFF03F0(const void *src, void *dst, u32 size);
extern "C" void FUN_FFFF8FD0(void);

struct Unk_10010000 {
    u8 pad00[0x10];
    u8 unk10;
};

extern volatile Unk_10010000 DAT_10010000;

// The second copy is written out in both branches: armcc hoists the common destination and size above the test and
// merges the calls. The destination and size of the first copy are named first so their literals come first.
void FUN_FFFF1618(void)
{
    FUN_FFFF1F38();
    void *dst = (void *)0x07FFD000;
    u32 size = 0x2470;
    FUN_FFFF03F0((const void *)0x1FFFA000, dst, size);
    if (DAT_10010000.unk10 != 0) {
        FUN_FFFF03F0((const void *)0x1FFFD400, (void *)0x07FFC900, 0x400);
    } else {
        FUN_FFFF03F0((const void *)0x1FFFD000, (void *)0x07FFC900, 0x400);
    }
    FUN_FFFF8FD0();
}
