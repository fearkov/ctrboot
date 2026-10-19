// Sets every entry of the interrupt handler table to the empty handler, then installs the handlers of IRQs 48 to 54
// and 56.
#include "types.h"

typedef void (*Handler)();

extern Handler DAT_1FFE8140[];

extern "C" void FUN_00012198();
extern "C" void FUN_0001219A();
extern "C" void FUN_000121A4();
extern "C" void FUN_000121AE();
extern "C" void FUN_000121B8();
extern "C" void FUN_000121C2();
extern "C" void FUN_000121CC();
extern "C" void FUN_000121D6();
extern "C" void FUN_000121E0();

void FUN_000120FC()
{
    for (s32 i = 0; i < 0x7E; i++)
        DAT_1FFE8140[i] = FUN_00012198;
    DAT_1FFE8140[48] = FUN_0001219A;
    DAT_1FFE8140[49] = FUN_000121A4;
    DAT_1FFE8140[50] = FUN_000121AE;
    DAT_1FFE8140[51] = FUN_000121B8;
    DAT_1FFE8140[52] = FUN_000121C2;
    DAT_1FFE8140[53] = FUN_000121CC;
    DAT_1FFE8140[54] = FUN_000121D6;
    DAT_1FFE8140[56] = FUN_000121E0;
}
