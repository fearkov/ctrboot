#include "types.h"

struct Unk_080F8000 {
    u8 pad00[0x92];
    u16 unk92;
};

struct Unk_FFF016F0 {
    u8 pad00[0x20];
    u32 unk20;
    u8 *unk24;
    s32 unk28;
};

extern u32 DAT_080F8000[];
extern u32 DAT_080F9000[];
extern u32 *DAT_FFF00114;
extern Unk_FFF016F0 DAT_FFF016F0;

extern "C" Unk_080F8000 *FUN_FFFF9718();
extern "C" void FUN_FFFF03F0(const void *src, void *dst, u32 size);
extern "C" void FUN_FFFF03A4(u32 value, void *dst, u32 size);
extern "C" void FUN_FFFF47D0();

u32 FUN_FFFF330C(u32 addr, u8 *dst, s32 size)
{
    Unk_080F8000 *hdr = FUN_FFFF9718();
    u32 end = addr + size;
    u32 lo = (hdr->unk92 << 19) + 0x3000;
    u32 hi = lo + 0x4000;
    s32 n;
    s32 over;

    if (addr < 0x1000 && size > 0) {
        n = size;
        over = end - 0x1000;
        if (over > 0) {
            n -= over;
        }
        FUN_FFFF03F0(&DAT_080F8000[addr >> 2], dst, n);
        addr += n;
        dst += n;
        size -= n;
    }
    if (addr >= 0x1000 && addr < 0x4000 && size > 0) {
        over = end - addr - 0x3000;
        n = size;
        if (over > 0) {
            n -= over;
        }
        FUN_FFFF03A4(0, dst, n);
        addr += n;
        dst += n;
        size -= n;
    }
    if (addr >= 0x4000 && addr < 0x8000 && size > 0) {
        over = end - addr - 0x4000;
        n = size;
        if (over > 0) {
            n -= over;
        }
        FUN_FFFF03F0(&DAT_080F9000[(addr - 0x4000) >> 2], dst, n);
        addr += n;
        dst += n;
        size -= n;
    }
    if (hdr->unk92 != 0 && addr >= lo && addr < hi && size > 0) {
        over = end - hi;
        n = size;
        if (over > 0) {
            n -= over;
        }
        if (DAT_FFF00114 != 0) {
            FUN_FFFF03F0(&DAT_FFF00114[(addr - lo) >> 2], dst, n);
        }
        addr += n;
        dst += n;
        size -= n;
    }
    FUN_FFFF47D0();
    DAT_FFF016F0.unk24 = dst;
    DAT_FFF016F0.unk28 = size;
    DAT_FFF016F0.unk20 = addr;
    if (addr >= 0x8000 && size > 0) {
        return 1;
    }
    return 0;
}
