#include "types.h"

extern "C" u32 FUN_FFFF8940();
extern "C" void FUN_FFFF047C(const volatile void *fifo, void *dst, u32 size);
extern "C" void FUN_FFFF0540(const void *src, void *dst);

// The callback FUN_FFFFA15C gives FUN_FFFFAF70: once the AES output FIFO holds its 16 words, moves
// them (0x40 bytes from the FIFO at 0x1000900C) into the SHA input window at 0x1000A080 and copies the
// block from there to dst.
void FUN_FFFFAFE0(u32 dst)
{
    while (FUN_FFFF8940() != 0x10) {
    }
    FUN_FFFF047C((const volatile void *)0x1000900C, (void *)0x1000A080, 0x40);
    FUN_FFFF0540((const void *)0x1000A080, (void *)dst);
}
