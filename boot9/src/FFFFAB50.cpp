#include "types.h"

extern "C" void FUN_FFFFA850();
extern "C" u32 FUN_FFFFA874();
extern "C" void FUN_FFFF9D10(u8 *dst, const u8 *src, u32 size);
extern "C" void FUN_FFFF056C(void *dst, u32 value, u32 size);

struct Unk_FFF0007C {
    u8 unk0[8];
    u32 unk8;
};
extern Unk_FFF0007C DAT_FFF0007C;

// Loads a modulus of `bits` bits (big endian, rejected when the unused top bits of its first byte are
// set) into the engine, byte-reversed and zero-padded to a multiple of 8 bytes (at least 16).
u32 FUN_FFFFAB50(s32 bits, const u8 *modulus)
{
    s32 size = (bits + 7) >> 3;
    s32 padded = (size + 7) & ~7;
    if (DAT_FFF0007C.unk8 == 0) {
        FUN_FFFFA850();
    }
    if (padded < 0x10) {
        padded = 0x10;
    }
    if (bits & 7) {
        // computed before the loop (not in its condition): that keeps bits out of the registers that
        // live across the later calls, as in the dump
        s32 rem = bits % 8;
        for (s32 i = 0; i < rem; i++) {
            if (modulus[0] & (1 << (7 - i))) {
                return 0;
            }
        }
    }
    if (FUN_FFFFA874() != 0) {
        return 0;
    }
    FUN_FFFF9D10((u8 *)0x1000B800, modulus, size);
    if (padded > size) {
        // the destination first, as the dump computes it before the length
        u8 *rest = (u8 *)0x1000B800 + size;
        FUN_FFFF056C(rest, 0, padded - size);
    }
    return 1;
}
