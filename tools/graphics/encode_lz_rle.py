#!/usr/bin/env python3
"""Encode data as a DecompressLzRle stream, byte-identical to the ROM's encoder.

The token format is described in docs/formats/graphics.md ("The
DecompressLzRle codec, decoded"); tools/graphics/decode_lz_rle.py is the
inverse. The parse reproduces every LzRle stream in the US item-icon and
portrait banks:

- At each position, take the byte run there (up to 1089 bytes) if it is at
  least 3 bytes long and no shorter than the best back-reference.
- Otherwise take the best back-reference of at least 3 bytes. Copies never
  overlap their source (length <= distance); among equally long matches the
  farthest one within the 1023-byte window wins.
- A copy is deferred as a literal when the byte run starting at the next
  position is longer than the copy.
- Literal bytes accumulate into chunks of at most 63.

The stream ends with a 0 control byte.
"""
from bisect import bisect_left

MAX_DISTANCE = 0x3FF
MAX_COPY = 33
MAX_SHORT_RUN = 66
MAX_RUN = 0x3FF + 0x42
MAX_LITERAL = 63
MIN_TOKEN = 3


def _run_length(data: bytes, i: int) -> int:
    end = min(len(data), i + MAX_RUN)
    j = i + 1
    while j < end and data[j] == data[i]:
        j += 1
    return j - i


def encode_lz_rle(data: bytes) -> bytes:
    n = len(data)
    chains: dict[bytes, list[int]] = {}
    for p in range(n - MIN_TOKEN + 1):
        chains.setdefault(data[p:p + MIN_TOKEN], []).append(p)

    def best_copy(i: int) -> tuple[int, int]:
        best_len, best_dist = 0, 0
        chain = chains.get(data[i:i + MIN_TOKEN])
        if not chain:
            return 0, 0
        # Farthest candidates first; a later one must be strictly longer.
        for k in range(bisect_left(chain, i - MAX_DISTANCE), len(chain)):
            p = chain[k]
            dist = i - p
            if dist < MIN_TOKEN:
                break
            cap = min(MAX_COPY, dist, n - i)
            length = MIN_TOKEN
            while length < cap and data[p + length] == data[i + length]:
                length += 1
            if length > best_len:
                best_len, best_dist = length, dist
                if length == MAX_COPY:
                    break
        return best_len, best_dist

    out = bytearray()
    literal_start = 0
    i = 0

    def flush_literals(end: int) -> None:
        for start in range(literal_start, end, MAX_LITERAL):
            chunk = data[start:min(end, start + MAX_LITERAL)]
            out.append(len(chunk))
            out.extend(chunk)

    while i < n:
        run = _run_length(data, i)
        copy_len, dist = best_copy(i)
        if run >= MIN_TOKEN and run >= copy_len:
            flush_literals(i)
            if run <= MAX_SHORT_RUN:
                out += bytes((0x40 | (run - 3), data[i]))
            else:
                code = run - 0x42
                out += bytes((0x80 | (code >> 3), (code & 7) << 5, data[i]))
            i += run
            literal_start = i
        elif copy_len >= MIN_TOKEN and not (i + 1 < n and _run_length(data, i + 1) > copy_len):
            flush_literals(i)
            out += bytes((0x80 | (dist >> 3), ((dist & 7) << 5) | (copy_len - 2)))
            i += copy_len
            literal_start = i
        else:
            i += 1
    flush_literals(n)
    out.append(0)
    return bytes(out)
