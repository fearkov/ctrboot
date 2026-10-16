#include "types.h"

struct Unk_10003000 {
    u16 unk0;
    u16 unk2;
};

extern volatile Unk_10003000 DAT_10003000[];

void FUN_FFFF21E8(u32 index)
{
    DAT_10003000[index].unk2 = 0;
}
