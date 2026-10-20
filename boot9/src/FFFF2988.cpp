// FUN_FFFF2988 shares this file with FUN_FFFF5730, FUN_FFFF5BBC and FUN_FFFF5C10, the driver functions that use the
// two cards' contexts. The file defines the SD/MMC driver's zero-initialized RAM in a section of its own that the
// build places at 0xFFF00250: the timeout alarm, the two cards' contexts and the SD status buffer. armcc lays out
// the variables the file's functions use in definition order and reaches them as that section's base plus an
// offset, which it computes again after a call: FUN_FFFF2988 finds the SD status buffer at base + 0xF8 that way.
// Without the card functions armcc would place the buffer right after the alarm, at base + 0x30.
#include "types.h"

// An alarm (FUN_FFFF1E40, FUN_FFFF2130), kept in a list sorted by the time it fires.
struct Unk_FFFF17C8 {
    void (*unk0)(void *);
    void *unk4;
    u32 unk8;
    u8 padC[4];
    u64 unk10;
    Unk_FFFF17C8 *unk18;
    Unk_FFFF17C8 *unk1C;
    u64 unk20;
    u64 unk28;
};

// A card's size (FUN_FFFF5068, FUN_FFFF5092).
struct Unk_FFFF5068 {
    u8 unk00;
    u8 pad01[3];
    u32 unk04;
    u32 unk08;
};

// A card's context: flags (initialized, MMC, SD, high capacity), CID, CSD, OCR, SCR, RCA, error bits, status,
// the controller's clock and option registers, the size and error counts.
struct Unk_FFF00280 {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
    u8 unk4[0x10];
    u8 unk14[0x10];
    u32 unk24;
    u8 unk28[8];
    u16 unk30;
    u8 pad32[2];
    u32 unk34;
    u32 unk38;
    u16 unk3C;
    u16 unk3E;
    Unk_FFFF5068 unk40;
    u8 pad4C[4];
    u32 unk50;
    u8 pad54[4];
    u32 unk58;
    u8 pad5C[8];
};

// The driver's state: unk3 refuses initialization, unk1C is the controller block, unk20 the selected unit
// (0x200 or 0x201) and unk24 its context.
struct Unk_FFF0009C {
    u8 pad00[3];
    u8 unk3;
    u8 pad04[0x18];
    u32 unk1C;
    u32 unk20;
    Unk_FFF00280 *unk24;
};

extern Unk_FFF0009C DAT_FFF0009C;

// The timeout alarm, the contexts of units 0x200 and 0x201 and the SD status, at 0xFFF00250, 0xFFF00280,
// 0xFFF002E4 and 0xFFF00348.
#pragma arm section zidata = "bss.FFF00250"
static Unk_FFFF17C8 sAlarm;
static Unk_FFF00280 sCard0;
static Unk_FFF00280 sCard1;
static u8 sSdStatus[0x40];
#pragma arm section

extern "C" u32 FUN_FFFF06EC();
extern "C" void FUN_FFFF0700(u32 state);
extern "C" void *FUN_FFFF056C(void *dst, u32 value, u32 size);
extern "C" void FUN_FFFF19D4(u64 value);
extern "C" void FUN_FFFF1E40(Unk_FFFF17C8 *alarm);
extern "C" void FUN_FFFF2920(u32 time);
extern "C" void FUN_FFFF3D98(u16 rca, u8 *scr);
extern "C" void FUN_FFFF3E28(u16 rca, u8 *status);
extern "C" void FUN_FFFF4134(u32 wide, u16 rca);
extern "C" void FUN_FFFF4190(u16 rca, u32 wide);
extern "C" void FUN_FFFF42B4(u16 rca);
extern "C" void FUN_FFFF4308(u16 rca);
extern "C" void FUN_FFFF4398(u16 rca, u8 *csd);
extern "C" void FUN_FFFF487A(u32 unit);
extern "C" void FUN_FFFF48F6(u32 unit);
extern "C" u32 FUN_FFFF4998(u32 unit);
extern "C" void FUN_FFFF4CA4(u32 unit, u16 *out);
extern "C" void FUN_FFFF4CB4(u32 unit, u16 *out);
extern "C" void FUN_FFFF4CC4(u32 unit);
extern "C" void FUN_FFFF4D84(u32 unit, u32 mode);
extern "C" void FUN_FFFF4E1C(u32 unit, u16 length);
extern "C" void FUN_FFFF4E38(u32 unit, u32 wide);
extern "C" void FUN_FFFF4EA4(u32 unit);
extern "C" void FUN_FFFF4EB8(u32 unit);
extern "C" void FUN_FFFF4ECC(u32 unit, u16 value);
extern "C" void FUN_FFFF4EDA(u32 unit, u16 value);
extern "C" void FUN_FFFF5068(u8 *csd, Unk_FFFF5068 *size);
extern "C" void FUN_FFFF5092(u8 *csd, u8 *status, Unk_FFFF5068 *size);
extern "C" void FUN_FFFF5178(u32 bits);
extern "C" void FUN_FFFF5194(u8 *cid);
extern "C" void FUN_FFFF51CC(u16 rca);
extern "C" void FUN_FFFF5240();
extern "C" void FUN_FFFF529C(bool hcs, u32 *ocr);
extern "C" void FUN_FFFF52FC(u16 rca);
extern "C" void FUN_FFFF5334(u16 rca, u8 *csd);
extern "C" void FUN_FFFF538C();
extern "C" void FUN_FFFF53AC(u32 *ocr);
extern "C" void FUN_FFFF53E8(u16 *rca);
extern "C" void FUN_FFFF545C(u32 length);
extern "C" void FUN_FFFF54D0(u16 rca);
extern "C" u8 FUN_FFFF5A56(u8 *scr);
extern "C" u32 FUN_FFFF5A62(u8 *csd);
extern "C" u32 FUN_FFFF5A7C(u8 *scr);
extern "C" void FUN_FFFF5CAC(u32 bits);
extern "C" void FUN_FFFF5CC8(u32 unit, u8 *csd);
extern "C" void FUN_FFFF5CEE(u32 unit);

