#include "types.h"

extern "C" void FUN_00012738(void);
extern "C" u64 FUN_000125E4(void);
extern "C" u16 FUN_00013B34(void);

struct Unk_1FFE8120 {
    u64 unk0;
    u16 unk8;
    u16 unkA;
};

extern u32 DAT_1FFE8044;
extern Unk_1FFE8120 DAT_1FFE8120;

void FUN_00013B04(void)
{
    Unk_1FFE8120* p = &DAT_1FFE8120;
    if (DAT_1FFE8044 == 0) {
        DAT_1FFE8044 = 1;
        FUN_00012738();
        p->unk0 = FUN_000125E4();
        p->unk8 = FUN_00013B34();
        p->unkA = p->unk8;
    }
}
