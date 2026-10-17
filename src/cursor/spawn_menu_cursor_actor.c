#include "types.h"
#include "actor.h"
#include "color.h"
#include "palette.h"
#include "cursor.h"
#include "background.h"
#include "gen/graphics/menus.h"

Actor *SpawnMenuCursorActor(u32 kind)
{
    Actor *actor;
    const u16 *pPaletteFrames;

    if (kind == 5)
    {
        actor = SpawnActor(0xF, 0, 0, g_MenuCursorKind5Asset.pPalette);
        SetActorSprite(actor, &g_MenuCursorKind5Asset);
        SetActorAnimFrame(actor, 0);
        actor->oam.priority = 0;
    }
    else
    {
        actor = AllocActorOfType(kind);
        actor->oam.objMode = 0;
        actor->oam.bpp8 = 0;
        actor->oam.priority = 0;
        actor->dwFlags = ActorFlagKeepPaletteSlot | ActorFlagHasAnimation | ActorFlagHasTickLogic;
        actor->anim.bAnimFrameDelay = 1;
        actor->pfnTick = NULL;
        actor->bDepthSortBias = 0x80;
        SetActorSprite(actor, &g_MenuCursorAsset);

        switch (kind)
        {
        case 0:
            actor->dwFlags |= ActorFlagHasSpriteCells;
            actor->oam.paletteNum = 0;
            SetActorAnimFrame(actor, 0);
            SetActorPosition(actor, 0xE8, 0x92);
            SetActorOrbitY(actor, 0, 0x800, 4);
            actor->oam.bpp8 = 1;
            SetActorSprite(actor, &g_MenuCursor8bppAsset);
            SetActorAnimFrame(actor, 0);
            LoadMenuCursor8bppColors();
            break;
        case 1:
            actor->dwFlags |= ActorFlagHasSpriteCells | ActorFlagVisible;
            actor->oam.paletteNum = 0;
            actor->oam.vFlip = 1;
            SetActorPosition(actor, 0x4D, 0x4E);
            actor->oam.bpp8 = 1;
            SetActorSprite(actor, &g_MenuCursor8bppAsset);
            SetActorAnimFrame(actor, 0);
            LoadMenuCursor8bppColors();
            break;
        case 2:
            actor->dwFlags |= ActorFlagVisible;
            SetActorAnimFrame(actor, 1);
            AttachActorPalette(actor, (const ObjPalette *)gMainMenuPalette);
            break;
        case 7:
            actor->dwFlags |= ActorFlagHasSpriteCells | ActorFlagVisible;
            actor->oam.paletteNum = 0;
            actor->oam.vFlip = 1;
            SetActorAnimFrame(actor, 2);
            SetActorOrbitY(actor, 0x80, 0x400, 2);
            break;
        case 6:
            actor->dwFlags |= ActorFlagHasSpriteCells | ActorFlagVisible;
            actor->oam.paletteNum = 0;
            actor->oam.vFlip = 1;
            SetActorAnimFrame(actor, 0);
            SetActorOrbitY(actor, 0, 0x400, 2);
            break;
        case 3:
            actor->dwFlags |= ActorFlagHasSpriteCells | ActorFlagVisible;
            actor->oam.paletteNum = 0;
            actor->oam.vFlip = 1;
            SetActorAnimFrame(actor, 0);
            SetActorOrbitY(actor, 0, 0x800, 2);
            break;
        case 4:
            pPaletteFrames = GRAPHIC_BLOB_PALETTE_COLORS(gMenuCursor001);
            actor->dwFlags |= ActorFlagHasSpriteCells | ActorFlagVisible;
            actor->wCharacterId_candidate = 0xB;
            if (!g_dwMenuCursorParticleGfxLoaded)
            {
                g_dwMenuCursorParticleGfxLoaded = 1;
                sub_08030A1C(0, 0, &g_MenuCursorParticleAsset);
            }
            SetActorAnimData(actor, &g_MenuCursorSparkleAnimAsset, g_MenuCursorSparkleAnimData, 0);
            AttachActorPaletteUnshared(actor, (const ObjPalette *)gMenuCursorSparklePalette);
            // Pulses the cursor's own palette slot.
            g_nMenuCursorPaletteEffect = StartPaletteEffectWithFrameCount(actor->oam.paletteNum * 16, 0x10, 0xF, 0,
                0x1D, pPaletteFrames, 6);
            CreateMenuCursorEmitter(actor);
            break;
        }
    }

    return actor;
}