// Brings the card up: reset, operating conditions (SD, or MMC when the SD command fails), CID, RCA, CSD,
// selection, block length, bus width and speed, then the size. On an error it resets the card and returns
// the error bits.
u32 FUN_FFFF2988()
{
    u32 state;
    u32 error;
    Unk_FFF00280 *card;
    bool hcs;
    u32 ifCond;
    u16 rca;
    u32 *ocr;
    u8 *ccs;

    state = FUN_FFFF06EC();
    if (DAT_FFF0009C.unk3) {
        DAT_FFF0009C.unk24->unk34 = 0x800000;
        FUN_FFFF0700(state);
        return DAT_FFF0009C.unk24->unk34;
    }
    DAT_FFF0009C.unk24->unk34 = 0;
    FUN_FFFF0700(state);
    DAT_FFF0009C.unk24->unk38 = 0;
    DAT_FFF0009C.unk24->unk1 = 0;
    DAT_FFF0009C.unk24->unk3 = 0;
    DAT_FFF0009C.unk24->unk2 = 0;
    FUN_FFFF4EB8(DAT_FFF0009C.unk1C);
    FUN_FFFF5CEE(DAT_FFF0009C.unk1C);
    FUN_FFFF487A(DAT_FFF0009C.unk1C);
    FUN_FFFF4EA4(DAT_FFF0009C.unk1C);
    FUN_FFFF19D4(1000);
    FUN_FFFF2920(500);
    FUN_FFFF5240();
    FUN_FFFF1E40(&sAlarm);
    if (DAT_FFF0009C.unk24->unk34 != 0) {
        goto fail;
    }
    FUN_FFFF19D4(1000);
    DAT_FFF0009C.unk24->unk30 = 0;
    FUN_FFFF2920(500);
    FUN_FFFF538C();
    FUN_FFFF1E40(&sAlarm);
    if (DAT_FFF0009C.unk24->unk34 == 0) {
        ifCond = 1;
    } else {
        ifCond = 0;
    }
    FUN_FFFF2920(2000);
    while (!(DAT_FFF0009C.unk24->unk34 & 0x200)) {
        FUN_FFFF5178(~0x200);
        FUN_FFFF51CC(DAT_FFF0009C.unk24->unk30);
        FUN_FFFF5178(0x100);
        card = DAT_FFF0009C.unk24;
        error = card->unk34;
        if (error == 0) {
            rca = card->unk30;
            ocr = &card->unk24;
            ccs = &card->unk3;
            if (ifCond) {
                hcs = true;
            } else {
                hcs = false;
            }
            while (DAT_FFF0009C.unk24->unk34 == 0) {
                FUN_FFFF529C(hcs, ocr);
                if (DAT_FFF0009C.unk24->unk34 != 0) {
                    break;
                }
                if ((s32)*ocr < 0) {
                    if (*ocr & 0x40000000) {
                        *ccs = 1;
                    } else {
                        *ccs = 0;
                    }
                    break;
                }
                FUN_FFFF51CC(rca);
            }
            if (DAT_FFF0009C.unk24->unk34 == 0) {
                DAT_FFF0009C.unk24->unk2 = 1;
                break;
            }
        } else if (error == 8) {
            FUN_FFFF5178(~0x200);
            ocr = &DAT_FFF0009C.unk24->unk24;
            while (DAT_FFF0009C.unk24->unk34 == 0) {
                FUN_FFFF53AC(ocr);
                if (DAT_FFF0009C.unk24->unk34 != 0) {
                    break;
                }
                if ((s32)*ocr < 0) {
                    break;
                }
            }
            if (DAT_FFF0009C.unk24->unk34 == 0) {
                DAT_FFF0009C.unk24->unk1 = 1;
                break;
            }
        }
    }
    FUN_FFFF1E40(&sAlarm);
    if (DAT_FFF0009C.unk24->unk34 != 0) {
        if (DAT_FFF0009C.unk24->unk34 & 0x200) {
            FUN_FFFF5178(0x200);
            FUN_FFFF5CAC(0x400);
        }
        goto fail;
    }
    FUN_FFFF2920(3500);
    while (!(DAT_FFF0009C.unk24->unk34 & 0x200)) {
        FUN_FFFF5178(~0x200);
        FUN_FFFF5194(DAT_FFF0009C.unk24->unk4);
        if (DAT_FFF0009C.unk24->unk34 == 0) {
            break;
        }
    }
    if (DAT_FFF0009C.unk24->unk34 != 0) {
        goto fail;
    }
    if (DAT_FFF0009C.unk24->unk1) {
        FUN_FFFF54D0(1);
        FUN_FFFF5178(0x100);
        if (DAT_FFF0009C.unk24->unk34 != 0) {
            goto fail;
        }
        DAT_FFF0009C.unk24->unk30 = 1;
    } else {
        do {
            FUN_FFFF53E8(&DAT_FFF0009C.unk24->unk30);
            if (DAT_FFF0009C.unk24->unk34 != 0) {
                goto fail;
            }
        } while (DAT_FFF0009C.unk24->unk30 == 0);
    }
    {
        Unk_FFF00280 *c = DAT_FFF0009C.unk24;
        FUN_FFFF5334(c->unk30, c->unk14);
    }
    if (DAT_FFF0009C.unk24->unk34 != 0) {
        goto fail;
    }
    FUN_FFFF19D4(62);
    FUN_FFFF4EB8(DAT_FFF0009C.unk1C);
    FUN_FFFF5CC8(DAT_FFF0009C.unk1C, DAT_FFF0009C.unk24->unk14);
    FUN_FFFF4EA4(DAT_FFF0009C.unk1C);
    FUN_FFFF52FC(DAT_FFF0009C.unk24->unk30);
    if (DAT_FFF0009C.unk24->unk34 != 0) {
        goto fail;
    }
    FUN_FFFF1E40(&sAlarm);
    FUN_FFFF4E1C(DAT_FFF0009C.unk1C, 0x200);
    FUN_FFFF2920(500);
    FUN_FFFF545C(0x200);
    FUN_FFFF1E40(&sAlarm);
    if (DAT_FFF0009C.unk24->unk34 != 0) {
        goto fail;
    }
    if (DAT_FFF0009C.unk24->unk2) {
        FUN_FFFF42B4(DAT_FFF0009C.unk24->unk30);
        if (DAT_FFF0009C.unk24->unk34 != 0) {
            goto fail;
        }
    }
    if (DAT_FFF0009C.unk24->unk2) {
        {
            Unk_FFF00280 *c = DAT_FFF0009C.unk24;
            FUN_FFFF4190(c->unk30, 0);
        }
        if (DAT_FFF0009C.unk24->unk34 != 0) {
            goto fail;
        }
        {
            Unk_FFF00280 *c = DAT_FFF0009C.unk24;
            FUN_FFFF3D98(c->unk30, c->unk28);
        }
        if (DAT_FFF0009C.unk24->unk34 != 0) {
            goto fail;
        }
        if (FUN_FFFF5A7C(DAT_FFF0009C.unk24->unk28)) {
            FUN_FFFF4190(DAT_FFF0009C.unk24->unk30, 1);
            if (DAT_FFF0009C.unk24->unk34 != 0) {
                goto fail;
            }
        }
        if (FUN_FFFF5A56(DAT_FFF0009C.unk24->unk28)) {
            rca = DAT_FFF0009C.unk24->unk30;
            FUN_FFFF4398(rca, DAT_FFF0009C.unk24->unk14);
            if (DAT_FFF0009C.unk24->unk34 != 0) {
                goto fail;
            }
        }
    } else {
        if (FUN_FFFF5A62(DAT_FFF0009C.unk24->unk14)) {
            FUN_FFFF4134(1, DAT_FFF0009C.unk24->unk30);
            if (DAT_FFF0009C.unk24->unk34 != 0) {
                FUN_FFFF5178(~0x200);
                FUN_FFFF4134(0, DAT_FFF0009C.unk24->unk30);
                if (DAT_FFF0009C.unk24->unk34 != 0) {
                    FUN_FFFF5178(~0x200);
                    FUN_FFFF4E38(DAT_FFF0009C.unk1C, 0);
                }
            }
            FUN_FFFF4308(DAT_FFF0009C.unk24->unk30);
            if (DAT_FFF0009C.unk24->unk34 != 0) {
                goto fail;
            }
        } else {
            FUN_FFFF4E38(DAT_FFF0009C.unk1C, 0);
        }
    }
    {
        Unk_FFF00280 *c = DAT_FFF0009C.unk24;
        if (c->unk2) {
            FUN_FFFF3E28(c->unk30, sSdStatus);
            if (DAT_FFF0009C.unk24->unk34 != 0) {
                goto fail;
            }
            c = DAT_FFF0009C.unk24;
            FUN_FFFF5092(c->unk14, sSdStatus, &c->unk40);
        } else {
            FUN_FFFF5068(c->unk14, &c->unk40);
        }
    }
    FUN_FFFF19D4(62);
    FUN_FFFF4EB8(DAT_FFF0009C.unk1C);
    FUN_FFFF48F6(DAT_FFF0009C.unk1C);
    FUN_FFFF4EA4(DAT_FFF0009C.unk1C);
    error = DAT_FFF0009C.unk24->unk34;
    if (error == 0) {
        DAT_FFF0009C.unk24->unk0 = 1;
    }
    return error;
fail:
    FUN_FFFF1E40(&sAlarm);
    state = FUN_FFFF06EC();
    error = DAT_FFF0009C.unk24->unk34;
    DAT_FFF0009C.unk24->unk34 = 0;
    FUN_FFFF0700(state);
    FUN_FFFF19D4(1000);
    FUN_FFFF2920(500);
    FUN_FFFF5240();
    FUN_FFFF1E40(&sAlarm);
    FUN_FFFF19D4(62);
    FUN_FFFF4EB8(DAT_FFF0009C.unk1C);
    DAT_FFF0009C.unk24->unk34 = error;
    return error;
}

