// The request is reached through two pointers: req for filling it in and pending for handing it on at the end. Both
// end up in r7, but the second user variable is what gives armcc the dump's register order (size, index, cb and req in
// r4-r7, src in ip, dst in r0). The requests' address has a local of its own so that the channel table is reached as
// that address minus 0xB0 from one literal.
#include "types.h"

typedef void (*Unk_Callback)(void *);

// One entry of the table at DAT_FFF01990 (0x2C bytes each): how a DMA channel moves data.
struct Unk_Channel {
    u8 pad00[0x1d];
    u8 unk1d;
    u8 pad1e[0xe];
};

// A transfer in progress on a channel, split into parts the channel's program can move.
struct Unk_Request {
    s32 unk00;
    u32 unk04;
    u32 unk08;
    u32 unk0c;
    Unk_Callback unk10;
    void *unk14;
    u32 unk18;
    u8 unk1c;
};

// The channel table and the requests right after it.
struct Unk_FFF01990 {
    Unk_Channel channels[4];
    Unk_Request requests[4];
};

extern Unk_FFF01990 DAT_FFF01990;

extern "C" u32 FUN_FFFF14AC(s32 index, u32 src, u32 dst, u32 size, void *arg, u32 periph);
extern "C" u32 FUN_FFFF1F38(void);
extern "C" u32 FUN_FFFF1ED4(u32 irq);
extern "C" u32 FUN_FFFF1F40(u32 irq);
extern "C" void FUN_FFFF1238(Unk_Callback cb, Unk_Request *req);
extern "C" u8 FUN_FFFF1224(s32 index, u8 value);
extern "C" void FUN_FFFF2128(u32 state);

// Starts a transfer of size bytes on channel index: records it in the channel's request and, if the channel's hook
// lets it go ahead, clears and enables interrupt 0x1C and starts the first part with interrupts held off (done is the
// callback for the end of each part). An empty transfer only calls cb(arg).
void FUN_FFFF12AC(s32 index, u32 src, u32 dst, u32 size, Unk_Callback cb, void *arg, u32 periph, Unk_Callback done)
{
    Unk_Request *requests = DAT_FFF01990.requests;
    Unk_Request *req = &requests[index];
    u32 irq = 0x1C;
    Unk_Channel *channel = &DAT_FFF01990.channels[index];
    req->unk00 = index;
    req->unk04 = src;
    req->unk08 = dst;
    req->unk0c = size;
    req->unk18 = periph;
    req->unk10 = cb;
    req->unk14 = arg;
    req->unk1c = channel->unk1d;
    if (FUN_FFFF14AC(index, src, dst, size, arg, periph) == 0) {
        return;
    }
    if (size == 0) {
        if (cb != 0) {
            cb(arg);
        }
        return;
    }
    u32 state = FUN_FFFF1F38();
    FUN_FFFF1ED4(irq);
    FUN_FFFF1F40(irq);
    Unk_Request *pending = &requests[index];
    FUN_FFFF1238(done, pending);
    if (pending->unk0c != 0) {
        FUN_FFFF1224(index, 0);
    }
    FUN_FFFF2128(state);
}
