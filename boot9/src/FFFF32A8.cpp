#include "types.h"

// The command block at 0xFFF01728; unk14 points at where the reply goes.
struct Unk_FFF01728 {
    u8 unk00[8];
    u32 unk08;
    u32 unk0C;
    u8 pad10[4];
    u32 *unk14;
};

typedef void (*Handler)(u32 address, u32 *dst, u32 size, void *command);

struct Unk_FFF017E0 {
    u8 pad00[0x50];
    Handler unk50;
};

struct Unk_FFF016F0 {
    u8 pad00[0x20];
    u32 unk20;
    u32 *unk24;
    u32 unk28;
    u32 unk2C;
    u8 pad30[8];
    Unk_FFF01728 unk38;
    u8 pad50[0xA0];
    Unk_FFF017E0 unkF0;
};
extern Unk_FFF016F0 DAT_FFF016F0;

extern "C" void FUN_FFFF4760(u32 a, u32 b, u32 c, Unk_FFF016F0 *g);
extern "C" void FUN_FFFF32DC(u32 address, u32 *dst, u32 size, void *command);

void FUN_FFFF32A8(u32 a, u32 b, u32 c)
{
    Unk_FFF016F0 *g = &DAT_FFF016F0;
    Unk_FFF01728 *cmd = &g->unk38;
    cmd->unk14 = (u32 *)&g->unkF0;
    g->unkF0.unk50 = FUN_FFFF32DC;
    FUN_FFFF4760(a, b, c, g);
    g->unkF0.unk50(g->unk20, g->unk24, g->unk2C, cmd);
}
