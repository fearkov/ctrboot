#include "types.h"

// The byte FUN_00013A7C reads back, as the dump tests it: bit 1 inverted, as a bitfield.
struct Unk_00013944 {
    u8 unk0 : 1;
    u8 unk1 : 1;
    u8 unk2 : 6;
};

extern "C" u32 FUN_00013A7C(Unk_00013944* value);
extern volatile u8 DAT_10147000;

u32 FUN_00013944()
{
    Unk_00013944 value;
    if (FUN_00013A7C(&value))
        return (value.unk1 ^ 1) << 1;
    return (DAT_10147000 >> 2) & 1;
}
