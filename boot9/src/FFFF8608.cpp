// The tables are integer addresses on purpose: armcc then derives 0xFFF00000 from the 0xFFF00020 literal in the else
// branch (subs #0x20), as the dump does, where a DAT symbol makes it hoist one literal load above the branch. The
// first loop's source is a u64 only to steer register allocation: as a u32, armcc builds the destination in the
// other argument register.
#include "types.h"

struct Unk_10010000
{
    u8 pad00[0x10];
    volatile u8 unk10;
};

struct Unk_07FFB800
{
    u8 pad000[0x500];
    u8 unk500[4][0x100];
    u8 unk900[4][0x200];
};

struct Unk_FFF00000
{
    u32 unk00[4];
    u32 unk10[4];
};

extern Unk_10010000 DAT_10010000;
extern Unk_07FFB800 DAT_07FFB800;

extern "C" void FUN_FFFFA954(u32 slot, u32 size, u32 a, u32 b);
extern "C" void FUN_FFFF03F0(u32 src, void *dst, u32 size);

// Sets RSA key slots 0-3 from the key table at 0xFFF00000 (at 0xFFF00020 when 0x10010010 is set), each modulus with
// its exponent 0x100 bytes after it, and copies each modulus to 0x07FFBD00 + i * 0x100; then copies the four
// 0x200-byte blocks the table's second half points at to 0x07FFC100 + i * 0x200.
void FUN_FFFF8608()
{
    Unk_07FFB800 *ram = &DAT_07FFB800;
    const Unk_FFF00000 *tab;
    if (DAT_10010000.unk10) {
        tab = (const Unk_FFF00000 *)0xFFF00020;
    } else {
        tab = (const Unk_FFF00000 *)0xFFF00000;
    }
    for (s32 i = 0; i < 4; i++) {
        u32 key = tab->unk00[i];
        FUN_FFFFA954(i, 0x800, key, key + 0x100);
        u64 src = tab->unk00[i];
        FUN_FFFF03F0(src, ram->unk500[i], 0x100);
    }
    for (u32 i = 0; i < 4; i++) {
        u32 src = tab->unk10[i];
        FUN_FFFF03F0(src, ram->unk900[i], 0x200);
    }
}
