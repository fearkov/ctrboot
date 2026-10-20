#include "types.h"

struct Unk_FFF01990 {
    u8 pad00[0x14];
    u32 unk14;
    u8 pad18[0x14];
};

extern Unk_FFF01990 DAT_FFF01990[];

// The largest part of a transfer of size bytes in units of unit bytes that one
// DMA program from FUN_FFFF0CF4 can move on channel index.
u32 FUN_FFFF10F4(s32 index, u32 unit, u32 size)
{
    u32 width = DAT_FFF01990[index].unk14;
    u32 max = unit << 8;
    u32 outer = (unit - 1) / width;
    u32 count = (size - 1) / unit;
    u32 high = outer ? 0 : count >> 8;
    if (high) {
        size &= ~(max - 1);
        max <<= 8;
    }
    return (max < size) ? max : size;
}
