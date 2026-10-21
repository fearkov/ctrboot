// FUN_FFFF8D50 shares this file with FUN_FFFFA408, the section loader it calls. The file defines the boot device's
// read functions with the FIRM header they loaded (0xFFF000C8..0xFFF000DF) and the FIRM partitions' boot priorities
// and results (0xFFF005C8..0xFFF00607), each group in a section of its own that the build places at that address.
// armcc lays out only the variables the file's functions use, in definition order: FUN_FFFFA408 uses the three
// section copy functions, which puts the loaded header at base + 0x14 as in the dump. The read functions are
// separate variables, not a struct: armcc loads the base of a scalar into the register that then takes the function
// pointer (ldr r3, =base; ldr r3, [r3, #4]), as the dump does, and the base of a struct member into r0, which also
// changes the registers and spills of the whole function.
#include "types.h"

extern "C" void *memset(void *, int, unsigned int);

// Reads size bytes at the byte offset src of the boot device into dst; nonzero when that worked.
typedef u32 (*Unk_Read)(void *dst, u32 src, u32 size);
// Copies size bytes at the byte offset src of the boot device to the address dst; nonzero when that worked.
typedef u32 (*Unk_Copy)(u32 dst, u32 src, u32 size);

// A section of a FIRM header: where it sits in the file, where it goes, how big it is, how it is copied
// and its hash.
struct Unk_FFFFA408_Section {
    u32 unk00;
    u32 unk04;
    u32 unk08;
    u32 unk0C;
    u8 unk10[0x20];
};

// A FIRM header: the magic "FIRM", the boot priority, then the four sections.
struct Unk_FFFFA408 {
    u32 unk00;
    u32 unk04;
    u8 pad08[0x38];
    Unk_FFFFA408_Section unk40[4];
};

// The NAND's NCSD header: the partitions' filesystem and crypt types, their offsets and sizes in media units,
// and the media unit size (0x200 << unk18E).
struct Unk_07FFB900 {
    u8 pad000[0x110];
    u8 unk110[8];
    u8 unk118[8];
    struct {
        u32 unk0;
        u32 unk4;
    } unk120[8];
    u8 pad160[0x2E];
    u8 unk18E;
};

// A range that sections must stay out of.
struct Unk_FFFFB088 {
    u32 unk0;
    u32 unk4;
};

extern Unk_FFFFB088 DAT_FFFFB088[7];
extern Unk_07FFB900 DAT_07FFB900;
extern Unk_FFFFA408 DAT_07FFBB00;

// The boot device's read functions (installed by FUN_FFFF8FC0): the NCSD header read (zero for a device without
// one), the FIRM header read and the section copies for copy methods 0, 1 and 2; then the FIRM header that was
// loaded (see FUN_FFFF8D30 and FUN_FFFF8D40).
#pragma arm section rwdata = "data.FFF000C8"
static Unk_Read sReadNcsd;
static Unk_Read sReadFirm;
static Unk_Copy sCopy0;
static Unk_Copy sCopy1;
static Unk_Copy sCopy2;
static Unk_FFFFA408 *sFirm;
#pragma arm section

// The boot priority and the result of each NAND partition (see FUN_FFFF8D24).
#pragma arm section zidata = "bss.FFF005C8"
static u32 sPriorities[8];
static s32 sResults[8];
#pragma arm section

extern "C" void FUN_FFFFAD18();
extern "C" u32 FUN_FFFFAC56(const u8 *hash);
extern "C" void FUN_FFFF898C(u32 slot);
extern "C" void FUN_FFFF95BC(void *dst, u32 size);
extern "C" u32 FUN_FFFFA4C4(Unk_07FFB900 *ncsd, u32 key);
extern "C" u32 FUN_FFFF8C8C(Unk_FFFFA408 *firm, u32 key);

