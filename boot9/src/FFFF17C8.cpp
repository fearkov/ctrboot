#include "types.h"

// An alarm, kept in a list sorted by the time it fires.
struct Unk_FFFF17C8 {
    void (*unk0)(void *);
    void *unk4;
    u32 unk8;
    u8 padC[4];
    u64 unk10; // when it fires
    Unk_FFFF17C8 *unk18; // previous in the list
    Unk_FFFF17C8 *unk1C; // next in the list
    u64 unk20; // period, 0 for a one-shot alarm
    u64 unk28; // start of a periodic alarm
};

struct Unk_FFF00140 {
    Unk_FFFF17C8 *unk0; // first
    Unk_FFFF17C8 *unk4; // last
};

extern Unk_FFF00140 DAT_FFF00140;

extern "C" void *FUN_FFFF25F0(void *dst, const void *src, u32 size);
extern "C" u64 FUN_FFFF1F70();
extern "C" void FUN_FFFF1964(Unk_FFFF17C8 *alarm);

void FUN_FFFF17C8(Unk_FFFF17C8 *alarm, u64 fire)
{
    if (alarm->unk20 != 0) {
        u64 now = FUN_FFFF1F70();
        FUN_FFFF25F0(&fire, &alarm->unk28, 8);
        if (alarm->unk28 < now) {
            fire += ((now - alarm->unk28) / alarm->unk20 + 1) * alarm->unk20;
        }
    }
    FUN_FFFF25F0(&alarm->unk10, &fire, 8);

    Unk_FFFF17C8 *prev;
    for (Unk_FFFF17C8 *next = DAT_FFF00140.unk0; next != 0; next = next->unk1C) {
        if ((s64)(fire - next->unk10) < 0) {
            alarm->unk18 = next->unk18;
            next->unk18 = alarm;
            alarm->unk1C = next;
            prev = alarm->unk18;
            if (prev != 0) {
                prev->unk1C = alarm;
            } else {
                DAT_FFF00140.unk0 = alarm;
                FUN_FFFF1964(alarm);
            }
            return;
        }
    }
    alarm->unk1C = 0;
    prev = DAT_FFF00140.unk4;
    DAT_FFF00140.unk4 = alarm;
    alarm->unk18 = prev;
    if (prev != 0) {
        prev->unk1C = alarm;
    } else {
        DAT_FFF00140.unk0 = alarm;
        FUN_FFFF1964(alarm);
    }
}
