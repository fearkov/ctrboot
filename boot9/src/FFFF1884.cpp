#include "types.h"

struct Unk_FFF01838 {
    void (*unk00)(u32);
    u32 unk04;
    u32 unk08;
};

extern Unk_FFF01838 DAT_FFF01838[];
extern const u16 DAT_FFF00164[];
extern "C" void FUN_FFFF2184(u32 irq);
extern "C" void FUN_FFFF1F10(u32 irq);

// Runs the handler of this interrupt (once: its slot is cleared first) and acknowledges the interrupt. Every access goes
// through DAT_FFF01838[index] again: with a pointer to the entry armcc allocates the registers differently.
void FUN_FFFF1884(u32 index)
{
    u32 irq = DAT_FFF00164[index];
    void (*handler)(u32) = DAT_FFF01838[index].unk00;
    u32 enabled = DAT_FFF01838[index].unk04;
    DAT_FFF01838[index].unk00 = 0;
    if (handler != 0) {
        handler(DAT_FFF01838[index].unk08);
    }
    FUN_FFFF2184(irq);
    if (enabled == 0) {
        FUN_FFFF1F10(irq);
    }
}
