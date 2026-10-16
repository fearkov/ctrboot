#include "types.h"

// CSD register as the controller returns it (without the CRC byte), read in halfwords.
struct Unk_FFFF5092
{
    u8 pad00[4];
    u16 unk04;
    u16 unk06;
    u8 pad08[6];
    u16 unk0E;
};

struct Unk_FFFF5068
{
    u8 unk00;
    u8 pad01[3];
    u32 unk04;
    u32 unk08;
};

extern "C" void FUN_FFFF3EB8(const void *csd, u16 *size, u8 *mult, u8 *length);

// The read goes through a helper (inlined): written out in place, armcc loads and combines the bytes in another order.
static inline u32 ReadBE32(const u8 *p)
{
    return (p[0] << 24) | (p[1] << 16) | (p[2] << 8) | p[3];
}

// Capacity from the CSD register and size of the protected area from the SD Status, both in 512-byte blocks. Version
// 1.0 of the CSD gives (C_SIZE + 1) << (C_SIZE_MULT + READ_BL_LEN - 7) blocks and a protected area counted in the
// same units; version 2.0 (high capacity) gives (C_SIZE + 1) * 1024 blocks and a protected area in bytes.
void FUN_FFFF5092(const Unk_FFFF5092 *csd, const u8 *status, Unk_FFFF5068 *out)
{
    u32 structure = (csd->unk0E >> 6) & 3;
    u32 area = ReadBE32(status + 4);
    u32 size;
    u8 mult;
    u8 length;
    if (structure == 0) {
        out->unk00 = 0;
        size = 0;
        FUN_FFFF3EB8(csd, (u16 *)&size, &mult, &length);
        u32 shift = mult + length - 7;
        u32 blocks = (size + 1) << shift;
        out->unk08 = area << shift;
        out->unk04 = blocks;
    } else if (structure == 1) {
        out->unk00 = 1;
        size = ((csd->unk06 & 0x3FFF) << 8) | (csd->unk04 >> 8);
        out->unk04 = (size << 10) + (1 << 10);
        out->unk08 = area >> 9;
    } else {
        out->unk00 = 0;
        out->unk04 = 0;
        out->unk08 = 0;
    }
}
