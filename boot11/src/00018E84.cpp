#include "types.h"

struct Unk_10202204 {
    u32 unk0;
    u8 pad4[0x7FC];
};

extern "C" void FUN_000122FC(const u8* src, u32* dst, u32 size);
extern volatile Unk_10202204 DAT_10202204[];

u32 FUN_00018E84(s32 index, u32 color)
{
    volatile u32* reg = &DAT_10202204[index].unk0;
    u32 value = *reg;
    *reg = (1u << 24) + (((color >> 8) & 0xFF) << 16) | (((color >> 16) & 0xFF) << 8) | (color >> 24);
    FUN_000122FC((const u8*)&value, &value, 4);
    return value;
}
