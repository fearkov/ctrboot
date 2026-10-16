#include "types.h"

struct Unk_FFF01990 {
    u8 pad00[0x2c];
};

extern Unk_FFF01990 DAT_FFF01990[];
extern "C" void FUN_FFFF0374(const void *src, void *dst, u32 size);

void FUN_FFFF1A84(u32 index, void *dst)
{
    FUN_FFFF0374(&DAT_FFF01990[index], dst, sizeof(Unk_FFF01990));
}
