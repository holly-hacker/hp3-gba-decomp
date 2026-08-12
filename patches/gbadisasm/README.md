Patches against camthesaxman/gbadisasm @ e35982bd105fd8b9bb497d955900f8375cdc9e60
(upstream inactive since 2020-01), applied in order via flake.nix.

0001 - fixes a double-free in the Thumb invalid-instruction fallback path
0002 - fixes a stale-pointer-after-realloc bug in indirect-jump handling
0003 - fixes output silently truncating before the true end of the ROM
        when nothing labels the tail
