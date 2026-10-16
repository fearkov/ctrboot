#include "types.h"

struct Unk_10140FE0 {
    u8 unk0[0x1C];
    u16 unk1C;
};

extern volatile Unk_10140FE0 DAT_10140FE0;

u32 FUN_000121EC()
{
    return DAT_10140FE0.unk1C & 1;
}
