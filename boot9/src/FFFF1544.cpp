#include "types.h"

typedef void (*Unk_Callback)(void *);

extern "C" void FUN_FFFF1238(Unk_Callback cb, void *req);

void FUN_FFFF1544(void *req)
{
    FUN_FFFF1238(FUN_FFFF1544, req);
}
