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

extern "C" void FUN_FFFF2214();
extern "C" u32 FUN_FFFF1F38();
extern "C" void FUN_FFFF2128(u32 state);
extern "C" void *FUN_FFFF25F0(void *dst, const void *src, u32 size);
extern "C" u64 FUN_FFFF1F70();
extern "C" void FUN_FFFF17C8(Unk_FFFF17C8 *alarm, u64 fire);

// Sets a one-shot alarm to call callback(arg) after delay ticks.
void FUN_FFFF2130(Unk_FFFF17C8 *alarm, u64 delay, void (*callback)(void *), void *arg)
{
    if (alarm == 0 || alarm->unk0 != 0) {
        FUN_FFFF2214();
    }
    u32 state = FUN_FFFF1F38();
    FUN_FFFF25F0(&alarm->unk20, "\0\0\0\0\0\0\0", 8);
    alarm->unk0 = callback;
    alarm->unk4 = arg;
    FUN_FFFF17C8(alarm, FUN_FFFF1F70() + delay);
    FUN_FFFF2128(state);
}
