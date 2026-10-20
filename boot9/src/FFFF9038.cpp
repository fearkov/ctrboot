// src is a cursor copied from the parameter otp: walking the parameter itself makes armcc spill it in the first round
// (pushed with r0) where the dump spills the padding length.
#include "types.h"

extern u32 DAT_FFF00618[4];

extern "C" void FUN_FFFF2214();
extern "C" void FUN_FFFFACF8();
extern "C" void FUN_FFFF03F0(const void *src, void *dst, u32 size);
extern "C" void FUN_FFFFA5BC(const void *src, void *dst, u32 size);
extern "C" void FUN_FFFFAC60(const void *data, u32 size);
extern "C" void FUN_FFFFACEC(u8 *hash);
extern "C" void FUN_FFFF89E4();
extern "C" void FUN_FFFF8AA0(u32 slot, u32 mode, const u32 *key);
extern "C" void FUN_FFFF8B18(u32 slot, u32 mode, const u32 *key);
extern "C" void FUN_FFFF8B90(u32 slot, u32 mode, const u32 *key);
extern "C" void FUN_FFFF898C(u32 slot);
extern "C" void FUN_FFFF8A64(u32 mode, const u32 *data);
extern "C" void FUN_FFFF8A00(u32 mode, u32 a, u32 b, u32 blkcnt, u32 blklen, u32 c, u32 d);
extern "C" void FUN_FFFF8C08(u32 *dst, const u32 *src, u32 size);
extern "C" void FUN_FFFF0374(const void *src, void *dst, u32 size);
extern "C" void FUN_FFFF03A4(u32 value, void *dst, u32 size);

