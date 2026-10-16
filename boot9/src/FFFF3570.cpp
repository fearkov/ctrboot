#include "types.h"

extern volatile u8 DAT_10164008[8];

extern "C" void FUN_FFFF3540();

void FUN_FFFF3570(const u8 *cmd)
{
    FUN_FFFF3540();
    DAT_10164008[0] = cmd[7];
    DAT_10164008[1] = cmd[6];
    DAT_10164008[2] = cmd[5];
    DAT_10164008[3] = cmd[4];
    DAT_10164008[4] = cmd[3];
    DAT_10164008[5] = cmd[2];
    DAT_10164008[6] = cmd[1];
    DAT_10164008[7] = cmd[0];
}
