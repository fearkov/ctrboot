// The boot9 main sequence: crypto setup, then the boot attempts (card when Start+Select+X are held, NAND, card),
// each result stored in a byte at 0x1FFFE00C..E.
// The card test of 0x10000010 takes its bit from a variable: "(status & absent) == absent" is what gives
// "movs r0, #1; bics r0, r1" (with the constant written in place armcc tests the bit with lsls #31).
#include "types.h"

struct Unk_10010000
{
    u8 pad00[0x10];
    volatile u8 unk10;
};

struct Unk_10000000
{
    u8 pad00[0x10];
    volatile u8 unk10;
};

struct Unk_1FFFE000
{
    u8 pad00[0xC];
    u8 unk0C;
    u8 unk0D;
    u8 unk0E;
    u8 unk0F;
    u8 unk10[8];
    u32 unk18;
    u32 unk1C;
};

extern Unk_10010000 DAT_10010000;
extern Unk_1FFFE000 DAT_1FFFE000;
extern u32 DAT_FFFFD6E0[4];
extern u32 DAT_FFFFD6F0[4];
extern u32 DAT_FFFFD700[4];
extern u32 DAT_FFFFD710[4];
extern u8 DAT_07FFB800[];

extern "C" void FUN_FFFF2024();
extern "C" void FUN_FFFF1FF8();
extern "C" void FUN_FFFF2220();
extern "C" void FUN_FFFFA850();
extern "C" void FUN_FFFF8594();
extern "C" void FUN_FFFFACF8();
extern "C" void FUN_FFFF89E4();
extern "C" void FUN_FFFF8AA0(u32 slot, u32 mode, const u32 *key);
extern "C" void FUN_FFFF8A64(u32 mode, const u32 *data);
extern "C" void FUN_FFFF898C(u32 slot);
extern "C" u32 FUN_FFFFAC00(u32 *dst);
extern "C" u32 FUN_FFFFAC34(const u8 *data);
extern "C" u32 FUN_FFFFABD8(const void *src, u8 *dst);
extern "C" void FUN_FFFF9014(u32 *src, u32 size);
extern "C" void FUN_FFFF03A4(u32 value, void *dst, u32 size);
extern "C" u32 FUN_FFFF4F94();
extern "C" u64 FUN_FFFF1F70();
extern "C" u32 FUN_FFFFA5D0();
extern "C" void FUN_FFFF8F60();
extern "C" s32 FUN_FFFF95D8(u32 a, u32 b);
extern "C" void FUN_FFFF95A8();
extern "C" u32 FUN_FFFF56C8();
extern "C" u32 FUN_FFFF5774(u32 id);
extern "C" void FUN_FFFF8F14();
extern "C" s32 FUN_FFFF8D50(u32 base);
extern "C" u32 FUN_FFFF8D24(u32 index);
extern "C" void FUN_FFFF5690(u32 id, u32 *error, u32 *status);
extern "C" void FUN_FFFF5644();
extern "C" void FUN_FFFF3668(u8 *out);
extern "C" void FUN_FFFF8F9C();
extern "C" u32 FUN_FFFF8D40();
extern "C" u32 FUN_FFFF8D30();
extern "C" void FUN_FFFF8608();
extern "C" void FUN_FFFF1E20();
extern "C" void FUN_FFFF2214();

void FUN_FFFF8228()
{
    Unk_1FFFE000 *g = &DAT_1FFFE000;
    s32 res;

    FUN_FFFF2024();
    FUN_FFFF1FF8();
    FUN_FFFF2220();
    FUN_FFFFA850();
    FUN_FFFF8594();
    FUN_FFFFACF8();
    FUN_FFFF89E4();

    const u32 *data;
    if (DAT_10010000.unk10) {
        FUN_FFFF8AA0(0x3F, 5, DAT_FFFFD700);
        data = DAT_FFFFD710;
    } else {
        FUN_FFFF8AA0(0x3F, 5, DAT_FFFFD6E0);
        data = DAT_FFFFD6F0;
    }
    FUN_FFFF8A64(5, data);
    FUN_FFFF898C(0x3F);

    {
        u32 otp[0x40];
        if (!FUN_FFFFAC00(otp) || !FUN_FFFFAC34((const u8 *)otp) || !FUN_FFFFABD8(otp, DAT_07FFB800)) {
            FUN_FFFF9014((u32 *)0x10012000, 0x70);
        } else {
            FUN_FFFF9014(&otp[0x24], 0x70);
        }
        FUN_FFFF03A4(0, otp, sizeof(otp));
    }

    if ((FUN_FFFF4F94() & 0xFFF) == 0x40C && g->unk0F) {
        FUN_FFFF1F70();
        FUN_FFFFA5D0();
        u32 status = ((volatile Unk_10000000 *)0x10000000)->unk10;
        u32 absent = 1;
        if ((status & absent) == absent) {
            res = -2;
        } else {
            FUN_FFFF8F60();
            res = FUN_FFFF95D8(0, 2);
        }
        g->unk0D = res;
        FUN_FFFF1F70();
        if (res == 0)
            goto boot;
        FUN_FFFF95A8();
    }

    FUN_FFFF1F70();
    FUN_FFFF898C(6);
    if (FUN_FFFF56C8()) {
        res = -3;
    } else if (FUN_FFFF5774(0x201)) {
        res = -2;
    } else {
        FUN_FFFF8F14();
        res = FUN_FFFF8D50(0);
        for (s32 i = 0; i < 8; i++)
            g->unk10[i] = FUN_FFFF8D24(i);
    }
    g->unk0C = res;
    FUN_FFFF5690(0x201, &g->unk18, &g->unk1C);
    FUN_FFFF5644();
    FUN_FFFF1F70();
    if (res == 0)
        goto boot;

    FUN_FFFF1F70();
    {
        u8 status;
        FUN_FFFF3668(&status);
        if (status & 1) {
            res = -2;
        } else {
            FUN_FFFF8F9C();
            res = FUN_FFFF95D8(0, 2);
        }
    }
    g->unk0E = res;
    FUN_FFFF1F70();
    if (res == 0)
        goto boot;
    FUN_FFFF95A8();
    goto fail;

boot:
    if (FUN_FFFF8D40() && FUN_FFFF8D30()) {
        FUN_FFFF8608();
    } else {
fail:
        FUN_FFFF03A4(0, DAT_07FFB800, 0x3C70);
    }
    FUN_FFFF1E20();
    FUN_FFFF2214();
}
