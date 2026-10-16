// Built for space like the other SD/MMC helpers of this ROM: the 12-byte frame comes from pushing r1-r3
// (what -Ospace does; -Otime allocates it with sub sp).
#pragma Ospace
#include "types.h"

struct Unk_FFFF5068
{
    u8 unk00;
    u8 pad01[3];
    u32 unk04;
    u32 unk08;
};

extern "C" void FUN_FFFF3EB8(const void *csd, u16 *size, u8 *mult, u8 *length);

// Capacity from the CSD register: (C_SIZE + 1) << (C_SIZE_MULT + READ_BL_LEN - 7), in 512-byte blocks.
void FUN_FFFF5068(const void *csd, Unk_FFFF5068 *out)
{
    u32 size = 0;
    u8 mult;
    u8 length;
    FUN_FFFF3EB8(csd, (u16 *)&size, &mult, &length);
    out->unk04 = (size + 1) << (mult + length - 7);
    out->unk00 = 0;
    out->unk08 = 0;
}
