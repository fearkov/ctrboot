// The lc0 count is patched through a copy of high (h): with high itself, armcc reloads it into r6 for the test but
// copies it to r2 for the store and builds the address in r6, where the dump stores r6 through an address in r2.
#include "types.h"

// One entry of the table at DAT_FFF01990 (0x2C bytes each): how a DMA channel moves data.
struct Unk_FFF01990 {
    u8 unk00[2];
    u8 unk02[4]; // channel control register value, little-endian
    u16 unk06;
    u8 unk08[2];
    u8 unk0A;
    u8 unk0B;
    u32 unk0C;
    u32 unk10;
    u32 unk14;
    u8 unk18[2];
    u16 unk1A; // added to the destination address after each store
    u8 unk1C;
    u8 unk1D;
    u8 unk1E;
    u8 unk1F;
    u8 unk20;
    u8 unk21[3];
    u32 unk24;
    u8 unk28[4];
};

// Writes a CoreLink DMA-330 channel program into buf that copies size bytes from
// src (or zeroes them when src is 0) to dst, synchronised with peripheral periph
// unless it is -1, and signals event index at the end. Returns the program's length.
u32 FUN_FFFF0CF4(u32 index, u32 src, u32 dst, u32 size, s32 periph, Unk_FFF01990 *config, u8 *buf)
{
    u32 srcBurst = config->unk0C;
    u32 dstBurst = config->unk10;
    s32 burst = config->unk0A > 1 || config->unk0B > 1;
    u32 unit = config->unk06;
    u32 outer = (unit - 1) / config->unk14;
    u32 count = (size - 1) / unit;
    u32 high = outer ? 0 : count >> 8;
    s32 loads = (dstBurst - 1) / srcBurst + 1;
    s32 stores = (srcBurst - 1) / dstBurst + 1;
    u8 *p = buf;
    u32 step = config->unk1A;
    u8 *loop0;
    u8 *loop1 = buf;
    u8 *inst;
    s32 n;

    *p++ = 0xBC; // DMAMOV DAR, 0
    *p++ = 2;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0xBC; // DMAMOV CCR
    *p++ = 1;
    *p++ = config->unk02[0];
    *p++ = config->unk02[1];
    *p++ = config->unk02[2];
    *p++ = config->unk02[3];
    *p++ = 0xBC; // DMAMOV SAR, src
    *p++ = 0;
    *p++ = src;
    *p++ = src >> 8;
    *p++ = src >> 16;
    *p++ = src >> 24;
    *p++ = 0xBC; // DMAMOV DAR, dst
    *p++ = 2;
    *p++ = dst;
    *p++ = dst >> 8;
    *p++ = dst >> 16;
    *p++ = dst >> 24;

    if (periph != -1 && config->unk1D != 0 && config->unk24 == 0) {
        *p++ = 0x35; // DMAFLUSHP
        *p++ = periph << 3;
    }
    u8 *aligned = (u8 *)(((u32)p + 31) & ~31u);
    while (p < aligned) {
        *p++ = 0x18; // DMANOP
    }
    *p++ = 0x20; // DMALP lc0
    *p++ = count;
    loop0 = p;
    u32 h = high;
    if (h != 0) {
        // more than 256 units: lc0 counts the high byte and lc1 the low byte
        p[-1] = h;
        *p++ = 0x22; // DMALP lc1
        *p++ = count;
        loop1 = p;
    }

    if (periph == -1) {
        if (outer != 0) {
            *p++ = 0x22; // DMALP lc1
            *p++ = outer;
            loop1 = p;
        }
        if (src != 0) {
            n = loads;
            while (n-- > 0) {
                *p++ = 0x04; // DMALD
            }
            *p++ = 0x12; // DMARMB
            n = stores;
            while (n-- > 0) {
                *p++ = 0x08; // DMAST
                if (step != 0) {
                    *p++ = 0x56; // DMAADDH DAR
                    *p++ = step;
                    *p++ = step >> 8;
                }
            }
            *p++ = 0x13; // DMAWMB
        } else {
            *p++ = 0x0C; // DMASTZ
            if (step != 0) {
                *p++ = 0x56; // DMAADDH DAR
                *p++ = step;
                *p++ = step >> 8;
            }
            *p++ = 0x13; // DMAWMB
        }
        if (outer != 0) {
            inst = p;
            *p++ = 0x3C; // DMALPEND lc1
            *p++ = inst - loop1;
        }
    } else {
        u8 *last = 0;
        s32 storeSize = (step != 0) * 3 + 2;
        u8 load = 0x05;  // DMALDS
        u8 store = 0x09; // DMASTS
        u8 wait = 0x30;  // DMAWFP single
        if (burst) {
            load = 0x07;  // DMALDB
            store = 0x0B; // DMASTB
            wait = 0x32;  // DMAWFP burst
        }
        *p++ = wait;
        *p++ = periph << 3;
        if (outer != 0) {
            *p++ = 0x22; // DMALP lc1
            *p++ = outer - 1;
            loop1 = p;
        }
        if (src != 0) {
            n = loads;
            while (n-- > 0) {
                *p++ = load;
            }
            *p++ = 0x12; // DMARMB
            last = p - 2;
            n = stores;
            while (n-- > 0) {
                *p++ = store;
                if (step != 0) {
                    *p++ = 0x56; // DMAADDH DAR
                    *p++ = step;
                    *p++ = step >> 8;
                }
            }
            *p++ = 0x13; // DMAWMB
        } else {
            *p++ = 0x0C; // DMASTZ
            if (step != 0) {
                *p++ = 0x56; // DMAADDH DAR
                *p++ = step;
                *p++ = step >> 8;
            }
            *p++ = 0x13; // DMAWMB
        }
        if (outer != 0) {
            // the last pass of the outer loop is unrolled after it
            inst = p;
            *p++ = 0x3C; // DMALPEND lc1
            *p++ = inst - loop1;
            n = loads;
            while (n-- > 0) {
                *p++ = load;
            }
            *p++ = 0x12; // DMARMB
            last = p - 2;
            n = stores;
            while (n-- > 0) {
                *p++ = store;
                if (step != 0) {
                    *p++ = 0x56; // DMAADDH DAR
                    *p++ = step;
                    *p++ = step >> 8;
                }
            }
            *p++ = 0x13; // DMAWMB
        }
        if (config->unk20 == 0) {
            // the last load waits for the peripheral
            wait = 0x25; // DMALDPS
            if (burst) {
                wait = 0x27; // DMALDPB
            }
            p = last;
            *p++ = wait;
            *p++ = periph << 3;
            *p++ = 0x12; // DMARMB
            n = stores;
            while (n-- > 0) {
                *p++ = store;
                if (step != 0) {
                    *p++ = 0x56; // DMAADDH DAR
                    *p++ = step;
                    *p++ = step >> 8;
                }
            }
            *p++ = 0x13; // DMAWMB
        } else {
            // the last store waits for the peripheral
            wait = 0x29; // DMASTPS
            if (burst) {
                wait = 0x2B; // DMASTPB
            }
            p -= storeSize;
            *p++ = wait;
            *p++ = periph << 3;
            if (step != 0) {
                *p++ = 0x56; // DMAADDH DAR
                *p++ = step;
                *p++ = step >> 8;
            }
            *p++ = 0x13; // DMAWMB
        }
    }

    if (high != 0) {
        inst = p;
        *p++ = 0x3C; // DMALPEND lc1
        *p++ = inst - loop1;
    }
    inst = p;
    *p++ = 0x38; // DMALPEND lc0
    *p++ = inst - loop0;
    *p++ = 0x13; // DMAWMB
    if (periph != -1 && config->unk1E != 0) {
        p[0] = 0x35; // DMAFLUSHP
        p[1] = periph << 3;
        p += 2;
    }
    p[0] = 0x34; // DMASEV
    p[1] = index << 3;
    p[2] = 0x00; // DMAEND
    p += 3;
    return p - buf;
}