// Copies the sections of a FIRM header from the boot device at base plus their offsets with the copy function of
// their method, unless they would land in a protected range, and checks their hashes; nonzero when all went well.
u32 FUN_FFFFA408(Unk_FFFFA408 *firm, u32 base)
{
    if (firm == 0) {
        return 0;
    }
    for (int i = 0; i < 4; i++) {
        Unk_FFFFA408_Section *section = &firm->unk40[i];
        if (section->unk08 == 0) {
            continue;
        }
        u32 start = section->unk04;
        u32 end = start + section->unk08;
        for (u32 j = 0; j < 7; j++) {
            if (DAT_FFFFB088[j].unk0 <= start && start < DAT_FFFFB088[j].unk4) {
                return 0;
            }
            if (DAT_FFFFB088[j].unk0 <= end && end < DAT_FFFFB088[j].unk4) {
                return 0;
            }
        }
        FUN_FFFFAD18();
        Unk_Copy copy;
        switch (section->unk0C) {
        case 2:
            copy = sCopy2;
            break;
        case 0:
            copy = sCopy0;
            break;
        case 1:
            copy = sCopy1;
            break;
        default:
            goto verify;
        }
        if (copy == 0) {
            return 0;
        }
        {
            u32 offset = section->unk00 + base;
            if (copy(section->unk04, offset, section->unk08) == 0) {
                return 0;
            }
        }
    verify:
        if (FUN_FFFFAC56(section->unk10) == 0) {
            return 0;
        }
    }
    return 1;
}

// Zeroes size bytes of words. armcc writes a memset of a small array in place as stores; through this helper it
// calls __aeabi_memclr4, as the dump does.
static inline void ClearWords(u32 *p, u32 size)
{
    memset(p, 0, size);
}

// Boots from NAND at base: reads and checks the NCSD header, reads the header of each FIRM partition and keeps its
// boot priority, then loads the partition with the highest priority, falling back to the next one when that fails.
// Returns 0, or the error of the last attempt; each partition's result is kept in sResults.
s32 FUN_FFFF8D50(u32 base)
{
    Unk_07FFB900 *ncsd = &DAT_07FFB900;
    s32 result = -1;
    u32 offsets[8];
    Unk_FFFFA408 *firm = &DAT_07FFBB00;
    u32 ncsdOffsets[1];
    u32 n;
    s32 i;

    ClearWords(ncsdOffsets, sizeof(ncsdOffsets));
    for (i = 0; i < 8; i++)
        sResults[i] = -1;
    sFirm = 0;
    if (sReadNcsd == 0 || sReadFirm == 0)
        return -4;

    for (n = 0; n < sizeof(ncsdOffsets) / sizeof(ncsdOffsets[0]); n++) {
        s32 err;
        FUN_FFFF95BC(ncsd, 0x200);
        if (!sReadNcsd(ncsd, ncsdOffsets[n] + base, 0x200))
            err = -17;
        else if (!FUN_FFFFA4C4(ncsd, 3))
            err = -18;
        else
            break;
        result = err;
    }
    if (n == sizeof(ncsdOffsets) / sizeof(ncsdOffsets[0]))
        return result;

    FUN_FFFF898C(6);
    for (i = 0; i < 8; i++) {
        if (ncsd->unk110[i] == 3 && ncsd->unk118[i] == 2) {
            u32 offset = ncsd->unk120[i].unk0;
            offsets[i] = offset << ncsd->unk18E << 9;
            FUN_FFFF95BC(firm, 0x200);
            if (!sReadFirm(firm, offsets[i] + base, 0x200)) {
                sResults[i] = -33;
            } else if (firm->unk00 == 0x4D524946) {
                sPriorities[i] = firm->unk04;
                continue;
            } else {
                sResults[i] = -8;
            }
        }
        offsets[i] = 0;
    }

    s32 best;
    do {
        result = -1;
        best = -1;
        for (i = 0; i < 8; i++) {
            if (offsets[i] != 0) {
                if (best < 0 || sPriorities[best] < sPriorities[i])
                    best = i;
                else
                    sResults[i] = -9;
            }
        }
        if (best < 0)
            break;
        FUN_FFFF95BC(firm, 0x200);
        if (!sReadFirm(firm, offsets[best] + base, 0x200)) {
            offsets[best] = 0;
            result = -33;
        } else if (!FUN_FFFF8C8C(firm, 1)) {
            offsets[best] = 0;
            result = -34;
        } else if (!FUN_FFFFA408(firm, offsets[best] + base)) {
            offsets[best] = 0;
            result = -49;
        } else {
            sFirm = firm;
            result = 0;
        }
        sResults[best] = result;
    } while (result != 0);
    return result;
}
