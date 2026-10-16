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

extern "C" u32 FUN_FFFF1F38();
extern "C" void FUN_FFFF2128(u32 state);
extern "C" void *FUN_FFFF25F0(void *dst, const void *src, u32 size);
extern "C" void FUN_FFFF1964(Unk_FFFF17C8 *alarm);

// Takes an alarm out of the list.
void FUN_FFFF1E40(Unk_FFFF17C8 *alarm)
{
    u32 state = FUN_FFFF1F38();
    if (alarm->unk0 == 0) {
        FUN_FFFF2128(state);
        return;
    }
    Unk_FFFF17C8 *next = alarm->unk1C;
    Unk_FFFF17C8 *prev = alarm->unk18;
    if (next == 0) {
        DAT_FFF00140.unk4 = prev;
    } else {
        next->unk18 = prev;
    }
    if (alarm->unk18 != 0) {
        alarm->unk18->unk1C = next;
    } else {
        DAT_FFF00140.unk0 = next;
        if (next != 0) {
            FUN_FFFF1964(next);
        }
    }
    alarm->unk0 = 0;
    FUN_FFFF25F0(&alarm->unk20, "\0\0\0\0\0\0\0", 8);
    FUN_FFFF2128(state);
}
