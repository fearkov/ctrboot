#include "types.h"

extern "C" u32 FUN_FFFF2184(u32 bit);

struct Unk_FFF0007C {
    void (*unk0)(u32);  // set by FUN_FFFFA900
    u32 unk4;
    u32 unk8;           // set once the driver is initialised
};
extern Unk_FFF0007C DAT_FFF0007C;

// The handler of interrupt 0x16 (FUN_FFFFA850 installs it): sets the interrupt's bit in the flag word, then calls the
// callback of FUN_FFFFA900, if there is one, with its argument.
void FUN_FFFF9D28()
{
    FUN_FFFF2184(0x16);
    if (DAT_FFF0007C.unk0 != 0) {
        DAT_FFF0007C.unk0(DAT_FFF0007C.unk4);
    }
}