// Sets up the AES key slots from size bytes of console data at otp and the key table at table. Four rounds each
// SHA-256 hash the next 0x1C bytes of otp (while any are left) padded to 0x40 bytes from the table, the first hash
// becoming key X and Y of slot 0x3F, then AES-CBC encrypt 0x40 table bytes with that slot into the buffer, which gives
// the key X of slots 0x04-0x2B. The rest of the table gives the other key X, the key Y of slots 0x04-0x0B, the normal
// keys and the 16 bytes copied to 0xFFF00618; the buffer is then filled with the next table word. Some groups set one
// slot four times (0x10, 0x24, 0x38).
void FUN_FFFF9038(const u32 *otp, u32 size, const u32 *table)
{
    u32 buf[16];
    const u32 *src = otp;
    u32 n;

    if (otp == 0)
        FUN_FFFF2214();
    if (size & 3)
        FUN_FFFF2214();
    if (size == 0)
        FUN_FFFF2214();
    FUN_FFFFACF8();

    n = size < 0x1C ? size : 0x1C;
    FUN_FFFF03F0(src, buf, n);
    if (n < 0x40) {
        FUN_FFFFA5BC(table, (u8 *)buf + n, 0x40 - n);
        table += (0x40 - n) / 4;
    }
    src += n / 4;
    size -= n;
    FUN_FFFFAC60(buf, 0x40);
    FUN_FFFFACEC((u8 *)buf);
    FUN_FFFF89E4();
    FUN_FFFF8B18(0x3F, 5, buf);
    FUN_FFFF8B90(0x3F, 5, buf + 4);
    FUN_FFFF898C(0x3F);
    FUN_FFFF8A64(5, table);
    table += 4;
    FUN_FFFF8A00(5, 5, 5, 0, 4, 0, 0);
    FUN_FFFF8C08(buf, table, 0x40);
    table += 16;
    for (int i = 0; i < 4; i++)
        FUN_FFFF8B18(i + 0x04, 5, buf);
    for (int i = 0; i < 4; i++)
        FUN_FFFF8B18(i + 0x08, 5, buf + 4);
    for (int i = 0; i < 4; i++)
        FUN_FFFF8B18(i + 0x0C, 5, buf + 8);
    for (int i = 0; i < 4; i++)
        FUN_FFFF8B18(0x10, 5, buf + 12);
    FUN_FFFF89E4();

    if (size != 0) {
        n = size < 0x1C ? size : 0x1C;
        FUN_FFFF03F0(src, buf, n);
        if (n < 0x40) {
            FUN_FFFFA5BC(table, (u8 *)buf + n, 0x40 - n);
            table += (0x40 - n) / 4;
        }
        src += n / 4;
        size -= n;
        FUN_FFFFAC60(buf, 0x40);
        FUN_FFFFACEC((u8 *)buf);
    }
    FUN_FFFF8A64(5, table);
    table += 4;
    FUN_FFFF8A00(5, 5, 5, 0, 4, 0, 0);
    FUN_FFFF8C08(buf, table, 0x40);
    table += 4;
    FUN_FFFF8B18(0x14, 5, buf);
    FUN_FFFF8B18(0x15, 5, buf + 4);
    FUN_FFFF8B18(0x16, 5, buf + 8);
    FUN_FFFF8B18(0x17, 5, buf + 12);
    FUN_FFFF89E4();

    if (size != 0) {
        n = size < 0x1C ? size : 0x1C;
        FUN_FFFF03F0(src, buf, n);
        if (n < 0x40) {
            FUN_FFFFA5BC(table, (u8 *)buf + n, 0x40 - n);
            table += (0x40 - n) / 4;
        }
        src += n / 4;
        size -= n;
        FUN_FFFFAC60(buf, 0x40);
        FUN_FFFFACEC((u8 *)buf);
    }
    FUN_FFFF8A64(5, table);
    table += 4;
    FUN_FFFF8A00(5, 5, 5, 0, 4, 0, 0);
    FUN_FFFF8C08(buf, table, 0x40);
    table += 16;
    for (int i = 0; i < 4; i++)
        FUN_FFFF8B18(i + 0x18, 5, buf);
    for (int i = 0; i < 4; i++)
        FUN_FFFF8B18(i + 0x1C, 5, buf + 4);
    for (int i = 0; i < 4; i++)
        FUN_FFFF8B18(i + 0x20, 5, buf + 8);
    for (int i = 0; i < 4; i++)
        FUN_FFFF8B18(0x24, 5, buf + 12);
    FUN_FFFF89E4();

    if (size != 0) {
        n = size < 0x1C ? size : 0x1C;
        FUN_FFFF03F0(src, buf, n);
        if (n < 0x40) {
            FUN_FFFFA5BC(table, (u8 *)buf + n, 0x40 - n);
            table += (0x40 - n) / 4;
        }
        src += n / 4;
        size -= n;
        FUN_FFFFAC60(buf, 0x40);
        FUN_FFFFACEC((u8 *)buf);
    }
    FUN_FFFF8A64(5, table);
    table += 4;
    FUN_FFFF8A00(5, 5, 5, 0, 4, 0, 0);
    FUN_FFFF8C08(buf, table, 0x40);
    table += 4;
    FUN_FFFF8B18(0x28, 5, buf);
    FUN_FFFF8B18(0x29, 5, buf + 4);
    FUN_FFFF8B18(0x2A, 5, buf + 8);
    FUN_FFFF8B18(0x2B, 5, buf + 12);

    for (int i = 0; i < 4; i++)
        FUN_FFFF8B18(i + 0x2C, 5, table);
    table += 4;
    for (int i = 0; i < 4; i++)
        FUN_FFFF8B18(i + 0x30, 5, table);
    table += 4;
    for (int i = 0; i < 4; i++)
        FUN_FFFF8B18(i + 0x34, 5, table);
    table += 4;
    for (int i = 0; i < 4; i++)
        FUN_FFFF8B18(i + 0x38, 5, table);
    table += 4;
    FUN_FFFF8B18(0x3C, 5, table);
    table += 4;
    FUN_FFFF8B18(0x3D, 5, table);
    table += 4;
    FUN_FFFF8B18(0x3E, 5, table);
    table += 4;
    FUN_FFFF8B18(0x3F, 5, table);
    table += 4;

    FUN_FFFF8B90(0x04, 5, table);
    table += 4;
    FUN_FFFF8B90(0x05, 5, table);
    table += 4;
    FUN_FFFF8B90(0x06, 5, table);
    table += 4;
    FUN_FFFF8B90(0x07, 5, table);
    table += 4;
    FUN_FFFF8B90(0x08, 5, table);
    table += 4;
    FUN_FFFF8B90(0x09, 5, table);
    table += 4;
    FUN_FFFF8B90(0x0A, 5, table);
    table += 4;
    FUN_FFFF8B90(0x0B, 5, table);
    table += 4;

    for (int i = 0; i < 4; i++)
        FUN_FFFF8AA0(i + 0x0C, 5, table);
    table += 4;
    for (int i = 0; i < 4; i++)
        FUN_FFFF8AA0(0x10, 5, table);
    table += 4;
    FUN_FFFF8AA0(0x14, 5, table);
    table += 4;
    FUN_FFFF8AA0(0x15, 5, table);
    table += 4;
    FUN_FFFF8AA0(0x16, 5, table);
    table += 4;
    FUN_FFFF8AA0(0x17, 5, table);
    table += 4;
    for (int i = 0; i < 4; i++)
        FUN_FFFF8AA0(i + 0x18, 5, table);
    table += 4;
    for (int i = 0; i < 4; i++)
        FUN_FFFF8AA0(i + 0x1C, 5, table);
    table += 4;
    for (int i = 0; i < 4; i++)
        FUN_FFFF8AA0(i + 0x20, 5, table);
    table += 4;
    for (int i = 0; i < 4; i++)
        FUN_FFFF8AA0(0x24, 5, table);
    FUN_FFFF8AA0(0x28, 5, table);
    table += 4;
    FUN_FFFF8AA0(0x29, 5, table);
    table += 4;
    FUN_FFFF8AA0(0x2A, 5, table);
    table += 4;
    FUN_FFFF8AA0(0x2B, 5, table);
    table += 4;
    for (int i = 0; i < 4; i++)
        FUN_FFFF8AA0(i + 0x2C, 5, table);
    table += 4;
    for (int i = 0; i < 4; i++)
        FUN_FFFF8AA0(i + 0x30, 5, table);
    table += 4;
    for (int i = 0; i < 4; i++)
        FUN_FFFF8AA0(i + 0x34, 5, table);
    table += 4;
    for (int i = 0; i < 4; i++)
        FUN_FFFF8AA0(0x38, 5, table);
    FUN_FFFF8AA0(0x3C, 5, table);
    table += 4;
    FUN_FFFF8AA0(0x3D, 5, table);
    table += 4;
    FUN_FFFF8AA0(0x3E, 5, table);
    table += 4;
    FUN_FFFF8AA0(0x3F, 5, table);

    FUN_FFFF0374(table, DAT_FFF00618, 0x10);
    FUN_FFFF03A4(table[4], buf, 0x40);
}
