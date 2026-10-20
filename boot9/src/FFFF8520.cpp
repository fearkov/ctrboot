// The chunk read is an inline helper: passing it the destination as an argument keeps the sum of the two offsets
// ahead of the load of the base address, as in the dump (with the destination computed in the loop body itself,
// armcc loads the base address first and allocates the registers differently).
#include "types.h"

struct Unk_FFF01728
{
    u8 pad00[0x10];
    u32 unk10;
    u32 *unk14;
};

struct Unk_FFF016F0
{
    u8 pad00[0x24];
    u32 unk24;
    s32 unk28;
    u32 unk2C;
    u8 pad30[8];
    Unk_FFF01728 unk38;
    u8 pad50[0xB4];
    u32 unk104;
};

// The state of the block-ordered card read of FUN_FFFF9B70: the block's offset and the offset within the block.
struct Unk_FFF0068C
{
    u8 pad00[0xE];
    s16 unk0E;
    s16 unk10;
};

extern Unk_FFF016F0 DAT_FFF016F0;
extern Unk_FFF0068C DAT_FFF0068C;

extern "C" void FUN_FFFF343C(u32 *dst, u32 size, Unk_FFF01728 *cmd);

// Points the command's control word pointer at control, sets bit 28 of that word (and clears the flag) when the
// command's flag is set, then reads size bytes to dst.
static inline void ReadChunk(Unk_FFF01728 *cmd, u32 *control, u32 *dst, u32 size)
{
    cmd->unk14 = control;
    if (cmd->unk10) {
        *cmd->unk14 |= 0x10000000;
        cmd->unk10 = 0;
    }
    FUN_FFFF343C(dst, size, cmd);
}

// Reads the rest of the current 4 KB block of a block-ordered card read in chunks of the transfer's chunk size (+0x2C
// of the transfer state at 0xFFF016F0), each to its destination (+0x24) plus the block's offset plus the offset within
// the block, advancing that offset and counting the remaining size (+0x28) down to a 4 KB boundary.
void FUN_FFFF8520()
{
    Unk_FFF016F0 *g = &DAT_FFF016F0;
    Unk_FFF0068C *h = &DAT_FFF0068C;
    Unk_FFF01728 *cmd = &g->unk38;
    do {
        u32 size = g->unk2C;
        s32 off = h->unk0E + h->unk10;
        ReadChunk(cmd, &g->unk104, (u32 *)(g->unk24 + off), size);
        g->unk28 -= size;
        h->unk10 += size;
    } while (g->unk28 & 0xFFF);
}
