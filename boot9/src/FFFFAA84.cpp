// The exponent FIFO is reached by its absolute address: armcc then keeps it in r7 across the fill call, as the
// dump does (named as an extern DAT_1000B200, it is loaded again for the store).
#include "types.h"

extern "C" void FUN_FFFFA850();
extern "C" u32 FUN_FFFFA8B8(u32 index);
extern "C" u32 FUN_FFFFA874();
extern "C" u32 FUN_FFFFA8D4(u32 index);
extern "C" void FUN_FFFF03A4(u32 value, volatile void *dst, u32 size);
extern "C" void FUN_FFFF9D10(u8 *dst, const u8 *src, u32 size);
extern "C" void FUN_FFFF056C(void *dst, u32 value, u32 size);

struct Unk_FFF0007C {
    u8 unk0[8];
    u32 unk8;
};
extern Unk_FFF0007C DAT_FFF0007C;
extern volatile u32 DAT_1000B000;

// Like FUN_FFFFA954, with a 32-bit exponent (a public key, such as 0x10001): the exponent FIFO takes zero bytes up
// to the slot size, then the exponent; only the modulus is checked for set unused top bits.
u32 FUN_FFFFAA84(u32 slot, s32 bits, const u8 *modulus, u32 exponent)
{
    s32 size = (bits + 7) >> 3;
    s32 padded = (size + 7) & ~7;
    if (DAT_FFF0007C.unk8 == 0) {
        FUN_FFFFA850();
    }
    if (slot >= 4 || FUN_FFFFA8B8(slot) != 0) {
        return 0;
    }
    if (padded < 0x10) {
        padded = 0x10;
    }
    if (bits & 7) {
        // computed before the loop (not in its condition), as in the dump
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
    FUN_FFFFA8D4(slot);
    DAT_1000B000 = (DAT_1000B000 & ~0x30) | (slot << 4);
    FUN_FFFF03A4(0, (volatile u32 *)0x1000B200, padded - 4);
    *(volatile u32 *)0x1000B200 = exponent;
    volatile u32 *reg = (volatile u32 *)(0x1000B100 + slot * 0x10);
    if (reg[1] != padded >> 2) {
        return 0;
    }
    FUN_FFFF9D10((u8 *)0x1000B400, modulus, size);
    if (padded > size) {
        u8 *rest = (u8 *)0x1000B400 + size;
        FUN_FFFF056C(rest, 0, padded - size);
    }
    return 1;
}
