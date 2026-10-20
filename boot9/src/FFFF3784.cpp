#include "types.h"

struct Unk_FFF000C0 {
    u8 pad00[0x54];
    u32 unk54;
    u32 unk58;
};

struct Unk_FFFFADB4 {
    u8 unk00[0xC];
    u8 unk0C[0x20];
    u32 unk2C;
};

extern const void *DAT_FFF00160;
extern Unk_FFF000C0 *DAT_FFF000C0;

extern "C" u32 FUN_FFFF5C10(u32 id);
extern "C" void FUN_FFFFA594(const void *key, u64 offset);
extern "C" void FUN_FFFFADB4(Unk_FFFFADB4 *out);

// Runs op over count sectors from sector on port 0x201, in chunks of at most 0x7FF sectors: before each chunk it
// sets the AES counter for the chunk's first sector and saves the hash state, and it retries a failing chunk up to
// three times, counting the errors in DAT_FFF000C0. op gets first only with the first chunk and last only with the
// last one (0 otherwise).
u32 FUN_FFFF3784(u32 (*op)(u32, u32, u32, u32, void *), u32 first, u32 last, u32 sector, u32 count, void *buf)
{
    u32 ret = 0;
    u32 left;
    u32 max;
    u32 a;
    u32 b;
    u32 cur;
    u8 *dst;
    Unk_FFFFADB4 state;
    u32 n;
    s32 tries;
    if (DAT_FFF00160 == 0) {
        ret = 0x4000000;
    }
    if (ret != 0) {
        return ret;
    }
    FUN_FFFF5C10(0x201);
    max = 0x7FF;
    left = count;
    dst = (u8 *)buf;
    cur = sector;
    while (left != 0) {
        n = max;
        if (max > left) {
            n = left;
        }
        FUN_FFFFA594(DAT_FFF00160, (u64)cur << 9);
        FUN_FFFFADB4(&state);
        if (left == count) {
            a = first;
        } else {
            a = 0;
        }
        if (left <= max) {
            b = last;
        } else {
            b = 0;
        }
        tries = 0;
        for (;;) {
            ret = op(a, b, cur, n, dst);
            if (ret == 0) {
                break;
            }
            tries++;
            DAT_FFF000C0->unk54++;
            DAT_FFF000C0->unk58 |= ret;
            if (tries > 2) {
                return ret;
            }
            FUN_FFFFADB4(&state);
        }
        cur += n;
        left -= n;
        dst += n << 9;
    }
    return ret;
}
