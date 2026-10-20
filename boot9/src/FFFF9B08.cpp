#include "types.h"

typedef u32 (*Reader)(u32 address, u32 dst, u32 size, u8 *cmd);

// The transfer state that FUN_FFFF4760 sets up; its command buffer (+0x38) is the one at 0xFFF01728.
struct Unk_FFF016F0 {
    u8 pad00[0x20];
    u32 unk20;
    u32 unk24;
    u8 pad28[4];
    u32 unk2C;
    u8 pad30[8];
    u8 unk38[0x14];
    u8 *unk4C;
    u8 pad50[0xF0];
    Reader unk140;
};
extern Unk_FFF016F0 DAT_FFF016F0;
extern u8 DAT_FFF00630[];

extern "C" void FUN_FFFF4760(u32 address, u8 *dst, u32 size, Unk_FFF016F0 *state);
extern "C" u32 FUN_FFFF9B60(u32 address, u32 dst, u32 size, u8 *cmd);

// Builds the eight-byte card command 0x9F (top byte), with its response pointer (+0x14) set to +0x18, sets
// FUN_FFFF9B60 as the reader, sets up a 0x2000-byte transfer to 0xFFF00630 with FUN_FFFF4760 and reads its first
// chunk.
void FUN_FFFF9B08()
{
    Unk_FFF016F0 *p = &DAT_FFF016F0;
    u8 *dst = DAT_FFF00630;
    u8 *cmd = p->unk38;
    p->unk4C = (u8 *)p + 0x50;
    *(__packed u64 *)cmd = 0x9F00000000000000ULL;
    p->unk140 = FUN_FFFF9B60;
    FUN_FFFF4760(0, dst, 0x2000, p);
    p->unk140(p->unk20, p->unk24, p->unk2C, cmd);
}
