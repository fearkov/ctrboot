#include "types.h"

struct Unk_00012F1E {
    u32 unk0;
    u8* unk4;
};

void FUN_00012F1E(Unk_00012F1E* buffer, const u8* src, s32 count)
{
    if (count > 0) {
        u32 n = buffer->unk0;
        if (n > (u32)count)
            n = count;
        for (u32 i = 0; i < n; i++)
            buffer->unk4[i] = src[i];
        buffer->unk0 -= n;
        buffer->unk4 += count;
    }
}
