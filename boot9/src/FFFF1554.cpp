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

struct Unk_10003004 {
    u16 unk0;
    u16 unk2;
};

extern Unk_FFF00140 DAT_FFF00140;
extern volatile Unk_10003004 DAT_10003004;

extern "C" void FUN_FFFF1F10(u32 irq);
extern "C" void FUN_FFFF2184(u32 irq);
extern "C" u64 FUN_FFFF1F70();
extern "C" void FUN_FFFF17C8(Unk_FFFF17C8 *alarm, u64 fire);
extern "C" void FUN_FFFF1964(Unk_FFFF17C8 *alarm);

// The interrupt handler of the alarm timer (timer 1, IRQ 9). It stops the timer and, if the first alarm of the list is
// due, takes it off the list, calls its callback and puts a periodic alarm back; then it arms the timer for the alarm
// that is now first. The two calls to FUN_FFFF1964 are written out: the second reads the list head again, which keeps
// the first call on the pointer already in a register.
void FUN_FFFF1554()
{
    FUN_FFFF1F10(9);
    DAT_10003004.unk2 = 0;
    FUN_FFFF2184(9);
    u64 now = FUN_FFFF1F70();
    Unk_FFFF17C8 *alarm = DAT_FFF00140.unk0;
    if (alarm != 0) {
        if (now < alarm->unk10) {
            FUN_FFFF1964(alarm);
            return;
        }
        Unk_FFFF17C8 *next = alarm->unk1C;
        DAT_FFF00140.unk0 = next;
        if (next == 0) {
            DAT_FFF00140.unk4 = 0;
        } else {
            next->unk18 = 0;
        }
        void (*callback)(void *) = alarm->unk0;
        if (alarm->unk20 == 0) {
            alarm->unk0 = 0;
        }
        if (callback != 0) {
            callback(alarm->unk4);
        }
        if (alarm->unk20 != 0) {
            alarm->unk0 = callback;
            FUN_FFFF17C8(alarm, 0);
        }
        if (DAT_FFF00140.unk0 != 0) {
            FUN_FFFF1964(DAT_FFF00140.unk0);
        }
    }
}
