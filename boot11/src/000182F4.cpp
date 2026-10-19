// Called by the hook FUN_000181F4 when there is an entry point: copies the eight 0x100-byte blocks the table at
// 0x1FFE8000 points to into 0x1FFFD000, then clears the 0x2470 bytes at 0x1FFFA000, fills them with data from the ROM
// and cleans both areas from the data cache.
// 0x1FFFD000 is written as an address at each use, not as an extern array: only then does armcc keep it in a register
// across the loop for the cache clean, and load it after the table's address, as the dump does. The table entry is
// read before the call, which gives the dump's order of the argument instructions.
#include "types.h"

struct Unk_1FFFA000 {
    u8 unk0[0x80];
    u8 unk80[0x80];
    u8 unk100[0x80];
    u8 unk180[0x80];
    u8 unk200[0x80];
    u8 unk280[0x80];
    u8 unk300[0x40];
    u8 unk340[0x40];
    u8 unk380[0x30];
    u8 unk3B0[0x30];
    u8 unk3E0[0x1048];
    u8 unk1428[0x1048];
};

extern Unk_1FFFA000 DAT_1FFFA000;
extern const void* DAT_1FFE8000[];
extern const u8 DAT_0001C498[];
extern const u8 DAT_0001C4C8[];
extern const u8 DAT_0001C4F8[];
extern const u8 DAT_0001C538[];
extern const u8 DAT_0001C578[];
extern const u8 DAT_0001C5F8[];
extern const u8 DAT_0001C678[];
extern const u8 DAT_0001C6F8[];
extern const u8 DAT_0001C778[];
extern const u8 DAT_0001C7F8[];
extern const u8 DAT_00019408[];
extern const u8 DAT_0001A450[];

extern "C" void FUN_00011730(const void* src, void* dst, u32 size);
extern "C" void FUN_000116E4(u32 value, void* dst, u32 size);
extern "C" void FUN_00011374(void* start, s32 size);

void FUN_000182F4()
{
    Unk_1FFFA000* d = &DAT_1FFFA000;
    for (s32 i = 0; i < 8; i++) {
        const void* src = DAT_1FFE8000[i];
        FUN_00011730(src, (u8*)0x1FFFD000 + i * 0x100, 0x100);
    }
    FUN_00011374((void*)0x1FFFD000, 0x800);
    FUN_000116E4(0, d, sizeof(*d));
    FUN_00011730(DAT_0001C678, d->unk80, sizeof(d->unk80));
    FUN_00011730(DAT_0001C7F8, d->unk200, sizeof(d->unk200));
    FUN_00011730(DAT_0001C5F8, d->unk0, sizeof(d->unk0));
    FUN_00011730(DAT_0001C6F8, d->unk100, sizeof(d->unk100));
    FUN_00011730(DAT_0001C778, d->unk180, sizeof(d->unk180));
    FUN_00011730(DAT_0001C498, d->unk380, sizeof(d->unk380));
    FUN_00011730(DAT_0001C4C8, d->unk3B0, sizeof(d->unk3B0));
    FUN_00011730(DAT_0001C4F8, d->unk340, sizeof(d->unk340));
    FUN_00011730(DAT_0001C538, d->unk300, sizeof(d->unk300));
    FUN_00011730(DAT_0001C578, d->unk280, sizeof(d->unk280));
    FUN_00011730(DAT_00019408, d->unk3E0, sizeof(d->unk3E0));
    FUN_00011730(DAT_0001A450, d->unk1428, sizeof(d->unk1428));
    FUN_00011374(d, sizeof(*d));
}
