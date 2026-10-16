#include "types.h"

struct Unk_FFF00280 {
    u8 pad00[0x54];
    u32 unk54;
    u32 unk58;
};

extern const void *DAT_FFF00160;
extern Unk_FFF00280 *DAT_FFF000C0;

extern "C" u32 FUN_FFFF5C10(u32 id);
extern "C" void FUN_FFFFA594(const void *key, u64 offset);

u32 FUN_FFFF36D8(u32 mode, u32 (*op)(u32, u32, void *), u32 sector, u32 count, void *buf)
{
    u32 ret = 0;
    u32 left;
    u32 max;
    u32 cur;
    u8 *dst;
    u32 n;
    s32 tries;
    if (mode != 0 && DAT_FFF00160 == 0) {
        return 0x4000000;
    }
    FUN_FFFF5C10(0x201);
    if (mode) {
        max = 0x7FF;
    } else {
        max = 0xFFFF;
    }
    left = count;
    cur = sector;
    dst = (u8 *)buf;
    while (left != 0) {
        n = max;
        if (max > left) {
            n = left;
        }
        if (mode) {
            FUN_FFFFA594(DAT_FFF00160, (u64)cur << 9);
        }
        tries = 0;
        for (;;) {
            ret = op(cur, n, dst);
            if (ret == 0) {
                break;
            }
            tries++;
            DAT_FFF000C0->unk54++;
            DAT_FFF000C0->unk58 |= ret;
            if (tries > 2) {
                break;
            }
        }
        if (ret != 0) {
            break;
        }
        cur += n;
        left -= n;
        dst += n << 9;
    }
    return ret;
}
