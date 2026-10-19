#include "types.h"

typedef void (*Handler)();

// Entry of the table FUN_0001215C works through (the handler is cleared when it runs).
struct Unk_1FFE8338 {
    Handler unk0;
    u32 unk4;
    u32 unk8;
};

extern Unk_1FFE8338 DAT_1FFE8338[];
extern Handler DAT_1FFE8140[];

// Sets the handler of an interrupt: the interrupts 0x30-0x39 get an entry of the table above (0x39 the first one,
// like 0x30), the others go straight into the dispatch table.
void FUN_00012870(u32 irq, Handler handler)
{
    Unk_1FFE8338* entry;
    if (irq >= 0x30 && irq <= 0x38) {
        entry = &DAT_1FFE8338[irq - 0x30];
    } else if (irq == 0x39) {
        entry = &DAT_1FFE8338[irq - 0x39];
    } else {
        entry = 0;
    }
    if (entry != 0) {
        entry->unk0 = handler;
        entry->unk8 = 0;
        entry->unk4 = 1;
    } else {
        DAT_1FFE8140[irq] = handler;
    }
}
