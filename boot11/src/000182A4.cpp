#include "types.h"

struct Unk_1FFFE000 {
    u8 pad0[0xF];
    u8 unkF;
};

extern Unk_1FFFE000 DAT_1FFFE000;

extern "C" void FUN_0001263C(void);
extern "C" void FUN_000182D0(void);
extern "C" u32 FUN_00013944(void);
extern "C" void FUN_00012E14(void);
extern "C" void FUN_00012220(u32 handler);
extern "C" void FUN_000181F4(u32 arg);
extern "C" void FUN_00012454(void);

void FUN_000182A4(void)
{
    Unk_1FFFE000* p = &DAT_1FFFE000;
    FUN_0001263C();
    FUN_000182D0();
    p->unkF = FUN_00013944();
    FUN_00012E14();
    FUN_00012220((u32)FUN_000181F4);
    FUN_00012454();
}
