#include "types.h"

extern "C" bool FUN_0001391C(u32 reg, u8* buffer, u32 count);

struct Unk_1FFE80E8 {
    u32 unk0;
    u8 unk4;
    u8 pad5[3];
    u32 unk8;
};

extern Unk_1FFE80E8 DAT_1FFE80E8;

bool FUN_00013A4C(u32* out)
{
    u32 value;
    if (DAT_1FFE80E8.unk4) {
        value = DAT_1FFE80E8.unk8;
    } else {
        u8 buf[1];
        if (!FUN_0001391C(0, buf, 1))
            return false;
        value = buf[0] >> 4;
        DAT_1FFE80E8.unk8 = value;
    }
    *out = value;
    return true;
}
