#pragma arm

extern "C" void FUN_FFFF00AC(void);

// The data abort exception vector: a branch to its handler.
void FUN_FFFF0010(void)
{
    FUN_FFFF00AC();
}
