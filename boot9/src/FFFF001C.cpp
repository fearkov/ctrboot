#pragma arm

extern "C" void FUN_FFFF008C(void);

// The FIQ exception vector: a branch to its handler.
void FUN_FFFF001C(void)
{
    FUN_FFFF008C();
}
