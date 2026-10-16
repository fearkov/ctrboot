#include "types.h"

struct Unk_FFF001A8 {
    u8 unk0;
    u8 pad1[3];
    u8 *unk4;
    u32 unk8;
};

struct Unk_10009000 {
    u32 unk00;
    u32 unk04;
    u32 unk08;
    u32 unk0C;
};

extern Unk_FFF001A8 DAT_FFF001A8;
extern volatile Unk_10009000 DAT_10009000;
extern volatile u32 DAT_1000A080;

extern "C" u32 FUN_FFFF8930();
extern "C" u32 FUN_FFFF8940();
extern "C" u32 FUN_FFFFAD58();
extern "C" u32 FUN_FFFFAD68();
extern "C" void FUN_FFFF0540(volatile u32 *src, void *dst);

u32 FUN_FFFF39D0(volatile u32 *fifo)
{
    u32 left;
    u8 *dst;
    u32 tries = 0;
    u32 in = 0x200;
    u32 out = 0x200;
    u32 queued = 0;
    left = 0x200;
    dst = DAT_FFF001A8.unk4;
    while (in | out | left) {
        while (in != 0 && 0x10 - FUN_FFFF8930() >= 4) {
            DAT_10009000.unk08 = *fifo;
            DAT_10009000.unk08 = *fifo;
            DAT_10009000.unk08 = *fifo;
            DAT_10009000.unk08 = *fifo;
            in -= 0x10;
        }
        if (out != 0 && FUN_FFFF8940() >= 4) {
            if (queued == 0) {
                FUN_FFFFAD58();
            }
            if (queued < 0x40) {
                DAT_1000A080 = DAT_10009000.unk0C;
                DAT_1000A080 = DAT_10009000.unk0C;
                DAT_1000A080 = DAT_10009000.unk0C;
                DAT_1000A080 = DAT_10009000.unk0C;
                out -= 0x10;
                queued += 0x10;
            }
        }
        if (queued >= 0x40 && FUN_FFFFAD68()) {
            FUN_FFFF0540(&DAT_1000A080, dst);
            queued -= 0x40;
            dst += 0x40;
            left -= 0x40;
        }
        if (++tries > 0x1298A7) {
            return 0x10000;
        }
    }
    DAT_FFF001A8.unk4 += 0x200;
    return 0;
}
