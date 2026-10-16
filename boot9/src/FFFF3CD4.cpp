#include "types.h"

struct Unk_FFFF3CD4 {
    void (*unk0)();
    Unk_FFFF3CD4 *unk4;
};

void FUN_FFFF3CD4(Unk_FFFF3CD4 *list)
{
    while (list) {
        list->unk0();
        list = list->unk4;
    }
}