// Clears the context of unit id (0x200 or 0x201) and gives its clock and option registers their defaults.
void FUN_FFFF5730(u32 id)
{
    Unk_FFF00280 *p;
    switch (id) {
    case 0x200:
        p = &sCard0;
        break;
    case 0x201:
        p = &sCard1;
        break;
    default:
        return;
    }
    FUN_FFFF056C(p, 0, sizeof(Unk_FFF00280));
    p->unk0 = 0;
    p->unk1 = 0;
    p->unk2 = 0;
    p->unk3 = 0;
    p->unk34 = 0;
    p->unk50 = 0;
    p->unk58 = 0;
    p->unk3C = 0x40;
    p->unk3E = 0x40EB;
}

// With IRQs masked: clears both units' contexts, resets the controller block, then selects unit 0x201 and loads
// its clock and option registers.
void FUN_FFFF5BBC()
{
    u32 state = FUN_FFFF06EC();
    FUN_FFFF5730(0x200);
    FUN_FFFF5730(0x201);
    FUN_FFFF4CC4(DAT_FFF0009C.unk1C);
    DAT_FFF0009C.unk20 = 0x201;
    DAT_FFF0009C.unk24 = &sCard1;
    FUN_FFFF4ECC(DAT_FFF0009C.unk1C, DAT_FFF0009C.unk24->unk3C);
    FUN_FFFF4EDA(DAT_FFF0009C.unk1C, DAT_FFF0009C.unk24->unk3E);
    FUN_FFFF4D84(DAT_FFF0009C.unk1C, 1);
    FUN_FFFF0700(state);
}

