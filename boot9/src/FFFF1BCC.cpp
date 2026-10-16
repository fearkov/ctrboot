// One translation unit with FUN_FFFF1BCC (not inlined): armcc then knows it only touches r0, so FUN_FFFF1DBC
// keeps the IRQ state in r3 across the busy loop.
#pragma no_inline
#include "types.h"

// CoreLink DMA-330 debug registers.
struct DmaDebugRegs {
    u32 status;      // DBGSTATUS: bit 0 set while a debug instruction runs
    u32 command;     // DBGCMD: writing 0 executes DBGINST0/DBGINST1
    u32 instruction0; // DBGINST0: thread, channel and first two instruction bytes
    u32 instruction1; // DBGINST1: remaining four instruction bytes
};

// Buffer the debug instruction is assembled in.
union DmaDebugInstruction {
    u32 words[2];
    u8 bytes[8];
};

extern volatile DmaDebugRegs DAT_1000CD00;
extern DmaDebugInstruction DAT_FFF00190;

extern "C" u32 FUN_FFFF1F38();
extern "C" void FUN_FFFF2128(u32 state);

u32 FUN_FFFF1BCC()
{
    return DAT_1000CD00.status & 1;
}

// Kills one DMA channel through the debug interface (DMAKILL run by the channel's thread), with IRQs masked.
void FUN_FFFF1DBC(u32 channel)
{
    u8 *bytes = DAT_FFF00190.bytes;
    u32 state = FUN_FFFF1F38();
    while (FUN_FFFF1BCC() != 0) {
    }
    DAT_FFF00190.words[0] = 0;
    DAT_FFF00190.words[1] = 0;
    bytes[0] = 1;       // channel thread
    bytes[1] = channel;
    bytes[2] = 0x01;    // DMAKILL
    DAT_1000CD00.instruction0 = DAT_FFF00190.words[0];
    DAT_1000CD00.instruction1 = DAT_FFF00190.words[1];
    DAT_1000CD00.command = 0;
    FUN_FFFF2128(state);
}
