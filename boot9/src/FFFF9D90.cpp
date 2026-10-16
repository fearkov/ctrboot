#include "types.h"

extern "C" u32 FUN_FFFFAD58();
extern "C" void FUN_FFFF05E0(const void *src, void *dst, u32 size);
extern "C" void FUN_FFFF0540(const void *src, void *dst);
extern "C" void FUN_FFFFAC8C();

// A copy of the engine's control state at DAT_FFF00240.
struct Unk_FFF00240 {
    u16 unk0;
    u8 unk2;
    u8 unk3;
    u8 unk4;
    u8 unk5;
    u8 unk6;
    u8 unk7;
    u8 unk8;
    u8 unk9;
};

void FUN_FFFF9D90(const u8 *data, u32 size, Unk_FFF00240 *state)
{
    const u8 *p = data;
    const u8 *end = data + size;
    const u8 *blocksEnd = data + ((size >> 6) << 6);
    while (p < blocksEnd) {
        while (FUN_FFFFAD58()) {
        }
        if ((u32)p & 3) {
            FUN_FFFF05E0(p, (void *)0x1000A080, 0x40);
        } else {
            FUN_FFFF0540(p, (void *)0x1000A080);
        }
        p += 0x40;
    }
    if (p < end) {
        while (FUN_FFFFAD58()) {
        }
        FUN_FFFF05E0(p, (void *)0x1000A080, end - p);
    }
    if (state->unk2) {
        FUN_FFFFAC8C();
    }
}