// Switches the card controller to unit id (0x200 or 0x201, its low byte the port): saves the clock and option
// registers into the current unit's context, then loads the new unit's.
u32 FUN_FFFF5C10(u32 id)
{
    Unk_FFF0009C *g = &DAT_FFF0009C;
    u32 cur = g->unk20;
    if (id == cur) {
        return 0;
    }
    u32 count = FUN_FFFF4998(g->unk1C);
    u32 slot = id;
    if (count == 0 || *(u8 *)&slot > count) {
        return 1 << 24;
    }
    FUN_FFFF4CA4(g->unk1C, &g->unk24->unk3C);
    FUN_FFFF4CB4(g->unk1C, &g->unk24->unk3E);
    FUN_FFFF19D4(0x3E);
    FUN_FFFF4EB8(g->unk1C);
    u32 state = FUN_FFFF06EC();
    g->unk20 = id;
    Unk_FFF00280 *ctx;
    if (id == 0x200) {
        ctx = &sCard0;
    } else {
        ctx = &sCard1;
    }
    g->unk24 = ctx;
    FUN_FFFF4ECC(g->unk1C, g->unk24->unk3C);
    FUN_FFFF4EDA(g->unk1C, g->unk24->unk3E);
    u32 mode;
    if (g->unk20 == 0x200) {
        mode = 0;
    } else {
        mode = 1;
    }
    FUN_FFFF4D84(g->unk1C, mode);
    FUN_FFFF0700(state);
    return 0;
}
