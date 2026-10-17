#include "types.h"

extern "C" u32 FUN_FFFF5AC0(u32 unit, u32 force, u32 flag);
extern "C" u32 FUN_FFFF5B34(u32 unit, u32 force, u32 flag);

// Signals the unit's events for a change of its status from was to now: FUN_FFFF5AC0 signals the first event and
// FUN_FFFF5B34 the second (resetting the unit's state), each when forced or when its status flag (a, b) is set.
void FUN_FFFF5AD2(u32 unit, u32 was, u32 now, u32 a, u32 b)
{
    if (was) {
        if (now) {
            if (FUN_FFFF5B34(unit, 0, b)) {
                FUN_FFFF5AC0(unit, 1, a);
            }
        } else {
            FUN_FFFF5B34(unit, 1, b);
            if (FUN_FFFF5AC0(unit, 0, a)) {
                FUN_FFFF5B34(unit, 1, b);
            }
        }
    } else {
        if (now) {
            FUN_FFFF5AC0(unit, 1, a);
            if (FUN_FFFF5B34(unit, 0, b)) {
                FUN_FFFF5AC0(unit, 1, a);
            }
        } else {
            if (FUN_FFFF5AC0(unit, 0, a)) {
                FUN_FFFF5B34(unit, 1, b);
            }
        }
    }
}
