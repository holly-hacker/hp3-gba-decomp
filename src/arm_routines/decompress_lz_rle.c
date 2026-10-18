#include "arm_routines.h"

// Decompresses an LZ/RLE stream and stores its size to *pSize. Control byte:
//   1xxxxxxx  back-reference (10-bit distance, 5-bit length + 2), or with a
//             zero length field a fill of distance + 0x42 bytes
//   01xxxxxx  fill of (control & 0x3F) + 3 bytes
//   00xxxxxx  literal run of control bytes; 0 ends the stream
// Output is written in halfwords only, so an odd byte waits in pending.
void DecompressLzRle(const void *src, void *dst, u32 *pSize)
{
    const u8 *pSrc;
    u8 *pDst;
    u8 *pDstStart;
    const u8 *pFrom;
    u32 control;
    u32 hasPending;
    u32 pending;
    u32 distance;
    u32 length;
    u32 count;
    u32 high;
    u32 value;

    pSrc = src;
    pDst = dst;
    hasPending = 0;
    control = *pSrc++;
    pDstStart = pDst;
    while (control != 0) {
        if (control & 0x80) {
            high = control & 0x7F;
            control = *pSrc++;
            length = (control & 0x1F) + 2;
            distance = (high << 3) | (control >> 5);
            if (length == 2) {
                length = distance + 0x42;
                goto fill;
            }
            pFrom = pDst + hasPending - distance;
            if ((u32)pFrom & 1) {
                value = *pFrom++;
                hasPending ^= 1;
                if (hasPending)
                    pending = value;
                else {
                    pending |= value << 8;
                    *(u16 *)pDst = pending;
                    pDst += 2;
                }
                length--;
            }
            count = length >> 1;
            if (hasPending == 0) {
                for (; count != 0; count--) {
                    *(u16 *)pDst = *(const u16 *)pFrom;
                    pDst += 2;
                    pFrom += 2;
                }
                if (length & 1) {
                    pending = *pFrom;
                    hasPending = 1;
                }
            }
            else {
                for (; count != 0; count--) {
                    value = *(const u16 *)pFrom;
                    pFrom += 2;
                    pending |= value << 8;
                    *(u16 *)pDst = pending;
                    pDst += 2;
                    pending = value >> 8;
                }
                if (length & 1) {
                    pending |= *pFrom << 8;
                    *(u16 *)pDst = pending;
                    pDst += 2;
                    hasPending = 0;
                }
            }
        }
        else if (control & 0x40) {
            length = (control & 0x3F) + 3;
        fill:
            control = *pSrc++;
            if (hasPending) {
                pending |= control << 8;
                length--;
                *(u16 *)pDst = pending;
                pDst += 2;
            }
            pending = control | (control << 8);
            for (count = length >> 1; count != 0; count--) {
                *(u16 *)pDst = pending;
                pDst += 2;
            }
            hasPending = length & 1;
            if (hasPending)
                pending &= 0xFF;
        }
        else {
            length = control;
            if ((u32)pSrc & 1) {
                hasPending ^= 1;
                if (hasPending)
                    pending = *pSrc++;
                else {
                    pending |= *pSrc++ << 8;
                    *(u16 *)pDst = pending;
                    pDst += 2;
                }
                length--;
            }
            count = length >> 1;
            if (hasPending == 0) {
                for (; count != 0; count--) {
                    *(u16 *)pDst = *(const u16 *)pSrc;
                    pDst += 2;
                    pSrc += 2;
                }
                if (length & 1) {
                    pending = *pSrc++;
                    hasPending = 1;
                }
            }
            else {
                for (; count != 0; count--) {
                    value = *(const u16 *)pSrc;
                    pSrc += 2;
                    pending |= value << 8;
                    *(u16 *)pDst = pending;
                    pDst += 2;
                    pending = value >> 8;
                }
                if (length & 1) {
                    hasPending = 0;
                    pending |= *pSrc++ << 8;
                    *(u16 *)pDst = pending;
                    pDst += 2;
                }
            }
        }
        control = *pSrc++;
    }
    if (hasPending)
        *pDst++ = pending;
    *pSize = pDst - pDstStart;
}
