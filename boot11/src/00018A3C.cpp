// The glyph's row goes through a u8 that is then reused for the row's first character (r = r * perRow + 0x20), which
// gives the dump's "mov r5, r1" copy, and i is set to 0 before the shift is worked out, in the dump's order.
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

extern "C" Unk_Surface *FUN_00018670(u32 screen);
extern "C" u32 FUN_00018EF4(u32 screen);
extern volatile Unk_10202000 DAT_10202000;

// Draws character ch at (x, y) on screen in color, from a font of glyphs width bits wide and height rows tall, packed
// perRow to a 32-bit font row from 0x20 on; with bit 9 of 0x10202008 set each pixel is drawn twice. Does nothing for
// a character past the font or a glyph that would leave the screen.
void FUN_00018A3C(u32 screen, u32 x, u32 y, u32 color, u32 ch, const u32 *font, u32 width, u32 height)
{
    Unk_Surface *surface = FUN_00018670(screen);
    u32 base = FUN_00018EF4(screen) - y * 4 + x * 0x3C0 + 0x3BC;
    u32 perRow = width == 3 ? 10 : 6;
    u32 last = width == 3 ? 0x5B : 0x7F;
    u32 scale = 1;
    if (DAT_10202000.unk8 & 0x200)
        scale = 2;
    if (0xF0 - (y - width) + (x + height) * 0xF0 < (surface->width >> (scale - 1)) * 0xF0 && ch >= 0x20 && ch <= last) {
        s32 rem = ch - 0x20;
        u32 row = 0;
        while ((rem -= perRow) >= 0)
            row++;
        u8 r = row;
        font += r * height;
        r = r * perRow + 0x20;
        u32 col = ch - r;
        u32 i = 0;
        u32 shift = width * (perRow - col - 1);
        for (u32 stride = scale * 0x3C0; i < height; i++) {
            u32 p = base - i * 4;
            for (u32 j = 0; j < width; j++) {
                if ((font[i] >> (width - j + shift - 1)) & 1) {
                    *(u32 *)p = color;
                    if (scale == 2)
                        *(u32 *)(p + 0x3C0) = color;
                }
                p += stride;
            }
        }
    }
}
