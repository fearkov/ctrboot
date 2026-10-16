#include "types.h"

struct Unk_FFF001A0 {
    u8 *unk0;
    u32 unk4;
};

extern Unk_FFF001A0 DAT_FFF001A0;
extern u32 (*DAT_FFF000A8)();
extern u32 (*DAT_FFF000AC)(volatile u32 *fifo);
extern void (*DAT_FFF000B0)();

extern "C" u32 FUN_FFFF3B9C();
extern "C" u32 FUN_FFFF3B08(volatile u32 *fifo);
extern "C" void FUN_FFFF3B00();
extern "C" u32 FUN_FFFF2E38(u32 address, u32 count);

u32 FUN_FFFF3930(u32 address, u32 count, u8 *dst)
{
    DAT_FFF001A0.unk0 = dst;
    DAT_FFF001A0.unk4 = count << 9;
    DAT_FFF000A8 = FUN_FFFF3B9C;
    DAT_FFF000AC = FUN_FFFF3B08;
    DAT_FFF000B0 = FUN_FFFF3B00;
    return FUN_FFFF2E38(address, count);
}
