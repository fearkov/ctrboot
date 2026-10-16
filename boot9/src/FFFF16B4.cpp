#include "types.h"

// Handler entries of 12 bytes; the four events of the DMA engine at 0x1000C000 use entries 14-17, all on IRQ 0x1C.
struct Unk_FFF01838 {
    void (*unk00)(u32);
    u32 unk04;
    u32 unk08;
};

extern Unk_FFF01838 DAT_FFF01838[];
extern "C" u32 FUN_FFFF1F40(u32 irq);

// Sets the handler of a DMA event and enables its interrupt, keeping whether it was enabled before. The IRQ number is
// a local: armcc then loads it into r0 first, which moves the index to r3 and the 12 of the multiply to r4.
void FUN_FFFF16B4(s32 index, void (*handler)(u32), u32 arg)
{
    u32 irq = 0x1c;
    DAT_FFF01838[index + 14].unk08 = arg;
    DAT_FFF01838[index + 14].unk00 = handler;
    DAT_FFF01838[index + 14].unk04 = FUN_FFFF1F40(irq);
}
