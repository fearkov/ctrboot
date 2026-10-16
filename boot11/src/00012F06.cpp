#include "types.h"

struct Unk_00012F06 {
    u32 unk0;
    u8* unk4;
};

void FUN_00012F06(Unk_00012F06* buffer, u8 c)
{
    if (buffer->unk0 != 0) {
        *buffer->unk4 = c;
        buffer->unk0--;
    }
    buffer->unk4++;
}
