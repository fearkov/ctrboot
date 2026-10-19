#include "types.h"

struct Unk_FFF0064C {
    u8 pad00[0x20];
    u32 unk20;
};
extern Unk_FFF0064C DAT_FFF0064C;
extern u8 DAT_FFF01728[];

extern "C" void FUN_FFFF9C9C(u8 *cmd);

// Sends the eight-byte command 0x40 (top byte) with the value at 0xFFF0066C in bits 20-43, its response going
// to +0x40.
void FUN_FFFF9CCC()
{
    u8 *cmd = DAT_FFF01728;
    *(u8 **)(cmd + 0x14) = cmd + 0x40;
    *(__packed u64 *)cmd = 0x4000000000000000ULL;
    *(u64 *)cmd |= ((u64)DAT_FFF0064C.unk20 << 20) & 0xFFFFFF00000ULL;
    FUN_FFFF9C9C(cmd);
}
