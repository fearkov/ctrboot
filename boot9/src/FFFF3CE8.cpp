#include "types.h"

struct Unk_FFFF3CD4;

struct Unk_FFF00088 {
    u8 unk0[4];
    Unk_FFFF3CD4 *unk4;
    Unk_FFFF3CD4 *unk8;
    Unk_FFFF3CD4 *unkC;
    Unk_FFFF3CD4 *unk10;
};
extern Unk_FFF00088 DAT_FFF00088;

extern "C" void FUN_FFFF3CD4(Unk_FFFF3CD4 *list);

void FUN_FFFF3CE8(u32 id)
{
    switch (id) {
    case 0x200:
        FUN_FFFF3CD4(DAT_FFF00088.unk8);
        break;
    case 0x201:
        FUN_FFFF3CD4(DAT_FFF00088.unk10);
        break;
    }
}
