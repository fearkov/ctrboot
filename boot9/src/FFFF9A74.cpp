#include "types.h"

struct Unk_080F8000 {
    u8 pad00[0x92];
    u16 unk92;
};

struct Unk_FFF000E8 {
    u8 pad00[0x2C];
    u8 *unk2C;
};

extern Unk_080F8000 DAT_080F8000;
extern u8 DAT_080F9000[];
extern Unk_FFF000E8 DAT_FFF000E8;

extern "C" void FUN_FFFF32A8(u32 address, u8 *dst, u32 size);
extern "C" void FUN_FFFF47D0();

// Reads one 0x4000-byte window from the storage into the RAM buffer that FUN_FFFF330C serves it from.
// With flag 0 that is the window at 0x4000 (buffer at 0x080F9000); otherwise, if unk92 of the header at
// 0x080F8000 is not 0, the window at (unk92 << 19) + 0x3000 (buffer pointed to by DAT_FFF000E8).
void FUN_FFFF9A74(u32 flag)
{
    Unk_080F8000 *hdr = &DAT_080F8000;
    u32 address;
    u8 *dst;
    if (flag == 0) {
        address = 0x4000;
        dst = DAT_080F9000;
    } else {
        u32 count = hdr->unk92;
        if (count == 0) {
            return;
        }
        address = (count << 19) + 0x3000;
        dst = DAT_FFF000E8.unk2C;
    }
    FUN_FFFF32A8(address, dst, 0x4000);
    FUN_FFFF47D0();
}
