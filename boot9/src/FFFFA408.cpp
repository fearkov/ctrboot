// Built for space, like the rest of this ROM.
#include "types.h"

// A section of a FIRM header: where it sits in the file, where it goes, how big it is, how it is copied
// and its hash.
struct Unk_FFFFA408_Section {
    u32 unk00;
    u32 unk04;
    u32 unk08;
    u32 unk0C;
    u8 unk10[0x20];
};

struct Unk_FFFFA408 {
    u8 unk00[0x40];
    Unk_FFFFA408_Section unk40[4];
};

// A range that sections must stay out of.
struct Unk_FFFFB088 {
    u32 unk0;
    u32 unk4;
};
extern Unk_FFFFB088 DAT_FFFFB088[7];

typedef u32 (*Unk_Copy)(u32 dst, u32 src, u32 size);

struct Unk_FFF000C8 {
    u8 unk00[8];
    Unk_Copy unk08;
    Unk_Copy unk0C;
    Unk_Copy unk10;
};
extern Unk_FFF000C8 DAT_FFF000C8;

extern "C" void FUN_FFFFAD18();
extern "C" u32 FUN_FFFFAC56(const u8 *hash);

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
            copy = DAT_FFF000C8.unk10;
            break;
        case 0:
            copy = DAT_FFF000C8.unk08;
            break;
        case 1:
            copy = DAT_FFF000C8.unk0C;
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
