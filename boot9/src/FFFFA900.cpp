#include "types.h"

extern "C" void FUN_FFFFA850();
extern "C" u32 FUN_FFFFA884(u32 index);
extern "C" u32 FUN_FFFFA874();

struct Unk_FFF0007C {
    void (*unk0)(u32);  // called by the interrupt handler with unk4
    u32 unk4;
    u32 unk8;           // set once the driver is initialised
};
extern Unk_FFF0007C DAT_FFF0007C;
extern volatile u32 DAT_1000B000;

// Starts the operation of key slot `slot` (initialising the driver first if needed); with a callback,
// the interrupt is enabled and the callback runs with arg when the engine finishes.
u32 FUN_FFFFA900(u32 slot, void (*callback)(u32), u32 arg)
{
    if (DAT_FFF0007C.unk8 == 0) {
        FUN_FFFFA850();
    }
    if (slot >= 4 || FUN_FFFFA884(slot) == 0 || FUN_FFFFA874() != 0) {
        return 0;
    }
    DAT_FFF0007C.unk0 = callback;
    DAT_FFF0007C.unk4 = arg;
    // reading the callback back from the global (rather than using the argument) gives the dump's
    // register assignment
    DAT_1000B000 = (slot << 4) | (DAT_FFF0007C.unk0 != 0 ? 2 : 0) | 1;
    return 1;
}
