# Spells

## Casts for unlock

How many casts are needed of a specific spell before it levels up. Note that each spell has a maximum level.

| Level | Threshold |
| ----- | --------- |
| Uno   | n/a       |
| Duo   | 25        |
| Tria  | 50        |

## Spell data

Individual stats for each spell.

Damage dealt by the player is calculated as \\(P_\text{base} + \frac{P_\text{scale}\times\text{lvl}}{9} \\). This is later scaled by
character modifiers, buffs, enemy resistences and critical hits.

| Spell              | Level | MP Cost | Base power | Power scale | Note         |
| ------------------ | ----- | ------- | ---------- | ----------- | ------------ |
| Flipendo           | Uno   | 0       | 10         | 4           |              |
| Flipendo           | Duo   | 10      | 20         | 8           |              |
| Flipendo           | Tria  | 20      | 15         | 10          | Multi-target |
| Verdimillious      | Uno   | 3       | 15         | 4           |              |
| Verdimillious      | Duo   | 15      | 25         | 12          |              |
| Verdimillious      | Tria  | 25      | 20         | 14          | Multi-target |
| Incendio           | Uno   | 6       | 23         | 8           |              |
| Incendio           | Duo   | 20      | 35         | 16          |              |
| Incendio           | Tria  | 30      | 45         | 18          |              |
| Diffindo           |       | 10      | 30         | 18          |              |
| Diffindo           | Duo   | 0       | 30         | 19          | Unused       |
| Diffindo           | Tria  | 0       | 40         | 20          | Unused       |
| Wingardium Leviosa |       | 20      | 20         | 20          |              |
| Wingardium Leviosa | Duo   | 30      | 21         | 21          | Unused       |
| Wingardium Leviosa | Tria  | 40      | 22         | 22          | Unused       |
| Petrificus Totalus | Uno   | 10      | 0          | 0           |              |
| Petrificus Totalus | Duo   | 15      | 0          | 0           |              |
| Petrificus Totalus | Tria  | 20      | 0          | 0           | Unused       |
| Glacius            | Uno   | 15      | 18         | 18          |              |
| Glacius            | Duo   | 25      | 20         | 20          |              |
| Glacius            | Tria  | 0       | 20         | 20          | Unused       |
| Fumos              | Uno   | 8       | 0          | 0           |              |
| Fumos              | Duo   | 30      | 0          | 0           |              |
| Fumos              | Tria  | 0       | 0          | 0           | Unused       |
| Spongify           |       | 10      | 0          | 0           |              |
