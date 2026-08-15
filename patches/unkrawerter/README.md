Patches against MCJack123/UnkrawerterGBA @ 999e310fcc62a0d21e783549051a06a2a3fbd848,
applied in order via flake.nix.

0001 - fixes a heap-corrupting out-of-bounds write in the XM writer. A
        pattern row's channel index is a 5-bit field (0-31) independent of
        the module's actual channel count, but `unkrawerter_writeModuleToXM`
        allocates its per-channel `memory[]` array sized to the module's
        real channel count and only bounds-checks `channel` against it
        *after* already indexing `memory[channel]` for five S3M effect
        types (volume slide, porta up/down, and their vibrato/porta
        combos). Any module using one of those effects on an out-of-range
        channel corrupts the heap -- reliably reproduced as a `free():
        invalid size` crash partway through `-x` export once enough
        low-channel-count modules are exported in one run (see
        docs/formats/krawall.md; this repo's ROMs have several modules
        with fewer than the max 16-ish channels). Confirmed via a source
        diff against the original: the fix only skips the `memory[channel]`
        read/write itself for out-of-range channels (which are discarded a
        few lines later anyway) -- verified byte-identical output on every
        module that didn't already crash.
