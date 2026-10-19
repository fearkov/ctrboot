#include "types.h"

struct Unk_10202000 {
    u32 unk0;
    u32 unk4;
    u32 unk8;
};

struct Unk_Surface {
    u8 pad0[4];
    u16 width;
};

typedef void (*PutCharFunc)(u32 screen, u32 x, u32 y, u32 color, u32 ch);

extern "C" Unk_Surface *FUN_00018670(u32 screen);
extern volatile Unk_10202000 DAT_10202000;

void FUN_000189A0(u32 screen, u32 x, u32 y, u32 color, const char *str, PutCharFunc putChar, u32 margin, u32 lineGap)
{
    Unk_Surface *surface = FUN_00018670(screen);
    u32 startX = x;
    u32 advance = (u8)(margin + 1);
    if (DAT_10202000.unk8 & 0x200) {
        advance = (advance & 0x7F) << 1;
    }
    for (; *str != 0; str++) {
        if (*str == '\n') {
            x = startX;
            y += lineGap + 1;
        } else {
            putChar(screen, x, y, color, *str);
            x += advance;
            if (margin * 2 + x + 1 >= surface->width) {
                x = startX;
                y += lineGap + 1;
            }
        }
    }
}
