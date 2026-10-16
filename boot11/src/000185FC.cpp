#include "types.h"

struct Unk_000185FC {
    u8 pad0[4];
    u16 unk4;
};

extern "C" Unk_000185FC* FUN_00018670(u32 index);
extern "C" u32 FUN_00018EF4(u32 index);
extern "C" void FUN_00011398(u32 start, u32 size);

void FUN_000185FC(u32 index)
{
    Unk_000185FC* info = FUN_00018670(index);
    u32 buffer = FUN_00018EF4(index);
    FUN_00011398(buffer, info->unk4 * 0x3C0);
}
