// The dump gets its 16-byte local by pushing r0-r3 along with r4 and lr; with -Otime armcc
// uses push {lr} / sub sp instead. That frame only comes out when building for space.
#include "types.h"

extern "C" u32 FUN_00012564();
extern "C" u32 FUN_000112A0();
extern "C" void FUN_00011320();
extern "C" void FUN_000113C0();
extern "C" void FUN_0001140C();
extern "C" void FUN_0001144C();
extern "C" void FUN_00012528(u32* saved);
extern "C" void FUN_000114B0();
extern "C" void FUN_00011490();
extern "C" void FUN_000114E8();
extern "C" u32 FUN_00011B80();

void FUN_0001207C()
{
    u32 saved[4];
    FUN_00012564();
    FUN_000112A0();
    FUN_00011320();
    FUN_000113C0();
    FUN_0001140C();
    FUN_0001144C();
    FUN_00012528(saved);
    FUN_000114B0();
    FUN_00011490();
    FUN_000114E8();
    FUN_00011B80();
}
