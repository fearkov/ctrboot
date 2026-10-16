#include "types.h"

extern "C" void FUN_FFFF96EC();
extern "C" u32 FUN_FFFFA5EC();

struct Unk_FFF000E8 {
    u8 unk00[0x24];
    u32 unk24;
};
extern Unk_FFF000E8 DAT_FFF000E8;

u32 FUN_FFFFA5D0()
{
    if (DAT_FFF000E8.unk24 != 0) {
        return 1;
    }
    FUN_FFFF96EC();
    return FUN_FFFFA5EC();
}
