#include "types.h"

struct Unk_FFF01990 {
    u8 unk0[0x2C];
};

extern Unk_FFF01990 DAT_FFF01990[];

extern "C" void FUN_FFFF0374(const void *src, void *dst, u32 size);

void FUN_FFFF1D64(u32 index, const void *src)
{
    FUN_FFFF0374(src, &DAT_FFF01990[index], sizeof(Unk_FFF01990));
}
