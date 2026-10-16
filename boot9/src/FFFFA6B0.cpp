#include "types.h"

struct Unk_10164000 {
    u8 unk0[4];
    volatile u32 unk4;
};
extern Unk_10164000 DAT_10164000;

extern "C" void FUN_FFFF0198(u32 count);
extern "C" void FUN_FFFF3094();
extern "C" u32 FUN_FFFFA5C4();
extern "C" void FUN_FFFFA72A(u32 value);
extern "C" void FUN_FFFF19E4(u64 value);

// The same as FUN_FFFF46C0, inlined here.
static inline u32 IsNotSet()
{
    return ~*(volatile u8 *)0x10000010 & 1;
}

void FUN_FFFFA6B0(u32 value)
{
    *(volatile u16 *)0x10000012 = value;
    *(volatile u16 *)0x10000014 = value;
    FUN_FFFF0198(value << 10);
    if (IsNotSet()) {
        FUN_FFFF3094();
        if (FUN_FFFFA5C4() != 0) {
            FUN_FFFFA72A(3);
            while (FUN_FFFFA5C4() != 0) {
            }
        }
        FUN_FFFF19E4(2);
        FUN_FFFFA72A(1);
        FUN_FFFF19E4(0x14);
        FUN_FFFFA72A(2);
        FUN_FFFF19E4(0x36);
        DAT_10164000.unk4 = 0x20000000;
        FUN_FFFF19E4(0x78);
    }
}
