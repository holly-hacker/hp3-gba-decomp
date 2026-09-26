"""Choose GammaLz tokens with the compression passes of Pucrunch 1.11.

This module is a modified Python translation of parts of pucrunch.c from
Pucrunch 1.11 (30-Jan-2000):

    Pucrunch (c)1997-2005 by Pasi 'Albert' Ojala, a1bert@iki.fi
    Pucrunch is under GNU LGPL.

This library is free software; you can redistribute it and/or modify it
under the terms of the GNU Lesser General Public License, version 2.1, as
published by the Free Software Foundation. It is distributed in the hope
that it will be useful, but WITHOUT ANY WARRANTY; without even the implied
warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
license text in LICENSES/LGPL-2.1.txt.

Changes from pucrunch.c (2026): translated to Python; reduced to the passes
that choose tokens (PackLz77's match search, InitRle, OptimizeLength,
escape-width and LZPOS-width selection, OptimizeEscape, OptimizeRle, and the
LZ77 rescan) for the default options with maxGamma 7 and no delta LZ; the
rescan, done while writing output in pucrunch.c, runs as a separate pass
before output; the match search is vectorized with numpy; the C64 file
handling, statistics, and output code are omitted. The GammaLz container
that the game reads is written by encode_gamma_lz.py, which is not part of
this translation. See docs/formats/graphics.md.
"""
from dataclasses import dataclass

import numpy as np

MAX_GAMMA = 7
MAX_LZ_LEN = 2 << MAX_GAMMA                  # 256
LZ_RANGE = ((2 << MAX_GAMMA) - 3) * 256      # LRANGE
MAX_RLE_LEN = ((2 << MAX_GAMMA) - 2) * 256   # MAXRLELEN
RANKS = 32                                   # ranks 1..31

LITERAL, RLE, LZ77 = 0, 1, 2
NO_LZ2 = 100000


def _len_value(v: int) -> int:
    count = v.bit_length() - 1
    return 2 * count + 1 if count < MAX_GAMMA else 2 * count


LEN_VALUE = [0] + [_len_value(v) for v in range(1, 256)]
_LEN_VALUE_NP = np.array(LEN_VALUE, dtype=np.int32)


@dataclass
class Parse:
    """Tokens and header choices for one input.

    tokens holds (mode, position, length, distance); distance is 0 except
    for LZ77. new_escapes maps a literal's position to the escape prefix
    that replaces the current one if the literal matches it.
    rle_values[1..31] is the final RLE byte ranking.
    """
    tokens: list[tuple[int, int, int, int]]
    escape_bits: int
    extra_lz_pos_bits: int
    start_escape: int
    new_escapes: dict[int, int]
    rle_values: list[int]
    rle_used: int


