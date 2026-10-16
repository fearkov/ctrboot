#include "types.h"

extern "C" void FUN_FFFFAE9C();
extern "C" void FUN_FFFF9F08();

// The callback that FUN_FFFF9FB0 hands to FUN_FFFF9FC4: waits until the engine has finished, writes the saved control
// word back with bit 0 set (FUN_FFFF9F08), and reports success.
u32 FUN_FFFF9F54()
{
    FUN_FFFFAE9C();
    FUN_FFFF9F08();
    return 1;
}
