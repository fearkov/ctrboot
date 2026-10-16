#include "types.h"

typedef void (*Unk_Callback)(void *);

struct Unk_FFF01990 {
    u8 pad00[2];
    u8 unk02;
    u8 unk03;
    u8 pad04[2];
    u16 unk06;
    u8 pad08[0x24];
};

struct Unk_Request {
    s32 unk00;
    u32 unk04;
    u32 unk08;
    u32 unk0c;
    Unk_Callback unk10;
    void *unk14;
    u32 unk18;
    u8 unk1c;
};

extern Unk_FFF01990 DAT_FFF01990[];
extern "C" u32 FUN_FFFF10F4(s32 index, u32 x, u32 y);
extern "C" void FUN_FFFF1340(s32 index, u32 a, u32 b, u32 n, Unk_Callback cb, void *arg, u32 c);
extern "C" u8 FUN_FFFF1224(s32 index, u8 value);

void FUN_FFFF1238(Unk_Callback cb, Unk_Request *req)
{
    void *arg = req;
    Unk_Request *r = req;
    s32 index = r->unk00;
    Unk_FFF01990 *entry = &DAT_FFF01990[index];
    u32 n = FUN_FFFF10F4(index, entry->unk06, r->unk0c);
    r->unk0c -= n;
    if (r->unk0c == 0) {
        cb = r->unk10;
        arg = r->unk14;
    }
    FUN_FFFF1340(index, r->unk04, r->unk08, n, cb, arg, r->unk18);
    if (entry->unk02 & 1) {
        r->unk04 += n;
    }
    if (entry->unk03 & 0x40) {
        r->unk08 += n;
    }
    if (r->unk0c == 0) {
        FUN_FFFF1224(index, r->unk1c);
    }
}
