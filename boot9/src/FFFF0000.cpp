#pragma arm

extern "C" void FUN_FFFF0030(void);

// The reset exception vector: a branch to its handler.
void FUN_FFFF0000(void)
{
    FUN_FFFF0030();
}
