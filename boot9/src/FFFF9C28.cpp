#include "types.h"

struct Unk_FFF000E8 {
    u8 pad00[0x20];
    u32 unk20;
};
extern Unk_FFF000E8 DAT_FFF000E8;

struct Unk_FFF00628 {
    s32 unk0;
    u32 unk4;
};
extern Unk_FFF00628 DAT_FFF00628;
extern u8 DAT_FFF01728[];

extern "C" void FUN_FFFF8678(u8 *cmd);
extern "C" void FUN_FFFF8580(u8 *cmd);
extern "C" void FUN_FFFF83E8(u8 *cmd);
extern "C" u32 FUN_FFFF34BC(u8 *cmd);

// Unless 0xFFF00108 is set, sends the eight-byte command 0x10 (top byte) with its response going to +0x7C, and keeps
// the word read back at 0xFFF0062C; returns that word. The command buffer: +0x10 a flag, +0x14 the response pointer.
u32 FUN_FFFF9C28()
{
    Unk_FFF00628 *s = &DAT_FFF00628;
    if (DAT_FFF000E8.unk20 == 0) {
        u8 *cmd = DAT_FFF01728;
        *(u8 **)(cmd + 0x14) = cmd + 0x7C;
        *(__packed u64 *)cmd = 0x1000000000000000ULL;
        FUN_FFFF8678(cmd);
        FUN_FFFF8580(cmd);
        FUN_FFFF83E8(cmd);
        if (s->unk0 >= 0) {
            *(u32 *)(cmd + 0x10) = 1;
        }
        *(u8 **)(cmd + 0x14) = cmd + 0x7C;
        if (*(u32 *)(cmd + 0x10) != 0) {
            **(u32 **)(cmd + 0x14) |= 0x10000000;
            *(u32 *)(cmd + 0x10) = 0;
        }
        s->unk4 = FUN_FFFF34BC(cmd);
    }
    return s->unk4;
}
