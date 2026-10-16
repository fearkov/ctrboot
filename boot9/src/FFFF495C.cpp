#include "types.h"

struct Unk_10006000 {
    u8 unk000[0x30];
    volatile u16 unk030;
};

volatile u16 *FUN_FFFF495C(u32 unit)
{
    return &(unit == 1 ? (Unk_10006000 *)0x10006000 : (Unk_10006000 *)0x10007000)->unk030;
}
