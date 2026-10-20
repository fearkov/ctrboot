// One translation unit with FUN_FFFF895C and FUN_FFFF8974 (not inlined): armcc then knows they only touch r0, so
// FUN_FFFF8C18 keeps both lengths and the input pointer in r1-r3 across the calls.
#pragma no_inline
#include "types.h"

struct Unk_10009000
{
    u32 unk00; // AES_CNT
    u32 unk04;
    u32 unk08; // AES_WRFIFO
    u32 unk0C; // AES_RDFIFO
};

extern volatile Unk_10009000 DAT_10009000;

// AES_CNT bits 0-4: words in the write FIFO; true when it is full (16).
u32 FUN_FFFF895C()
{
    if ((DAT_10009000.unk00 & 0x1f) == 0x10)
    {
        return 1;
    }
    return 0;
}

// AES_CNT bits 5-9: words in the read FIFO; true when it is empty.
u32 FUN_FFFF8974()
{
    if (((DAT_10009000.unk00 & 0x3ff) >> 5) == 0)
    {
        return 1;
    }
    return 0;
}

// Feeds inLen bytes from in to the AES write FIFO and drains outLen bytes from the read FIFO into out, a block of four
// words at a time, whenever the FIFOs have room or data. Does nothing unless both buffers are word aligned and both
// lengths are multiples of 16.
void FUN_FFFF8C18(u32 *out, u32 outLen, const u32 *in, u32 inLen)
{
    if (((u32)out & 3) || ((u32)in & 3) || (outLen & 0xF) || (inLen & 0xF))
    {
        return;
    }
    while (inLen != 0 || outLen != 0)
    {
        while (inLen != 0 && !FUN_FFFF895C())
        {
            DAT_10009000.unk08 = *in++;
            inLen -= 4;
            DAT_10009000.unk08 = *in++;
            inLen -= 4;
            DAT_10009000.unk08 = *in++;
            inLen -= 4;
            DAT_10009000.unk08 = *in++;
            inLen -= 4;
        }
        if (outLen != 0 && !FUN_FFFF8974())
        {
            *out++ = DAT_10009000.unk0C;
            *out++ = DAT_10009000.unk0C;
            *out++ = DAT_10009000.unk0C;
            *out++ = DAT_10009000.unk0C;
            outLen -= 16;
        }
    }
}
