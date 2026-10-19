#include "types.h"

struct Unk_10202240 {
    u32 unk0;
    u32 unk4;
};

extern "C" bool FUN_00013A4C(u32 *out);

extern volatile Unk_10202240 DAT_10202240;
extern volatile Unk_10202240 DAT_10202A40;
extern u32 DAT_1FFE80F4;

void FUN_0001846C()
{
    if (DAT_1FFE80F4 == 0) {
        u32 value;
        if (!FUN_00013A4C(&value)) {
            value = 1;
        }
        if (value == 1) {
            DAT_10202240.unk4 = (DAT_10202240.unk4 & 0xFFFF0C00) + 0xFF;
            DAT_10202A40.unk4 = (DAT_10202A40.unk4 & 0xFFFF0C00) + 0xFF;
        } else {
            DAT_10202240.unk4 = (DAT_10202240.unk4 & 0xFFFF0C00) + 0x60FF;
            DAT_10202A40.unk4 = (DAT_10202A40.unk4 & 0xFFFF0C00) + 0x60FF;
        }
        DAT_1FFE80F4 = 1;
    }
}