class _Packer:
    def __init__(self, data: bytes):
        self.data = data
        self.n = len(data)
        self.esc_bits = 2
        self.extra = 0
        self.lzopt = 0
        self._find_matches()
        self._init_rle()

    # PackLz77: run lengths, pair history, and LZ77 candidates.
    def _find_matches(self) -> None:
        d, n = self.data, self.n
        rle = [0] * n
        elr = [0] * n
        self.rle_hist = [0] * 256
        runs_by_value: dict[int, list[tuple[int, int]]] = {}
        p = 0
        while p < n:
            q = p + 1
            while q < n and d[q] == d[p]:
                q += 1
            if q - p >= 2:
                self.rle_hist[d[p]] += 1
                runs_by_value.setdefault(d[p], []).append((p, q - p))
                for k in range(q - p):
                    rle[p + k] = q - p - k
                    elr[p + k] = k
            p = q
        run_index = {start: k for runs in runs_by_value.values()
                     for k, (start, _) in enumerate(runs)}

        back_skip = [0] * n
        last_pair: dict[int, int] = {}
        for p in range(n - 1):
            key = d[p] << 8 | d[p + 1]
            if key in last_pair and p - last_pair[key] <= 0xFFFF:
                back_skip[p] = p - last_pair[key]
            last_pair[key] = p

        lzlen = [0] * n
        lzpos = [0] * n
        a = np.frombuffer(d, dtype=np.uint8)
        # cur[c] = common prefix length of d[c:] and d[p:], capped at 256.
        prev = np.zeros(n + 1, dtype=np.uint16)
        cur = np.zeros(n + 1, dtype=np.uint16)
        for p in range(n - 1, -1, -1):
            row = cur[:p]
            if p:
                np.add(prev[1:p + 1], 1, out=row)
                row *= a[:p] == a[p]
                np.minimum(row, MAX_LZ_LEN, out=row)
            prev, cur = cur, prev
            row = prev[:p]
            if not p + rle[p] + 1 < n:
                continue
            rlep = rle[p] or 1
            lo = max(0, p - LZ_RANGE)
            hits = np.flatnonzero(row[lo:] >= 2)
            # The nearest pair must start at or after lo + rlep - 1.
            if not len(hits) or int(hits[-1]) + lo < lo + rlep - 1:
                continue
            maxval, maxpos = 2, p - (int(hits[-1]) + lo)
            cand = np.flatnonzero(row[lo:] >= rlep + 1)[::-1] + lo
            if len(cand):
                lens = row[cand].astype(np.int32)
                dists = p - cand
                gains = 8 * lens - (self.esc_bits + 8 + _LEN_VALUE_NP[((dists - 1) >> 8) + 1]
                                    + _LEN_VALUE_NP[lens - 1])
                gain = 16 - (self.esc_bits + 10 if maxpos <= 256 else NO_LZ2)
                # Nearest first; accept a longer match only if it gains more.
                while maxval < MAX_LZ_LEN:
                    better = np.flatnonzero((lens > maxval) & (gains > gain))
                    if not len(better):
                        break
                    k = int(better[0])
                    maxval, maxpos, gain = int(lens[k]), int(dists[k]), int(gains[k])
                    lens, dists, gains = lens[k + 1:], dists[k + 1:], gains[k + 1:]
            if p and rle[p - 1] > maxval:
                maxval, maxpos = rle[p - 1] - 1, 1
            if maxval < MAX_LZ_LEN and rlep > maxval:
                # Only reachable at a run start: search earlier runs of the byte.
                assert elr[p] == 0
                runs = runs_by_value[d[p]]
                for start, length in reversed(runs[:run_index[p]]):
                    if start + length - 2 < lo:
                        break
                    if length > maxval:
                        maxval = min(length, rlep)
                        maxpos = p - (start + length - 2) + maxval - 2
                        if maxval == rlep:
                            break
            maxval = min(maxval, n - p)
            if maxpos <= 256 or maxval > 2:
                lzlen[p] = min(maxval, MAX_LZ_LEN)
                lzpos[p] = maxpos
        self.rle, self.elr, self.back_skip = rle, elr, back_skip
        self.lzlen, self.lzpos = lzlen, lzpos

    def _rank(self, hist: list[int]) -> int:
        """Fill rle_values[1..] by descending count; return ranks used."""
        hist = list(hist)
        i = 1
        while i < RANKS:
            best, value = 0, -1
            for v in range(256):
                if hist[v] > best:
                    best, value = hist[v], v
            if best <= 0:
                break
            self.rle_values[i] = value
            hist[value] = -1
            i += 1
        return i - 1

    def _init_rle(self) -> None:
        self.rle_values = [1] + [0] * (RANKS - 1)
        self._rank(self.rle_hist)
        self._init_rle_len()

    def _init_rle_len(self) -> None:
        # Unused rank slots hold 0, so byte 0 ends up with the last slot's
        # cost unless all 31 ranks are in use.
        self.rle_len = [LEN_VALUE[RANKS] + 3] * 256
        for i in range(1, RANKS):
            self.rle_len[self.rle_values[i]] = LEN_VALUE[i]

    def _len_lz(self, length: int, pos: int) -> int:
        if length == 2:
            return self.esc_bits + 2 + 8 if pos <= 256 else NO_LZ2
        return (self.esc_bits + 8 + self.extra
                + LEN_VALUE[((pos - 1) >> (8 + self.extra)) + 1] + LEN_VALUE[length - 1])

    def _len_rle(self, length: int, value: int) -> int:
        out = 0
        while True:
            if length == 1:
                return out + self.esc_bits + 3 + 8
            if length <= 1 << MAX_GAMMA:
                return out + self.esc_bits + 3 + LEN_VALUE[length - 1] + self.rle_len[value]
            part = min(length, MAX_RLE_LEN)
            out += (self.esc_bits + 3 + MAX_GAMMA + 8
                    + LEN_VALUE[((part - 1) >> 8) + 1] + self.rle_len[value])
            length -= part
            if not length:
                return out

    def _optimize_length(self, optimize: bool) -> None:
        d, n = self.data, self.n
        rle, elr, lzlen, lzpos = self.rle, self.elr, self.lzlen, self.lzpos
        length = [0] * (n + 1)
        mode = [LITERAL] * n
        i = n - 1
        while i >= 0:
            r1 = 8 + length[i + 1]
            if not lzlen[i] and not rle[i]:
                length[i] = r1
                i -= 1
                continue
            if rle[i] > MAX_LZ_LEN and elr[i] > 1:
                # Deep in a long run: code it from the run start.
                z = elr[i]
                i -= z
                r2 = self._len_rle(rle[i], d[i]) + length[i + rle[i]]
                if optimize:
                    mini, minv = rle[i], r2
                    for ii in range(rle[i] - 1, max(2, rle[i] - (1 << MAX_GAMMA)) - 1, -1):
                        v = self._len_rle(ii, d[i]) + length[i + ii]
                        if v < minv:
                            mini, minv = ii, v
                    if minv != r2:
                        self.lzopt += r2 - minv
                        rle[i], r2 = mini, minv
                for k in range(z, -1, -1):
                    length[i + k] = r2
                    mode[i + k] = RLE
                i -= 1
                continue
            r2 = r3 = r1 + 1000
            if rle[i]:
                r2 = self._len_rle(rle[i], d[i]) + length[i + rle[i]]
                if optimize:
                    mini, minv = rle[i], r2
                    ii = 2
                    while rle[i] > ii:
                        v = self._len_rle(ii, d[i]) + length[i + ii]
                        if v < minv:
                            mini, minv = ii, v
                        ii <<= 1
                    if minv != r2:
                        self.lzopt += r2 - minv
                        rle[i], r2 = mini, minv
            if lzlen[i]:
                r3 = self._len_lz(lzlen[i], lzpos[i]) + length[i + lzlen[i]]
                if optimize and lzlen[i] > 2:
                    mini, minv = lzlen[i], r3
                    top = self._len_lz(lzlen[i], lzpos[i]) - LEN_VALUE[lzlen[i] - 1]
                    ii = 4
                    while lzlen[i] > ii:
                        v = top + LEN_VALUE[ii - 1] + length[i + ii]
                        if v < minv:
                            mini, minv = ii, v
                        ii <<= 1
                    back = self.back_skip[i]
                    if back and back <= 256:
                        v = self._len_lz(2, back) + length[i + 2]
                        if v < minv:
                            mini, minv = 2, v
                            lzlen[i], lzpos[i], r3 = 2, back, v
                    if minv != r3 and minv < r2:
                        self.lzopt += r3 - minv
                        lzlen[i], r3 = mini, minv
            if r2 <= r1:
                if r2 <= r3:
                    length[i], mode[i] = r2, RLE
                else:
                    length[i], mode[i] = r3, LZ77
            elif r3 <= r1:
                length[i], mode[i] = r3, LZ77
            else:
                length[i] = r1
            i -= 1
        self.mode = mode

    def _walk(self):
        p = 0
        while p < self.n:
            m = self.mode[p]
            step = self.lzlen[p] if m == LZ77 else self.rle[p] if m == RLE else 1
            yield p, m, step
            p += step

    def _optimize_escape(self) -> tuple[int, int]:
        """Schedule escape changes; return (escaped literals, other tokens)."""
        states = 1 << self.esc_bits
        esc8 = 8 - self.esc_bits
        a = [-1] * 256
        b = [-1] * 256
        minp = minv = other = 0
        literals = []
        for p, m, _ in self._walk():
            if m == LITERAL:
                literals.append(p)
            else:
                other += 1
        new_escapes = {}
        for p in reversed(literals):
            k = self.data[p] >> esc8
            new_escapes[p] = minp << esc8
            a[k] = minv + 1
            b[k] = b[minp] + 1
            if k == minp:
                minv += 1
                for q in range(states - 1, -1, -1):
                    if a[q] < minv:
                        minv, minp = a[q], q
                        break
        best = self.n
        start = 0
        for q in range(states - 1, -1, -1):
            if a[q] <= best:
                start, best = q << esc8, a[q]
        self.new_escapes, self.start_escape = new_escapes, start
        return b[start >> esc8], other

    def _optimize_rle(self) -> None:
        hist = [0] * 256
        for p, m, _ in self._walk():
            if m == RLE:
                hist[self.data[p]] += 1
        self.rle_used = self._rank(hist)
        self._init_rle_len()

    def _rescan(self) -> None:
        """Move each shortened copy to the nearest source still long enough."""
        if not self.lzopt:
            return
        d, n, rle, back = self.data, self.n, self.rle, self.back_skip
        for p, m, length in list(self._walk()):
            if m != LZ77 or length <= 2 or length <= rle[p]:
                continue
            rlep = rle[p] or 1
            bot = max(0, p - self.lzpos[p] + 1) + rlep - 1
            i = p - back[p]
            while i >= bot:
                if rlep == 1 or rle[i - rlep + 1] == rlep:
                    top = n - (p + rlep - 1)
                    j = 1
                    while j < top and d[i + j] == d[p + rlep - 1 + j]:
                        j += 1
                    if j + rlep - 1 >= length:
                        self.lzpos[p] = p - i + rlep - 1
                        break
                if not back[i]:
                    break
                i -= back[i]

    def pack(self) -> Parse:
        best_bits = 0
        best_score = None
        for bits in range(1, 9):
            self.esc_bits = bits
            self._optimize_length(False)
            escaped, other = self._optimize_escape()
            score = (bits + 3) * escaped + other * bits
            if best_score is not None and score >= best_score:
                break
            best_bits, best_score = bits, score
        if best_bits == 1:
            self.esc_bits = 0
            self._optimize_length(False)
            escaped, _ = self._optimize_escape()
            if 3 * escaped < best_score:
                best_bits = 0
        self.esc_bits = best_bits
        self._optimize_length(True)

        totals = [0] * 5
        for p, m, length in self._walk():
            if m == LZ77:
                for extra in range(5):
                    self.extra = extra
                    totals[extra] += self._len_lz(length, self.lzpos[p])
        self.extra = min(range(5), key=lambda e: (totals[e], e))
        if self.extra:
            self._optimize_length(True)

        self._optimize_escape()
        self._optimize_rle()
        self._rescan()
        tokens = [(m, p, length, self.lzpos[p] if m == LZ77 else 0)
                  for p, m, length in self._walk()]
        return Parse(tokens, self.esc_bits, self.extra, self.start_escape,
                     self.new_escapes, list(self.rle_values), self.rle_used)


def parse(data: bytes) -> Parse:
    """Return Pucrunch 1.11's token choices for data."""
    return _Packer(bytes(data)).pack()
