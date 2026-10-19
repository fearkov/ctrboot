// Last step of the boot: swaps the sync values 1 and 0xE with the other processor, clears the boot code's RAM, calls
// the hook at 0x1FFE802C if one is set and then jumps to the entry point that value holds.
#include "types.h"

typedef void (*Hook)(u32);

extern Hook DAT_1FFE8028[];

extern "C" u32 FUN_00012564();
extern "C" void FUN_00012EB4(u32 value);
extern "C" void FUN_00012ECC(u32 value);
extern "C" void FUN_000121FC();
extern "C" void FUN_0001207C();
extern "C" void FUN_00011510();
extern "C" void FUN_000120E0();
extern "C" void FUN_00011534(u32 value);

void FUN_00011FFC(u32 value)
{
    Hook hook = DAT_1FFE8028[1];
    FUN_00012564();
    FUN_00012EB4(1);
    FUN_00012ECC(1);
    FUN_00012564();
    FUN_00012EB4(0xE);
    FUN_00012ECC(0xE);
    FUN_000121FC();
    FUN_0001207C();
    if (hook != 0)
        hook(value);
    FUN_00011510();
    FUN_000120E0();
    FUN_00011534(value);
}
