#include "types.h"

struct Unk_10010000 {
    u8 unk0[0x10];
    u8 unk10;
};
extern Unk_10010000 DAT_10010000;
extern u8 DAT_FFFFD7E0[];
extern u8 DAT_FFFFD820[];
extern u8 DAT_FFFFD760[];
extern u8 DAT_FFFFD7A0[];
struct Unk_07FFCD00 { u8 unk0[0x40]; u8 unk40[0x40]; };
extern Unk_07FFCD00 DAT_07FFCD00;

extern "C" void FUN_FFFF03F0(void *src, void *dst, u32 n);

void FUN_FFFF8FD0()
{
    u8 *a;
    u8 *b;
    if (DAT_10010000.unk10) {
        a = DAT_FFFFD7E0;
        b = DAT_FFFFD820;
    } else {
        a = DAT_FFFFD760;
        b = DAT_FFFFD7A0;
    }
    FUN_FFFF03F0(a, &DAT_07FFCD00, 0x40);
    FUN_FFFF03F0(b, DAT_07FFCD00.unk40, 0x40);
}
