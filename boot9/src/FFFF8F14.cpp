#include "types.h"

typedef void (*Unk_Callback)();

// Thumb entries (bit 0 set) of the callbacks, which boot9.functions does not list.
extern u8 DAT_FFFFA4A9;
extern u8 DAT_FFFFA3A9;
extern u8 DAT_FFFFA1AD;
extern u8 DAT_FFFFA26D;
extern u8 DAT_FFFFA0F1;
extern u8 DAT_FFF00608[0x10];

extern "C" void FUN_FFFF5660(u32 id, u8 *out);
extern "C" void FUN_FFFFA55C(u8 *out, const void *data, u32 size);
extern "C" void FUN_FFFF5CF8(u32 value);
extern "C" void FUN_FFFF8FC0(Unk_Callback a, Unk_Callback b, Unk_Callback c, Unk_Callback d, Unk_Callback e);

void FUN_FFFF8F14()
{
    u8 cid[0x10];
    FUN_FFFF5660(0x201, cid);
    FUN_FFFFA55C(DAT_FFF00608, cid, 0x10);
    FUN_FFFF5CF8((u32)DAT_FFF00608);
    FUN_FFFF8FC0((Unk_Callback)&DAT_FFFFA4A9, (Unk_Callback)&DAT_FFFFA3A9, (Unk_Callback)&DAT_FFFFA1AD,
                 (Unk_Callback)&DAT_FFFFA26D, (Unk_Callback)&DAT_FFFFA0F1);
}
