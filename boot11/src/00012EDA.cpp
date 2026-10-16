#include "types.h"

struct Unk_00012EDA {
    u32 unk0;
    u8* unk4;
};

void FUN_00012EDA(Unk_00012EDA* buffer, u8 c, s32 count)
{
    if (count > 0) {
        u32 n = buffer->unk0;
        if (n > (u32)count)
            n = count;
        for (u32 i = 0; i < n; i++)
            buffer->unk4[i] = c;
        buffer->unk0 -= n;
        buffer->unk4 += count;
    }
}
