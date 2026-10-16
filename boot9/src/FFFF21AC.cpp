#include "types.h"

typedef void (*Handler)();

// Handler entries of 12 bytes: one per IRQ 0-7, and IRQs 0x1C and 0x1D use the first one.
struct Unk_FFF01838 {
    Handler unk0;
    u32 unk4;
    u32 unk8;
};

extern Unk_FFF01838 DAT_FFF01838[];
extern Handler DAT_FFF001B4[];

void FUN_FFFF21AC(u32 irq, Handler handler)
{
    Unk_FFF01838 *entry;

    if (irq <= 7) {
        entry = &DAT_FFF01838[irq];
    } else if (irq == 0x1C) {
        // Indexed relative to the IRQ number: armcc folds this to 0 only after the point where it would
        // merge the two equal cases into one block, which the image does not have.
        entry = &DAT_FFF01838[irq - 0x1C];
    } else if (irq == 0x1D) {
        entry = &DAT_FFF01838[irq - 0x1D];
    } else {
        entry = 0;
    }

    if (entry != 0) {
        entry->unk0 = handler;
        entry->unk8 = 0;
        entry->unk4 = 1;
        return;
    }
    DAT_FFF001B4[irq] = handler;
}
