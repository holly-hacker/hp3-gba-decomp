#include "actor.h"
#include "hero.h"

// Exchanges the characters of two party members' actors along with their palettes; the
// actor that ends up with the leader's character becomes the player (actor type 0) and
// the other a follower (0x12). Returns b.
Actor *SwapPartyMemberCharacters(Actor *a, Actor *b)
{
    u32 tmp;
    u32 flagsB;

    a->dwFlags &= ~ActorFlagVisible;
    b->dwFlags &= ~ActorFlagVisible;

    tmp = a->wCharacterId_candidate;
    a->wCharacterId_candidate = b->wCharacterId_candidate;
    b->wCharacterId_candidate = tmp;
    if (b->wCharacterId_candidate == g_bPartyCharId0)
    {
        g_bPartyCharId0 = a->wCharacterId_candidate;
        a->wActorType = RoomActorType_Player;
        b->wActorType = RoomActorType_PartyFollower;
    }
    else if (a->wCharacterId_candidate == g_bPartyCharId0)
    {
        g_bPartyCharId0 = b->wCharacterId_candidate;
        b->wActorType = RoomActorType_Player;
        a->wActorType = RoomActorType_PartyFollower;
    }

    tmp = a->oam.paletteNum;
    a->oam.paletteNum = b->oam.paletteNum;
    b->oam.paletteNum = tmp;

    tmp = (u32)a->pPendingPalette;
    a->pPendingPalette = b->pPendingPalette;
    b->pPendingPalette = (const void *)tmp;

    tmp = a->dwPendingPaletteFlags;
    a->dwPendingPaletteFlags = b->dwPendingPaletteFlags;
    b->dwPendingPaletteFlags = tmp;

    tmp = a->dwFlags & ActorFlagHasPaletteSlot;
    flagsB = b->dwFlags & ActorFlagHasPaletteSlot;
    a->dwFlags &= ~ActorFlagHasPaletteSlot;
    b->dwFlags &= ~ActorFlagHasPaletteSlot;
    a->dwFlags |= flagsB;
    b->dwFlags |= tmp;

    SetActorAssetRecord(a, &g_aPartyWalkAssets[a->wCharacterId_candidate]);
    SetActorAssetRecord(b, &g_aPartyWalkAssets[b->wCharacterId_candidate]);
    SetActorAnimFrame(a, g_abPartyStandFrames[a->bFacing]);
    SetActorAnimFrame(b, g_abPartyStandFrames[b->bFacing]);
    a->oam.hFlip = a->bFacing > DirectionDown;
    b->oam.hFlip = b->bFacing > DirectionDown;
    b->bFacing = 0x2A;  // matches no trail facing, so b restarts its walk animation

    a->dwFlags |= ActorFlagVisible;
    b->dwFlags |= ActorFlagVisible;
    return b;
}
