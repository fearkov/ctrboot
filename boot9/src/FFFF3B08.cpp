// Feeds 0x200 bytes from the FIFO at fifo through the AES engine into the buffer at DAT_FFF001A0.unk0,
// four words at a time, and gives up after 0x1298A8 passes with 0x8000. The separate tries++ statement and
// the declaration order decide which local armcc keeps in a register: with them dst is the one it spills.
#include "types.h"

struct Unk_FFF001A0 {
    u32 *unk0;
    u32 unk4;
};

struct Unk_10009000 {
    u32 unk00;
    u32 unk04;
    u32 unk08;
    u32 unk0C;
};

extern Unk_FFF001A0 DAT_FFF001A0;
extern volatile Unk_10009000 DAT_10009000;

extern "C" u32 FUN_FFFF8930();
extern "C" u32 FUN_FFFF8940();

u32 FUN_FFFF3B08(volatile u32 *fifo)
{
    u32 tries = 0;
    u32 in = 0x200;
    u32 out = 0x200;
    u32 *dst = DAT_FFF001A0.unk0;
    while (in | out) {
        while (in != 0 && 0x10 - FUN_FFFF8930() >= 4) {
            DAT_10009000.unk08 = *fifo;
            DAT_10009000.unk08 = *fifo;
            DAT_10009000.unk08 = *fifo;
            DAT_10009000.unk08 = *fifo;
            in -= 0x10;
        }
        if (out != 0 && FUN_FFFF8940() >= 4) {
            *dst++ = DAT_10009000.unk0C;
            *dst++ = DAT_10009000.unk0C;
            *dst++ = DAT_10009000.unk0C;
            *dst++ = DAT_10009000.unk0C;
            out -= 0x10;
        }
        tries++;
        if (tries > 0x1298A7) {
            return 0x8000;
        }
    }
    DAT_FFF001A0.unk0 += 0x80;
    return 0;
}
