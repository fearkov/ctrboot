#include "types.h"

// Handler entries of 12 bytes, one per interrupt; the NDMA channels 0-7 use the entries of their own IRQs 0-7.
struct Unk_FFF01838 {
    void (*unk00)(u32);
    u32 unk04;
    u32 unk08;
};

extern Unk_FFF01838 DAT_FFF01838[];
extern "C" u32 FUN_FFFF1F40(u32 irq);

// Sets the handler of an interrupt and enables it, keeping whether it was enabled before. The IRQ number is a local
// of its own: armcc then multiplies in r0 and keeps the IRQ in r3 for the call, as the ROM does.
void FUN_FFFF1694(u32 index, void (*handler)(u32), u32 arg)
{
    u32 irq = index;
    DAT_FFF01838[index].unk00 = handler;
    DAT_FFF01838[index].unk08 = arg;
    DAT_FFF01838[index].unk04 = FUN_FFFF1F40(irq);
}
