#include "types.h"

// Two locals only steer armcc's register allocation, in both loops: the divisor, which makes armcc load it before
// the multiply (with the constant in the division it reloads scale into r1 and loads the divisor after it), and the
// copy of frac, which lets the masked value stay in r0 (stored straight to its stack slot) so idx stays in r1 for
// the first lookup (without it armcc masks into r1 and reloads idx). The first screen declares scale before value
// so that scale gets the upper stack slot, as in the dump. The loop pointer starts at &table[1] of the array itself:
// from table + 1 armcc merges the first store and the pointer into one post-increment store.

struct Unk_10202200 {
    u32 unk0[0x38 / 4];
    u32 unk38;
};

extern volatile Unk_10202200 DAT_10202200;
extern volatile Unk_10202200 DAT_10202A00;
extern volatile u32 DAT_10202400[256];
extern volatile u32 DAT_10202C00[256];

extern "C" void FUN_0001867C(u32 *a, u32 *b, u32 *c);
extern "C" u32 FUN_00018640(u32 which, u32 value);
extern "C" u32 FUN_00018894(u32 which, u32 index, u32 alt);

// For each screen in flags (1 and 2), fills the screen's 256-entry table with a quadratic curve over its levels
// (entry i is level i * i * max / (255 * 255), interpolated in 1/64 steps between two levels) and sets unk38 to
// the last index of the table's leading run of equal entries (0xFF when all are equal).
void FUN_00019060(u32 flags)
{
    if (flags & 1) {
        bool found = false;
        volatile u32 *table = DAT_10202400;
        u32 scale;
        u32 value;
        FUN_0001867C(&value, 0, 0);
        scale = FUN_00018640(1, value) << 6;
        u32 prev = FUN_00018894(1, 0, value);
        *table = prev;
        volatile u32 *p = &DAT_10202400[1];
        for (int i = 1; i < 256; i++) {
            u32 divisor = 255 * 255;
            int pos = i * i * scale / divisor;
            int idx = pos >> 6;
            int frac = pos & 0x3F;
            int weight = frac;
            int a = FUN_00018894(1, idx, value);
            int b = FUN_00018894(1, idx + 1, value);
            u32 v = (u16)(((weight * (b - a)) >> 6) + a);
            *p++ = v;
            if (!found && v != prev) {
                DAT_10202200.unk38 = i - 1;
                found = true;
            }
            prev = v;
        }
        if (!found)
            DAT_10202200.unk38 = 0xFF;
    }
    if (flags & 2) {
        bool found = false;
        volatile u32 *table = DAT_10202C00;
        u32 scale = FUN_00018640(2, 0) << 6;
        u32 prev = FUN_00018894(2, 0, 0);
        *table = prev;
        volatile u32 *p = &DAT_10202C00[1];
        for (int i = 1; i < 256; i++) {
            u32 divisor = 255 * 255;
            int pos = i * i * scale / divisor;
            int idx = pos >> 6;
            int frac = pos & 0x3F;
            int weight = frac;
            int a = FUN_00018894(2, idx, 0);
            int b = FUN_00018894(2, idx + 1, 0);
            u32 v = (u16)(((weight * (b - a)) >> 6) + a);
            *p++ = v;
            if (!found && v != prev) {
                DAT_10202A00.unk38 = i - 1;
                found = true;
            }
            prev = v;
        }
        if (!found)
            DAT_10202A00.unk38 = 0xFF;
    }
}
