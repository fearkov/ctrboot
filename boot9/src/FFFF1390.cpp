// One translation unit with FUN_FFFF1A9C (defined after its callers, as in the ROM, and never inlined): armcc then
// knows that it only touches r0 and r1, so FUN_FFFF1390 hands its fourth argument on in r3, and FUN_FFFF14EC keeps
// the entry pointer in r2 and its fourth argument in r3, across the calls.
#include "types.h"

// One entry of the table at DAT_FFF01990 (0x2C bytes each): how a DMA channel moves data.
struct Unk_FFF01990 {
    u8 pad00[2];
    u8 unk02;
    u8 unk03;
    u8 pad04[0x1c];
    u8 unk20;
    u8 pad21[0xb];
};

struct Unk_1000C100 {
    u32 unk00;
    u32 unk04;
};

typedef void (*Unk_Callback)(void *);

extern Unk_FFF01990 DAT_FFF01990[];

__attribute__((noinline)) u32 FUN_FFFF1A9C(u32 index);
extern "C" u32 FUN_FFFF0CF4(u32 event, u32 src, u32 dst, u32 size, s32 periph, Unk_FFF01990 *config, u8 *buf);
extern "C" void FUN_FFFF1424(s32 index, u8 *program, u32 length);
extern "C" void FUN_FFFF12AC(u32 index, u32 a, u32 b, u32 n, Unk_Callback cb, void *arg, u32 c, Unk_Callback done);

// Waits until channel index is stopped, writes its program into the channel's 256 bytes at 0x080FD000 and starts it.
void FUN_FFFF1390(s32 index, u32 src, u32 dst, u32 size, s32 periph)
{
    Unk_FFF01990 *config = &DAT_FFF01990[index];
    u8 *program = (u8 *)0x080FD000 + (index << 8);
    while (FUN_FFFF1A9C(index) != 0) {
    }
    u32 length = FUN_FFFF0CF4(index, src, dst, size, periph, config, program);
    FUN_FFFF1424(index, program, length);
}

void FUN_FFFF14EC(u32 index, u32 a, u32 b, u32 n, Unk_Callback cb, void *arg, u32 c)
{
    Unk_FFF01990 *entry = &DAT_FFF01990[index];
    while (FUN_FFFF1A9C(index) != 0) {
    }
    entry->unk02 &= ~1;
    entry->unk03 |= 0x40;
    entry->unk20 = 0;
    // 0xFFFF1545 is the Thumb function at 0xFFFF1544, which is not in the list yet (no FUN_FFFF1544 to name).
    FUN_FFFF12AC(index, a, b, n, cb, arg, c, (Unk_Callback)0xFFFF1545);
}

// Low four bits of the first word of the 8-byte register pair of this index. The base is an absolute address: with an
// extern array armcc would index it with a register offset instead of adding first.
u32 FUN_FFFF1A9C(u32 index)
{
    return ((volatile Unk_1000C100 *)0x1000C100)[index].unk00 & 0xF;
}
