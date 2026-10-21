# Special scene tile frames

The `SpecialSceneFrames` group holds `gTrainWindowNightPalette` and 128 raw
4 bpp tile frames. `RoomScriptOpPlaySpecialSceneEffect` animates them with
the BG tile animation system. The frame format is in
`tools/graphic_blob/tile_frames.py`.

## Picture

The frames show the scenery outside the Hogwarts Express windows, in rooms
5, 6 and 7. A frame holds 40 tiles, and they are not an 8x5 image. They are
tile numbers 0-39 of the room's layer 0, palette bank 15 (**PROVEN** from the
layer files), so the room's block map arranges them into the four window
views. To see one, draw the room's layer 0 with tiles 0-39 taken from the
frame and palette bank 15 of the room's palette A or of
`gTrainWindowNightPalette`. Stepping through the 128 frames animates it.

The three animation resources list the same frames with different
durations:

| Resource | Mode | Durations | Looks like |
|---|---|---|---|
| `g_aSpecialSceneBg2` | 2 | 1 for all 128 | the moving train (the rooms' default) |
| `g_aSpecialSceneBg1` | 1 | 2 x16, 4 x11, 8 x9, then 0 | the train slowing to a stop (`Room06V1Chain7`, "Why's the train stopped?") |
| `g_aSpecialSceneBg0` | 0 | 0 for all 128 | stopped |

Mode 3 loads `gTrainWindowNightPalette` in place of the room's palette.
These are probably the day and night looks of the scenery, switched when
the Dementors appear in `Room06V3Chain29` (**UNCONFIRMED**).

The `ServePumpkinJuiceFrames` and `DivinationTeaFrames` pools use the same
frame format, with GammaLz-compressed frames.
