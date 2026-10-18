Patches against gcc-core-3.0.2, applied in order via flake.nix. Both let
a modern host compiler build `cc1`; generated code is unchanged.

0001 - rewrites the cast-as-lvalue increments in `obstack.h`'s GNU C
        macros (`*((void **) p)++ = x`), which GCC 4 and later reject, as
        a store followed by a separate pointer increment.

0002 - assigns a declaration's RTL in `arm.c` through `SET_DECL_RTL`
        instead of through the `DECL_RTL` accessor, which modern GCC
        rejects as an assignment target.
