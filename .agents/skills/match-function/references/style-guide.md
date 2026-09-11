# Decompiled C style

Use these conventions for new decompilations. Existing declarations and public names remain
stable unless the task requires changing them. Avoid formatting unrelated files.

- Four spaces; no tabs. Allman braces for functions and compound statements.
- Omit braces for a simple single-statement branch/loop; use braces for multi-statement
  bodies and where nesting would be ambiguous. Keep `else` on its own line.
- Put a space after control keywords and around binary operators; write `Type *pointer`.
- Functions use PascalCase; locals/parameters use descriptive lowerCamelCase; macros
  use UPPER_SNAKE_CASE. Preserve established global/field conventions from headers
  (including `g_`, `p`, `b`, `w`, `dw` prefixes) rather than inventing competing names.
- Include `types.h` and owning subsystem headers. Reuse declarations instead of local
  duplicate structs or extern prototypes. Keep includes grouped at the top.
- Use the project's `s8/u8/s16/u16/s32/u32` types for known widths. Choose locals by
  semantics and generated operations; most arithmetic naturally uses s32/u32. Preserve
  signedness when it affects division, comparisons, extension or overflow.
- Declare locals at the start of a block, one per line, with consistent meaningful roles.
  Reuse one local across disjoint sites when they share meaning; do not borrow a loop
  index as a flag merely to perturb allocation. Preserve declaration order while matching.
- Use enum names and named constants for understood values. Decimal for ordinary counts;
  hex for masks and hardware/address values. Use typed field/array access once known.
- Prefer multiplication, division, indexing and normal loops when they express the behavior.
  Use shifts/masks for bit operations. Cast only at an actual type/width boundary; repeated
  pointer casts usually signal a missing type. Avoid explicit hard-register assignments.
- Prefer structured joins; a goto can express a real shared cleanup/exit, but excessive
  jumps or compiler-only constructs require discussion before acceptance.
- Comments explain game rules, units, sentinel values or uncertain meaning. Do not annotate
  obvious operations, register choices, source spelling or historical matching attempts.
- Keep logical sections separated by one blank line. Wrap long expressions at meaningful
  boundaries, generally around 100 columns; don't distort readable expressions to fit a ruler.

```c
u32 ComputeDamage(u32 damage, u8 statusFlags)
{
    if (statusFlags & AttackWeakened)
        damage /= 2;

    return damage;
}
```

Renaming locals is usually byte-neutral; changing declarations, types, expression order or
control flow may affect allocation anywhere in a function. Verify edits rather than adding
comments to discourage future changes. The source also serves as a readable base for mods.
