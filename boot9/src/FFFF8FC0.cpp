#include "types.h"

// Reads size bytes at the byte offset src of the boot device into dst; nonzero when that worked.
typedef u32 (*Unk_Read)(void *dst, u32 src, u32 size);

// The boot device's read functions (see FUN_FFFF8D50 and FUN_FFFFA408): the NCSD header read (zero for a device
// without one), the FIRM header read, and the section copies for copy methods 0, 1 and 2.
struct Unk_FFF000C8
{
    Unk_Read unk00;
    Unk_Read unk04;
    Unk_Read unk08;
    Unk_Read unk0C;
    Unk_Read unk10;
};

extern Unk_FFF000C8 DAT_FFF000C8;

// Installs the boot device's read functions.
void FUN_FFFF8FC0(Unk_Read ncsd, Unk_Read header, Unk_Read copy0, Unk_Read copy1, Unk_Read copy2)
{
    DAT_FFF000C8.unk00 = ncsd;
    DAT_FFF000C8.unk04 = header;
    DAT_FFF000C8.unk08 = copy0;
    DAT_FFF000C8.unk0C = copy1;
    DAT_FFF000C8.unk10 = copy2;
}
