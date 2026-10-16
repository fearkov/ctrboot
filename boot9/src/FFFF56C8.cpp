#include "types.h"

struct Unk_FFFF1F08;

struct Unk_FFF0009C {
    u8 pad00[2];
    u8 unk2;
    u8 unk3;
};

typedef void (*Handler)();

extern "C" u16 FUN_FFFF211C();
extern "C" u16 FUN_FFFF20F0();
extern "C" void FUN_FFFF1F08(Unk_FFFF1F08 *state);
extern "C" void FUN_FFFF5BBC();
extern "C" u32 FUN_FFFF06EC();
extern "C" u32 FUN_FFFF0700(u32 state);
extern "C" u32 FUN_FFFF1ED4(u32 bit);
extern "C" void FUN_FFFF21AC(u32 irq, Handler handler);
extern "C" u32 FUN_FFFF1F40(u32 bit);
extern Unk_FFF0009C DAT_FFF0009C;
extern Unk_FFFF1F08 DAT_FFF00250;

u32 FUN_FFFF56C8()
{
    Unk_FFF0009C *g = &DAT_FFF0009C;
    if (g->unk2 != 0) {
        return 0;
    }
    u16 present = FUN_FFFF211C();
    u32 error = 1 << 27;
    if (present == 0) {
        return error;
    }
    if (FUN_FFFF20F0() == 0) {
        return error;
    }
    g->unk2 = 1;
    FUN_FFFF1F08(&DAT_FFF00250);
    g->unk3 = 0;
    FUN_FFFF5BBC();
    u32 state = FUN_FFFF06EC();
    FUN_FFFF1ED4(0x10);
    FUN_FFFF21AC(0x10, (Handler)0xFFFF2965);
    FUN_FFFF1F40(0x10);
    FUN_FFFF0700(state);
    return 0;
}
