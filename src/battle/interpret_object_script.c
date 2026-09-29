#include "types.h"
#include "battle/battle.h"
#include "battle/effect_script.h"
#include "game/rewards.h"
#include "graphics/audio.h"
#include "graphics/display.h"
#include "graphics/graphics.h"
#include "graphics/scanline_effects.h"
#include "hw/io_regs.h"
#include "hw/vblank.h"
#include "menu/minigame_menu.h"
#include "mt19937.h"

// Runs an effect object's bytecode script (docs/formats/battle_scripts.md).
// Each call executes opcodes until one returns: the wait opcodes hand the
// object to a tick handler that resumes the interpreter later.
void InterpretObjectScript(Object *obj)
{
    BattleFighter *targetFighter;
    BattleFighter *casterFighter;
    const u8 *script;
    u32 i;
    u32 opcode;
    u16 *pc;
    u8 effectId;
    u8 args[17];
    s32 x;
    s32 y;
    s32 n;
    ScreenPoint pos;
    ScreenPoint offset;
    Object *child;
    u32 done;

    targetFighter = g_pFightState->pFighters + g_effectStaging.bTargetIndex;
    casterFighter = g_pFightState->pFighters + g_effectStaging.bCasterIndex;
    TickParticleEmitters();
    done = 0;
    do  // done is never set; every exit is a return
    {
        pc = &obj->scriptState.wScriptPc;
        effectId = obj->modeState.effect.bEffectId;
        script = g_apEffectScripts[effectId];
        opcode = script[*pc];
        for (i = 0; i <= g_abScriptOpcodeLengths[opcode]; i++)
            args[i] = script[(*pc)++];
        switch (opcode)
        {
        case 0x00:  // End
            obj->dwFlags = (obj->dwFlags & ~ObjectFlagVisible) | ObjectFlagPendingDestroy | ObjectFlagAnimFrameLoaded;
            return;
        case 0x01:  // SetObjectAnim
            SetObjectAnimData(obj, &g_aEffectAnimAssets[args[1]], g_aEffectAnimData_candidate[args[1]], args[2]);
            break;
        case 0x02:  // SetObjectAnimAndPalette: SetObjectAnim, then swaps in that animation's palette
            SetObjectAnimData(obj, &g_aEffectAnimAssets[args[1]], g_aEffectAnimData_candidate[args[1]], args[2]);
            ReleaseObjectPalette(obj);
            AttachObjectPalette(obj, g_aEffectAnimAssets[args[1]].pPalette);
            break;
        case 0x03:  // SetObjectAnimFromTable2: sets asset record and animation from the second table
            SetObjectAssetRecord(obj, &g_aEffectAnimAssets2[args[1]]);
            SetObjectAnimData(obj, &g_aEffectAnimAssets2[args[1]], g_aEffectAnimData2_candidate[args[1]], args[2]);
            obj->pAnimTable = (ObjectAssetRecord *)&g_aEffectAnimAssets2[args[1]];
            break;
        case 0x04:  // SetObjectAnimFromTable2AndPalette: like 0x03, then swaps in the palette
            SetObjectAssetRecord(obj, &g_aEffectAnimAssets2[args[1]]);
            SetObjectAnimData(obj, &g_aEffectAnimAssets2[args[1]], g_aEffectAnimData2_candidate[args[1]], args[2]);
            ReleaseObjectPalette(obj);
            AttachObjectPalette(obj, g_aEffectAnimAssets2[args[1]].pPalette);
            break;
        case 0x05:  // SetEffectPalette: swaps in effect palette N
            ReleaseObjectPalette(obj);
            AttachObjectPalette(obj, g_apEffectPalettes[args[1]]);
            break;
        case 0x07:  // UnmuteMusic: unmutes the music channels
            UnmuteAllMusicChannels();
            break;
        case 0x08:  // WaitFrames
            obj->wActionVariant = args[1];
            obj->dwStateTimer = 0;
            obj->pfnTick = WaitFramesTick;
            return;
        case 0x09:  // WaitForCounter
            obj->wActionVariant = obj->unk_DC.bEnemyAttackPhase_candidate + 1;
            obj->pfnTick = WaitForCounterTick;
            return;
        case 0x0A:  // WaitForFieldClear
            obj->pfnTick = WaitForFieldClearTick;
            return;
        case 0x0B:  // MoveToAbsolute: moves to absolute (x, y) over a duration
            x = args[1];
            y = args[2];
            StartObjectMove(obj, x << 16, y << 16, args[3]);
            break;
        case 0x0C:  // MoveTo
            if (args[4] == 0)
            {
                x = g_awBattleSlotPosX_candidate[g_effectStaging.bScriptParam] + (s8)args[1];
                y = g_abBattleSlotPosY_candidate[g_effectStaging.bScriptParam] + (s8)args[2];
            }
            else
            {
                pos = ComputeEffectSpawnPosition();
                x = (s8)args[1] + pos.x;
                y = (s8)args[2] + pos.y;
            }
            if (args[5] != 0)
            {
                sub_08001AA8(targetFighter->pObject, args[5] - 1, &offset);
                x += offset.x;
                y += offset.y;
            }
            StartObjectMove(obj, x << 16, y << 16, args[3]);
            break;
        case 0x0D:  // StopMove: stops movement: clears move duration and velocity
            obj->wUnk86 = 0;
            obj->wMoveDuration = 0;
            SetObjectVelocity(obj, 0, 0);
            break;
        case 0x0E:  // SpawnEffectDetached
            child = CreateEffectScriptObject(args[1], 0);
            child->modeState.effect.abLocal[0] = obj->modeState.effect.abLocal[0] + 1;
            child->modeState.effect.abLocal[1] = obj->modeState.effect.abLocal[1] + 1;
            child->pLinkedObject_candidate = obj->pLinkedObject_candidate;
            break;
        case 0x0F:  // SpawnEffect
            child = CreateEffectScriptObject(args[1], 1);
            child->modeState.effect.abLocal[0] = obj->modeState.effect.abLocal[0] + 1;
            child->modeState.effect.abLocal[1] = obj->modeState.effect.abLocal[1] + 1;
            child->pLinkedObject_candidate = obj->pLinkedObject_candidate;
            break;
        case 0x10:  // SpawnEffectAtSelfDetached: spawns a detached child at this object's position
            child = CreateEffectScriptObject(args[1], 0);
            child->modeState.effect.abLocal[0] = obj->modeState.effect.abLocal[0] + 1;
            child->modeState.effect.abLocal[1] = obj->modeState.effect.abLocal[1] + 1;
            child->pLinkedObject_candidate = obj->pLinkedObject_candidate;
            SnapObjectPosition(child, obj->nX, obj->nY);
            break;
        case 0x11:  // SpawnEffectAtSelf: spawns a child at this object's position
            child = CreateEffectScriptObject(args[1], 1);
            child->modeState.effect.abLocal[0] = obj->modeState.effect.abLocal[0] + 1;
            child->modeState.effect.abLocal[1] = obj->modeState.effect.abLocal[1] + 1;
            child->pLinkedObject_candidate = obj->pLinkedObject_candidate;
            SnapObjectPosition(child, obj->nX, obj->nY);
            break;
        case 0x12:  // SpawnEffectOffsetDetached: spawns a detached child at this object's position plus a scaled offset
            child = CreateEffectScriptObject(args[1], 0);
            child->modeState.effect.abLocal[0] = obj->modeState.effect.abLocal[0] + 1;
            child->modeState.effect.abLocal[1] = obj->modeState.effect.abLocal[1] + 1;
            child->pLinkedObject_candidate = obj->pLinkedObject_candidate;
            x = (s8)args[2] * (args[3] << 16) + obj->nX;
            y = (s8)args[4] * (args[5] << 16) + obj->nY;
            SnapObjectPosition(child, x, y);
            break;
        case 0x13:  // SpawnEffectOffset: spawns a child at this object's position plus a scaled offset
            child = CreateEffectScriptObject(args[1], 1);
            child->modeState.effect.abLocal[0] = obj->modeState.effect.abLocal[0] + 1;
            child->modeState.effect.abLocal[1] = obj->modeState.effect.abLocal[1] + 1;
            child->pLinkedObject_candidate = obj->pLinkedObject_candidate;
            x = (s8)args[2] * (args[3] << 16) + obj->nX;
            y = (s8)args[4] * (args[5] << 16) + obj->nY;
            SnapObjectPosition(child, x, y);
            break;
        case 0x16:  // SpawnEffectSharedTiles: spawns a child that shares tiles
            child = CreateEffectScriptObject(args[1], 1);
            child->bObjectPoolAuxSlot = 0;
            child->bDrawFlags |= ObjectDrawFlagShareTiles;
            child->modeState.effect.abLocal[0] = obj->modeState.effect.abLocal[0] + 1;
            child->modeState.effect.abLocal[1] = obj->modeState.effect.abLocal[1] + 1;
            child->pLinkedObject_candidate = obj->pLinkedObject_candidate;
            break;
        case 0x17:  // ToggleObjectFlipX
            SetObjectFlippedX(obj, !IsObjectFlippedX(obj));
            break;
        case 0x18:  // ToggleObjectFlipY: toggles a second flip state (likely vertical)
            sub_08003788(obj, !sub_08003954(obj));
            break;
        case 0x19:  // MoveBy: moves by a signed (dx, dy) in whole pixels
            SnapObjectPosition(obj, obj->nX + ((s8)args[1] << 16), obj->nY + ((s8)args[2] << 16));
            break;
        case 0x1A:  // MoveBy_2: moves by a signed (dx, dy) in whole pixels
            SnapObjectPosition(obj, obj->nX + ((s8)args[1] << 16), obj->nY + ((s8)args[2] << 16));
            break;
        case 0x1B:  // SnapToCaster: snaps to the caster's position, optionally offset
            pos.x = (s16)(casterFighter->pObject->nX >> 16);
            pos.y = (s16)(casterFighter->pObject->nY >> 16);
            if (args[1] != 0)
            {
                sub_08001AA8(casterFighter->pObject, args[1] - 1, &offset);
                pos.x += offset.x;
                pos.y += offset.y;
            }
            SetObjectPosition(obj, pos.x, pos.y);
            break;
        case 0x1C:  // TeleportToSlotPosition
            x = g_awBattleSlotPosX_candidate[g_effectStaging.bScriptParam];
            y = g_abBattleSlotPosY_candidate[g_effectStaging.bScriptParam];
            if (args[1] != 0)
            {
                sub_08001AA8(targetFighter->pObject, args[1] - 1, &offset);
                x += offset.x;
                y += offset.y;
            }
            SetObjectPosition(obj, x, y);
            break;
        case 0x1D:  // SetVelocity: sets velocity from signed whole-pixel values
            SetObjectVelocity(obj, (s8)args[1] << 16, (s8)args[2] << 16);
            break;
        case 0x1E:  // SetVelocity16: sets velocity from signed 8.8-style values
            {
                s32 velX;
                s32 velY;

                if (args[1] == 0xFF)
                    velX = -((args[2] << 16) + (args[3] << 8));
                else
                    velX = (args[2] << 16) + (args[3] << 8);
                if (args[4] == 0xFF)
                    velY = -((args[5] << 16) + (args[6] << 8));
                else
                    velY = (args[5] << 16) + (args[6] << 8);
                SetObjectVelocity(obj, velX, velY);
            }
            break;
        case 0x1F:  // opcode_1F: BG helper call with signed x and y
            sub_08007D14(args[1], (s8)args[1] << 16, (s8)args[2] << 16);
            break;
        case 0x20:  // SetLocal
            obj->modeState.effect.abLocal[args[1]] = args[2];
            break;
        case 0x21:  // IncrementLocal
            obj->modeState.effect.abLocal[args[1]]++;
            break;
        case 0x22:  // SkipBytes: skips forward N script bytes
            *pc += args[1];
            break;
        case 0x23:  // GotoIfContextLow: jumps to a label when the context value is <= 2 or 0x3E9
            if (g_effectStaging.wContextValue <= 2 || g_effectStaging.wContextValue == 0x3E9)
                sub_0801B710(obj, args[1]);
            break;
        case 0x24:  // GotoIfLocalAEqual
            if (obj->modeState.effect.abLocal[0] == args[1])
                sub_0801B710(obj, args[2]);
            break;
        case 0x25:  // GotoIfScriptParamEqual: jumps to a label when the script param equals the operand
            if (g_effectStaging.bScriptParam == args[1])
                sub_0801B710(obj, args[2]);
            break;
        case 0x26:  // GotoIfLocalANotEqual
            if (obj->modeState.effect.abLocal[0] != args[1])
                sub_0801B710(obj, args[2]);
            break;
        case 0x27:  // GotoIfFighterRosterMatches
            {
                for (n = 0; n < 2; n++)
                {
                    if (g_abEffectRosterIdPair_candidate[n] == targetFighter->bRosterIndex)
                        sub_0801B710(obj, args[1]);
                }
            }
            break;
        case 0x28:  // GotoIfLocalAEqual_2
            if (obj->modeState.effect.abLocal[0] == args[1])
                sub_0801B710(obj, args[2]);
            break;
        case 0x29:  // GotoIfScriptParamEqual_2: jumps to a label when the script param equals the operand
            if (g_effectStaging.bScriptParam == args[1])
                sub_0801B710(obj, args[2]);
            break;
        case 0x2A:  // GotoIfLocalANotEqual_2
            if (obj->modeState.effect.abLocal[0] != args[1])
                sub_0801B710(obj, args[2]);
            break;
        case 0x2B:  // GotoIfFighterRosterMatches_2
            {
                for (n = 0; n < 2; n++)
                {
                    if (g_abEffectRosterIdPair_candidate[n] == targetFighter->bRosterIndex)
                        sub_0801B710(obj, args[1]);
                }
            }
            break;
        case 0x2C:  // GotoIfLocalBEqual: jumps to a label when local B equals the operand
            if (obj->modeState.effect.abLocal[1] == args[1])
                sub_0801B710(obj, args[2]);
            break;
        case 0x2D:  // GotoIfLocalBNotEqual: jumps to a label when local B differs from the operand
            if (obj->modeState.effect.abLocal[1] != args[1])
                sub_0801B710(obj, args[2]);
            break;
        case 0x2E:  // GotoIfLocalBEqual_2: jumps to a label when local B equals the operand
            if (obj->modeState.effect.abLocal[1] == args[1])
                sub_0801B710(obj, args[2]);
            break;
        case 0x2F:  // GotoIfLocalBNotEqual_2: jumps to a label when local B differs from the operand
            if (obj->modeState.effect.abLocal[1] != args[1])
                sub_0801B710(obj, args[2]);
            break;
        case 0x30:  // AdvanceAttackOutcome: advances the caster's attack-outcome counter and publishes it
            g_pFightState->pFighters[g_effectStaging.bCasterIndex].pObject->scriptState.bytes.bAttackOutcomeState++;
            g_pFightState->bAttackAnimState_candidate = g_pFightState->pFighters[g_effectStaging.bCasterIndex].pObject->scriptState.bytes.bAttackOutcomeState;
            if (g_pFightState->pAttackAnimObject_candidate == NULL)
                g_pFightState->pAttackAnimObject_candidate = g_pFightState->pFighters[g_effectStaging.bCasterIndex].pObject;
            break;
        case 0x31:  // CreateEmitter12: creates an emitter (12 operands)
            g_effectStaging.pEmitter_candidate = sub_0801B774(obj, args[1], args[2], args[3], args[4], args[5], args[6], args[7], args[8], args[9], args[10], args[11], args[12]);
            g_effectStaging.pEmitter_candidate->bParalysisEffectFlag_candidate = 2;
            break;
        case 0x32:  // CreateEmitter8: creates an emitter (8 operands)
            g_effectStaging.pEmitter_candidate = sub_0801B870(obj, args[1], args[2], args[3], args[4], args[5], args[6], args[7], args[8]);
            g_effectStaging.pEmitter_candidate->bParalysisEffectFlag_candidate = 2;
            break;
        case 0x33:  // CreateEmitterOnSelf: creates an emitter on this object
            g_effectStaging.pEmitter_candidate = CreateBattleEffectEmitter_candidate(obj, args[1], args[2], args[3], args[4], args[5], args[6], args[7], args[8], args[9], args[10], args[11], args[12], args[13], args[14], args[15], args[16]);
            g_effectStaging.pEmitter_candidate->bParalysisEffectFlag_candidate = 2;
            break;
        case 0x34:  // CreateEmitterOnTarget: creates an emitter on the target's object
            g_effectStaging.pEmitter_candidate = CreateBattleEffectEmitter_candidate(targetFighter->pObject, args[1], args[2], args[3], args[4], args[5], args[6], args[7], args[8], args[9], args[10], args[11], args[12], args[13], args[14], args[15], args[16]);
            g_effectStaging.pEmitter_candidate->bParalysisEffectFlag_candidate = 2;
            break;
        case 0x35:  // opcode_35: effect object asset call
            sub_08030A1C(args[1], args[2], &g_aEffectObjectAssets[args[3]]);
            break;
        case 0x36:  // opcode_36: particle system setup
            sub_0803171C();
            sub_08031668(args[1], args[2]);
            break;
        case 0x37:  // opcode_37: particle system call
            sub_0803171C();
            break;
        case 0x38:  // ReleaseWindupEmitter: releases this object's windup emitter
            ReleaseParticleEmitter_candidate(obj->pWindupParticleEmitter);
            break;
        case 0x39:  // ReleaseKind2Emitters: releases every kind-2 emitter
            {
                ListNode *node;
                ListNode *next;

                for (node = g_pParticleEmitterActiveListHead; node != NULL; node = next)
                {
                    next = node->pNext;
                    if (((ParticleEmitter *)node)->bParalysisEffectFlag_candidate == 2)
                        ReleaseParticleEmitter_candidate((ParticleEmitter *)node);
                }
            }
            break;
        case 0x3B:  // SetBehaviorFlags: sets behavior flag bits
            obj->modeState.effect.bBehaviorFlags |= args[1];
            break;
        case 0x3C:  // ClearBehaviorFlags: clears behavior flag bits
            obj->modeState.effect.bBehaviorFlags &= ~args[1];
            break;
        case 0x3D:  // BlendEffectPalette: palette blend on an effect palette
            sub_0800D254(g_apEffectPalettes[args[2]], args[1] << 4, args[3] << 4);
            break;
        case 0x3E:  // SetOamPalette: sets the OAM palette bank
            obj->oam.paletteNum = args[1];
            break;
        case 0x41:  // StartOrbitMotion
            CopyOrbitParamsFromTable(obj, g_aEffectOrbitParams_candidate[args[1]]);
            obj->orbitState.awOrbit[0] += obj->modeState.effect.abLocal[0] * args[2] << 8;
            break;
        case 0x42:  // StartOrbitMotionRandom: starts orbit motion with a random angle
            CopyOrbitParamsFromTable(obj, g_aEffectOrbitParams_candidate[args[1]]);
            obj->orbitState.awOrbit[0] = Mt19937RandMax(0xFF) << 8;
            obj->orbitState.awOrbit[1] = -(u16)obj->orbitState.awOrbit[0];
            break;
        case 0x43:  // SaveOrbit: saves the orbit parameters
            g_effectStaging.awSavedOrbit[0] = obj->orbitState.awOrbit[0];
            g_effectStaging.awSavedOrbit[1] = obj->orbitState.awOrbit[2];
            g_effectStaging.awSavedOrbit[2] = obj->orbitState.awOrbit[4];
            g_effectStaging.awSavedOrbit[3] = obj->orbitState.awOrbit[1];
            g_effectStaging.awSavedOrbit[4] = obj->orbitState.awOrbit[3];
            g_effectStaging.awSavedOrbit[5] = obj->orbitState.awOrbit[5];
            break;
        case 0x44:  // RestoreOrbit: restores the saved orbit parameters
            obj->orbitState.awOrbit[0] = g_effectStaging.awSavedOrbit[0];
            obj->orbitState.awOrbit[2] = g_effectStaging.awSavedOrbit[1];
            obj->orbitState.awOrbit[4] = g_effectStaging.awSavedOrbit[2];
            obj->orbitState.awOrbit[1] = g_effectStaging.awSavedOrbit[3];
            obj->orbitState.awOrbit[3] = g_effectStaging.awSavedOrbit[4];
            obj->orbitState.awOrbit[5] = g_effectStaging.awSavedOrbit[5];
            break;
        case 0x45:  // StartCasterOrbitMotion
            CopyOrbitParamsFromTable(casterFighter->pObject, g_aEffectOrbitParams_candidate[args[1]]);
            casterFighter->pObject->orbitState.awOrbit[0] += obj->modeState.effect.abLocal[0] * args[2] << 8;
            break;
        case 0x46:  // SetAffineScale1: sets affine scale (mode 1)
            SetObjectAffineTransform(obj, (args[1] << 16) + (args[2] << 8), (args[3] << 16) + (args[4] << 8), 0, 1);
            break;
        case 0x47:  // SetAffineScale3: sets affine scale (mode 3)
            SetObjectAffineTransform(obj, (args[1] << 16) + (args[2] << 8), (args[3] << 16) + (args[4] << 8), 0, 3);
            break;
        case 0x48:  // StartAffineWobble: sets a rotating affine transform and behavior flag 2
            obj->modeState.effect.bBehaviorFlags |= 2;
            obj->modeState.effect.abParams[3] = args[5];
            obj->modeState.effect.abParams[0] = args[6];
            obj->modeState.effect.abParams[1] = args[7];
            obj->modeState.effect.abParams[2] = args[8];
            SetObjectAffineTransform(obj, (args[1] << 16) + (args[2] << 8), (args[3] << 16) + (args[4] << 8), args[5] * -0x7FF, 3);
            break;
        case 0x49:  // StopAffineWobble: clears behavior flag 2 and its parameters
            obj->modeState.effect.bBehaviorFlags &= ~2;
            obj->modeState.effect.abParams[0] = 0;
            obj->modeState.effect.abParams[1] = 0;
            obj->modeState.effect.abParams[2] = 0;
            obj->modeState.effect.abParams[3] = 0;
            break;
        case 0x4A:  // SetAffineScaleTween: sets affine scale and tweens to a second scale
            SetObjectAffineTransform(obj, (s8)args[1] * ((args[2] << 16) + (args[3] << 8)), (s8)args[4] * ((args[5] << 16) + (args[6] << 8)), 0, 3);
            StartObjectAffineScaleTween(obj, (s8)args[7] * ((args[8] << 16) + (args[9] << 8)), (s8)args[10] * ((args[11] << 16) + (args[12] << 8)), args[13]);
            break;
        case 0x4B:  // SetAffineRotation1: mode 1
            SetObjectAffineTransform(obj, 0x10000, 0x10000, args[1] * -0x7FF, 1);
            break;
        case 0x4C:  // SetAffineRotation3: mode 3
            SetObjectAffineTransform(obj, 0x10000, 0x10000, args[1] * -0x7FF, 3);
            break;
        case 0x4D:  // SetAffineScaleRotation1: scales and rotates (mode 1)
            SetObjectAffineTransform(obj, (args[2] << 16) + (args[3] << 8), (args[4] << 16) + (args[5] << 8), args[1] * -0x7FF, 1);
            break;
        case 0x4E:  // SetAffineScaleRotation3: scales and rotates (mode 3)
            SetObjectAffineTransform(obj, (args[2] << 16) + (args[3] << 8), (args[4] << 16) + (args[5] << 8), args[1] * -0x7FF, 3);
            break;
        case 0x4F:  // ReleaseAffineSlot: releases the affine slot
            if (obj->oam.affineMode != 0)
                ReleaseObjectAffineSlot(obj);
            break;
        case 0x50:  // ClearAnimFlag: clears the animation flag
            obj->dwFlags &= ~ObjectFlagHasAnimation;
            break;
        case 0x51:  // SetAnimFlag: sets the animation flag
            obj->dwFlags |= ObjectFlagHasAnimation;
            break;
        case 0x52:  // HideObject: hides the object
            obj->dwFlags &= ~ObjectFlagVisible;
            break;
        case 0x53:  // ShowObject: shows the object
            obj->dwFlags |= ObjectFlagVisible;
            break;
        case 0x54:  // SetOamPriority: sets this object's OAM priority
            obj->oam.priority = args[1];
            break;
        case 0x55:  // SetTargetOamPriority: sets the target's OAM priority
            targetFighter->pObject->oam.priority = args[1];
            break;
        case 0x56:  // SetEnemiesOamPriority: sets the OAM priority of every enemy's object
            {
                u32 j;

                for (j = 0; j < g_pFightState->bFighterCount; j++)
                {
                    if (g_pFightState->pFighters[j].bFighterType == Enemy && g_pFightState->pFighters[j].pObject != NULL)
                        g_pFightState->pFighters[j].pObject->oam.priority = args[1];
                }
            }
            break;
        case 0x57:  // SetAlliesOamPriority: sets the OAM priority of every ally's object
            {
                u32 j;

                for (j = 0; j < g_pFightState->bFighterCount; j++)
                {
                    if (g_pFightState->pFighters[j].bFighterType != Enemy && g_pFightState->pFighters[j].pObject != NULL)
                        g_pFightState->pFighters[j].pObject->oam.priority = args[1];
                }
            }
            break;
        case 0x58:  // IncrementActionVariant: increments the action variant
            obj->wActionVariant++;
            break;
        case 0x59:  // SnapToRandomAroundSlot: snaps to a random offset around the slot position
            {
                s16 py;

                x = (s16)(Mt19937RandSigned(args[1]) + g_awBattleSlotPosX_candidate[g_effectStaging.bScriptParam]);
                py = Mt19937RandSigned(args[2]) + g_abBattleSlotPosY_candidate[args[3]];
                SnapObjectPosition(obj, x << 16, py << 16);
            }
            break;
        case 0x5A:  // SnapToRandomAroundSpawn: snaps to a random offset around the spawn position
            {
                s16 py;

                pos = ComputeEffectSpawnPosition();
                x = Mt19937RandSigned(args[1]) + pos.x;
                py = pos.y + Mt19937RandSigned(args[2]);
                SnapObjectPosition(obj, x << 16, py << 16);
            }
            break;
        case 0x5B:  // JitterPosition
            x = Mt19937RandSigned(args[1]);
            y = Mt19937RandSigned(args[2]);
            SnapObjectPosition(obj, obj->nX + (x << 16), obj->nY + (y << 16));
            break;
        case 0x5C:  // EnableSemiTransparency: enables semi-transparency and resets the fade timer
            obj->oam.objMode = 1;
            g_effectStaging.wTimer_candidate = 0;
            g_effectStaging.wTimerMax_candidate = 0x1F;
            SetAlphaBlendCoefficients(0x10, 0);
            break;
        case 0x5E:  // StartAlphaFade: sets behavior flag 4 (alpha fade) and local B
            obj->modeState.effect.bBehaviorFlags |= 4;
            obj->modeState.effect.abLocal[1] = args[1];
            break;
        case 0x5F:  // SetAlphaBlend: sets alpha blend coefficients
            SetAlphaBlendCoefficients(args[1], args[2]);
            break;
        case 0x61:  // Goto
            sub_0801B710(obj, args[1]);
            break;
        case 0x62:  // Goto_2: jumps to a label
            sub_0801B710(obj, args[1]);
            break;
        case 0x63:  // GotoLocalIndexedLabel
            sub_0801B710(obj, args[obj->modeState.effect.abLocal[args[1]] + 2]);
            break;
        case 0x64:  // FreeTileAllocation: frees the tile allocation
            sub_080454F4(obj->wVramTileAllocId, obj->wVramTileRow, obj->oam.bpp8);
            obj->wVramTileAllocId = 0xFFFF;
            obj->wVramTileRow = 0;
            break;
        case 0x65:  // StartDelayedChain: sets behavior flag 8 (delayed chain)
            obj->modeState.effect.bParam6C = args[1];
            obj->modeState.effect.bBehaviorFlags |= 8;
            obj->modeState.effect.abParams[0] = args[2];
            obj->modeState.effect.abParams[1] = args[3];
            obj->modeState.effect.bParam6D = 0;
            break;
        case 0x67:  // SetLocalRandomRange: sets a local to a random value in a range
            obj->modeState.effect.abLocal[args[1]] = Mt19937RandRange(args[2], args[3] - 1);
            break;
        case 0x68:  // SetDepthBiasZero: depth bias = 0
            obj->bDepthSortBias = 0;
            break;
        case 0x69:  // SetDepthBiasMax: depth bias = 0xFF
            obj->bDepthSortBias = 0xFF;
            break;
        case 0x6A:  // SetDepthBias: depth bias = operand
            obj->bDepthSortBias = args[1];
            break;
        case 0x6B:  // SetDepthBiasInverseLocalA: depth bias = 25 - local A
            obj->bDepthSortBias = 25 - obj->modeState.effect.abLocal[0];
            break;
        case 0x6C:  // SetDepthBiasLocalA: depth bias = local A
            obj->bDepthSortBias = obj->modeState.effect.abLocal[0];
            break;
        case 0x6F:  // ScrollBgUp: scrolls a BG up 2 pixels and shifts its priority
            g_aBgScrollState[args[1]].nScrollY_candidate -= 0x20000;
            g_aBgScrollState[args[1]].dwFlags |= 0x8000;
            sub_0802D640(g_abBgPriority[4] - 3);
            break;
        case 0x70:  // ScrollBgDown: scrolls a BG down 2 pixels and shifts its priority
            g_aBgScrollState[args[1]].nScrollY_candidate += 0x20000;
            g_aBgScrollState[args[1]].dwFlags |= 0x8000;
            sub_0802D640(g_abBgPriority[4] + 3);
            break;
        case 0x71:  // SetTargetVelocityScaled: sets the target's velocity (scaled by 1/16)
            {
                Object *fighterObj;

                fighterObj = targetFighter->pObject;
                SetObjectVelocity(fighterObj, (s8)args[1] << 12, (s8)args[2] << 12);
            }
            break;
        case 0x72:  // SetTargetVelocity: sets the target's velocity
            SetObjectVelocity(targetFighter->pObject, (s8)args[1] << 16, (s8)args[2] << 16);
            break;
        case 0x73:  // SetCasterVelocityProduct: sets the caster's velocity from operand products
            {
                Object *fighterObj;

                fighterObj = casterFighter->pObject;
                SetObjectVelocity(fighterObj, ((s8)args[1] * (s8)args[2]) << 12, ((s8)args[3] * (s8)args[4]) << 12);
            }
            break;
        case 0x74:  // NudgeCaster: nudges the caster's position
            {
                Object *fighterObj;

                fighterObj = casterFighter->pObject;
                SnapObjectPosition(fighterObj, fighterObj->nX + (args[1] << 16), fighterObj->nY + (args[2] << 16));
            }
            break;
        case 0x75:  // NudgeTarget: nudges the target's position
            {
                Object *fighterObj;

                fighterObj = targetFighter->pObject;
                SnapObjectPosition(fighterObj, fighterObj->nX + (args[1] << 16), fighterObj->nY + (args[2] << 16));
            }
            break;
        case 0x76:  // SetCasterPosition: sets the caster's position
            {
                Object *fighterObj;

                fighterObj = casterFighter->pObject;
                SnapObjectPosition(fighterObj, args[1] << 16, args[2] << 16);
            }
            break;
        case 0x77:  // SetTargetPosition: sets the target's position
            {
                Object *fighterObj;

                fighterObj = targetFighter->pObject;
                SnapObjectPosition(fighterObj, args[1] << 16, args[2] << 16);
            }
            break;
        case 0x7A:  // MoveFighterTo
            {
                Object *fighterObj;

                x = args[1];
                y = args[2];
                fighterObj = targetFighter->pObject;
                StartObjectMove(fighterObj, x << 16, y << 16, args[3]);
            }
            break;
        case 0x7B:  // MoveFighterToSlotPosition
            x = g_awBattleSlotPosX_candidate[g_effectStaging.bScriptParam];
            y = g_abBattleSlotPosY_candidate[g_effectStaging.bScriptParam];
            StartObjectMove(targetFighter->pObject, x << 16, y << 16, args[1]);
            break;
        case 0x78:  // SnapTargetToSlot: snaps the target to its slot position
            x = g_awBattleSlotPosX_candidate[g_effectStaging.bScriptParam];
            y = g_abBattleSlotPosY_candidate[g_effectStaging.bScriptParam];
            SnapObjectPosition(targetFighter->pObject, x << 16, y << 16);
            break;
        case 0x79:  // SnapCasterToSpawn: snaps the caster to the spawn position
            pos = ComputeEffectSpawnPosition();
            SnapObjectPosition(casterFighter->pObject, pos.x << 16, pos.y << 16);
            break;
        case 0x7C:  // MoveCasterTo: moves the caster to a computed position
            if (args[4] == 0)
            {
                x = g_awBattleSlotPosX_candidate[g_effectStaging.bScriptParam] + (s8)args[1];
                y = g_abBattleSlotPosY_candidate[g_effectStaging.bScriptParam] + (s8)args[2];
            }
            else
            {
                pos = ComputeEffectSpawnPosition();
                x = (s8)args[1] + pos.x;
                y = (s8)args[2] + pos.y;
            }
            if (args[5] != 0)
            {
                sub_08001AA8(targetFighter->pObject, args[5] - 1, &offset);
                x += offset.x;
                y += offset.y;
            }
            StartObjectMove(casterFighter->pObject, x << 16, y << 16, args[3]);
            break;
        case 0x7D:  // WaitForCasterField86: waits on the caster's field 0x86 (returns)
            obj->pfnTick = WaitForCasterField86Tick_candidate;
            return;
        case 0x7E:  // SetCasterAnim: sets the caster's animation
            SetObjectAnimData(casterFighter->pObject, &g_aPlayerGfxRows_candidate[casterFighter->pObject->wObjectType], g_aEffectAnimData_candidate[args[1]], args[2]);
            break;
        case 0x7F:  // LoadBgEffect: loads a BG effect record
            {
                const void *pControls;

                sub_0801B4BC(args[1], g_aEffectBgRecords_candidate[args[2]].pGfx, g_aEffectBgRecords_candidate[args[2]].wUnk0C, args[3], g_pFightState->pad_0C);
                sub_08007AF0(args[1], g_aEffectBgRecords_candidate[args[2]].wUnk04 << 16, g_aEffectBgRecords_candidate[args[2]].wUnk06 << 16);
                g_effectStaging.bBgEffectId_candidate = args[2];
                pControls = g_aEffectBgRecords_candidate[args[2]].pControls;
                if (pControls != NULL)
                {
                    switch (args[1])
                    {
                    case 1:
                        sub_0800A598(pControls, &g_adwEffectBgControlOverride_candidate[1], 8);
                        break;
                    case 0:
                        sub_0800A598(pControls, &g_adwEffectBgControlOverride_candidate[2], 8);
                        break;
                    case 2:
                        sub_0800A598(pControls, &g_adwEffectBgControlOverride_candidate[0], 8);
                        break;
                    case 3:
                        sub_0800A598(pControls, &g_adwEffectBgControlOverride_candidate[3], 8);
                        break;
                    }
                }
            }
            break;
        case 0x80:  // QueueScanlineEffect: queues a scanline-effect table
            QueueScanlineEffectTable(g_apEffectScanlineTables_candidate[args[1]], g_abEffectScanlineTableSizes_candidate[args[1]]);
            break;
        case 0x81:  // SetBgEffectId: stores the BG effect id
            g_effectStaging.bBgEffectId_candidate = args[1];
            break;
        case 0x82:  // TeleportTo
            SnapObjectPosition(obj, args[1] << 16, args[2] << 16);
            break;
        case 0x83:  // KillTarget: faints the target and grants its XP and gold
            {
                targetFighter->wHp = 0;
                targetFighter->nFaintedFlag = 0xFFFF;
                targetFighter->pObject->bActionState = 1;
                targetFighter->pObject->dwStateTimer = 3;
                g_pFightState->dwDefeatCheckPending_candidate = 1;
                n = 0;
                // The slot index is never advanced: a non-empty first slot
                // spins here until it is cleared.
                if (g_anFaintedRosterIndices[0] != -1)
                {
                    do
                    {
                        if (n > 3)
                            break;
                    } while (g_anFaintedRosterIndices[0] != -1);
                }
                g_anFaintedRosterIndices[n] = targetFighter->bRosterIndex;
                g_nBattleXpReward += sub_080189C8(targetFighter->bRosterIndex);
                g_nBattleGoldReward += sub_08018AB8(targetFighter->bRosterIndex);
            }
            break;
        case 0x84:  // RampBlendUp: ramps BLDY from 0 to 16 over frames
            {
                REG_BLDCNT = 0xFF;
                for (n = 0; n <= 0x10; n++)
                {
                    REG_BLDY = n;
                    WaitForVBlankIntr();
                    TickParticleEmitters();
                    TickBgLayers_candidate();
                    TickPaletteAnimations_candidate();
                    TickBgTileAnimations_candidate();
                }
            }
            break;
        case 0x85:  // RampBlendDown: ramps BLDY from 16 to 0 over frames
            {
                REG_BLDCNT = 0xFF;
                for (n = 0x10; (s32)n >= 0; n--)
                {
                    REG_BLDY = n;
                    WaitForVBlankIntr();
                    TickParticleEmitters();
                    TickBgLayers_candidate();
                    TickPaletteAnimations_candidate();
                    TickBgTileAnimations_candidate();
                }
            }
            break;
        case 0x86:  // GotoIfLocalAGreater
            if (obj->modeState.effect.abLocal[0] > args[1])
                sub_0801B710(obj, args[2]);
            break;
        case 0x87:  // GotoIfLocalALess
            if (obj->modeState.effect.abLocal[0] < args[1])
                sub_0801B710(obj, args[2]);
            break;
        case 0x88:  // GotoIfLocalAInRange
            if (obj->modeState.effect.abLocal[0] > args[1] && obj->modeState.effect.abLocal[0] < args[2])
                sub_0801B710(obj, args[3]);
            break;
        case 0x89:  // GotoIfLocalAOutOfRange
            if (obj->modeState.effect.abLocal[0] <= args[1] || obj->modeState.effect.abLocal[0] >= args[2])
                sub_0801B710(obj, args[3]);
            break;
        case 0x8A:  // SetBgPaletteColors: sets palette colors of a BG record
            sub_0800D244((u8 *)g_aEffectBgRecords_candidate[args[1]].pGfx + ((args[2] << 4) + 2), args[3] << 4, args[4] << 4);
            break;
        case 0x8B:  // SetBgPaletteColorsAdjust: sets palette colors and adjusts a palette entry
            sub_0800D244((u8 *)g_aEffectBgRecords_candidate[args[1]].pGfx + ((args[2] << 4) + 2), args[3] << 4, args[4] << 4);
            sub_0800D4A4((args[3] << 4) + 1, args[5], 1, 1);
            break;
        case 0x8C:  // SetBgPriority
            SetBgPriority(args[1], args[2]);
            if (args[1] == 1)
                g_effectStaging.bStateB_candidate = args[2];
            if (args[1] == 0)
                g_effectStaging.bStateA_candidate = args[2];
            break;
        case 0x8D:  // SetEffectTimers: sets the effect timer and its maximum
            g_effectStaging.wTimer_candidate = args[1] | args[2] | args[3] | args[4] | args[5];
            g_effectStaging.wTimerMax_candidate = args[6] | args[7] | args[8] | args[9] | args[10];
            break;
        case 0x8E:  // StartFadeCounter: sets behavior flag 0x80 (fade) and its counters
            obj->modeState.effect.bBehaviorFlags |= 0x80;
            obj->modeState.effect.abLocal[1] = 0x10;
            obj->modeState.effect.bParam6C = args[1];
            obj->modeState.effect.bParam6D = args[1];
            obj->modeState.effect.abParams[4] = args[2];
            break;
        case 0x8F:  // SetWindowLayers: sets a window's layer masks
            SetScreenWindowLayers_candidate(args[1], args[2] | args[3] | args[4] | args[5] | args[6], args[7] | args[8] | args[9] | args[10] | args[11]);
            break;
        case 0x90:  // SetWindowRect: sets a window rectangle and clears behavior flag 0x10
            SetScreenWindowRect_candidate(args[1], args[2] << 16, args[3] << 16, args[4] << 16, args[5] << 16);
            obj->modeState.effect.bBehaviorFlags &= ~0x10;
            break;
        case 0x91:  // SetBehaviorFlag10: sets behavior flag 0x10
            obj->modeState.effect.bBehaviorFlags |= 0x10;
            break;
        case 0x92:  // HideWindow: hides a window
            SetScreenWindowLayers_candidate(args[1], 0, 0);
            HideScreenWindow_candidate(args[1]);
            break;
        case 0x93:  // ResetBgState: resets a BG's window, scroll and state
            sub_080075A8(args[1], 0, 0, 0x20, 0xF);
            sub_08007D14(args[1], 0, 0);
            sub_08007AF0(args[1], 0, 0);
            if (args[1] == 1)
                sub_080065D4(1, sub_08012A84(), 0x180);
            break;
        case 0x94:  // opcode_94: sub_08001D90(1)
            sub_08001D90(1);
            break;
        case 0x95:  // opcode_95: sub_08001D90(0)
            sub_08001D90(0);
            break;
        case 0x96:  // FlipTargetFacing: flips the target's facing unless it is type 0x3A
            {
                Object *fighterObj;

                fighterObj = targetFighter->pObject;
                if (fighterObj->wObjectType != 0x3A && g_effectStaging.wContextValue != 0)
                    SetObjectFlippedX(fighterObj, !IsObjectFlippedX(fighterObj));
            }
            break;
        case 0x9B:  // SetDispcntBit15: turns DISPCNT bit 15 on and sets OAM mode 2
            REG_DISPCNT |= 0x8000;
            obj->oam.objMode = 2;
            break;
        case 0x9C:  // ClearDispcntBit15: turns DISPCNT bit 15 off
            REG_DISPCNT &= 0x7FFF;
        case 0x5D:  // DisableBlendMode: clears the OAM blend mode
            obj->oam.objMode = 0;
            break;
        case 0x97:  // StatusEffect
            switch (args[1])
            {
            case 0:
                g_effectStaging.pEmitter_candidate = sub_0801B204(obj, args[2], args[3]);
                g_effectStaging.pEmitter_candidate->bParalysisEffectFlag_candidate = 2;
                break;
            case 1:
                g_effectStaging.pEmitter_candidate = sub_0801B2EC(obj, args[2], args[3]);
                g_effectStaging.pEmitter_candidate->bParalysisEffectFlag_candidate = 2;
                break;
            case 2:
                g_pFightState->bBonusRewardFlags |= ExtraExpBonus;
                break;
            case 3:
                g_pFightState->bBonusRewardFlags |= GrantExtraXp;
                break;
            case 4:
                REG_WINOUT = 0x3F3D;
                break;
            case 5:
                if ((targetFighter->bStatusFlags & (PoisonImmune | Poisoned)) == 0)
                {
                    g_pFightState->bPendingStatusMessageVariant_candidate = 3;
#ifdef VERSION_JP
                    ShowBattleMessage(AttackResult, 0, g_pFightState->bPendingStatusMessageVariant_candidate);
#endif
                    SpawnParalysisEffect(targetFighter->pObject);
                    targetFighter->pObject->wActionVariant = 1;
                    targetFighter->bStatusFlags |= Poisoned;
                    if (g_GameModeStackContext.dwCurrentGameModeArg3 == 0xFF && g_GameModeStackContext.dwCurrentGameModeArg1 == 3)
                        targetFighter->bPoisonDamage = 0xF;
                    else
                        targetFighter->bPoisonDamage = args[2];
                }
                break;
            case 6:
                targetFighter->pObject->bDrawFlags |= ObjectDrawFlagPostActionFlash;
                targetFighter->bStatusFlags |= AttackWeakened;
                ShowBattleMessage(AttackWeakenedMessage, 0, 0);
                break;
            case 7:
                targetFighter->bStatusFlags |= PoisonImmune;
                break;
            case 8:
                targetFighter->pObject->bDrawFlags = ObjectDrawFlagBlink;
                targetFighter->bStatusFlags |= Hidden;
                ShowBattleMessage(HiddenFromView, 0, g_effectStaging.bTargetIndex);
                break;
            case 9:
                targetFighter->pObject->bDrawFlags = ObjectDrawFlagBlink;
                targetFighter->bStatusFlags |= Hidden;
                ShowBattleMessage(HiddenFromView, 1, g_effectStaging.bTargetIndex);
                break;
            case 10:
                if (TryApplyParalysis(targetFighter, targetFighter->bFighterType == Enemy, 0x19) != 0
                    && targetFighter->bFighterType != Enemy)
                    SpawnParalysisEffect(targetFighter->pObject);
                break;
            case 17:
                TryApplyParalysis(targetFighter, 1, 0x63);
                break;
            case 18:
                TryApplyParalysis(targetFighter, 1, 0x50);
                break;
            case 22:
                if (TryApplyParalysis(targetFighter, targetFighter->bFighterType == Enemy, args[2]) != 0)
                {
                    g_pFightState->bPendingStatusMessageVariant_candidate = 4;
                    if (targetFighter->bFighterType != Enemy)
                    {
                        SpawnParalysisEffect(targetFighter->pObject);
                        ShowBattleMessage(AttackResult, 0, 4);
                    }
                }
                break;
            case 23:
                if (Mt19937ChanceNoisy(args[3]) != 0 && TryApplyParalysis(targetFighter, 0, args[2]) != 0)
                {
                    g_pFightState->bPendingStatusMessageVariant_candidate = 4;
                    SpawnParalysisEffect(targetFighter->pObject);
                }
                break;
            case 11:
                targetFighter->bStatusFlags |= DefenseBoost;
                break;
            case 12:
                sub_08037104(targetFighter->bRosterIndex);
                g_bDefeatWarpParam = targetFighter->bRosterIndex;
                break;
            case 13:
                {
                    for (n = 0; n < g_pFightState->bFighterCount; n++)
                    {
                        if (g_pFightState->pFighters[n].bFighterType == Enemy)
                            g_pFightState->pFighters[n].pObject->bDrawFlags |= ObjectDrawFlagPostActionFlash;
                    }
                }
                break;
            case 14:
                {
                    for (n = 0; n < g_pFightState->bFighterCount; n++)
                    {
                        if (g_pFightState->pFighters[n].bFighterType == Enemy && (g_pFightState->pFighters[n].bStatusFlags & AttackWeakened) == 0)
                            g_pFightState->pFighters[n].pObject->bDrawFlags &= ~ObjectDrawFlagPostActionFlash;
                    }
                }
                break;
            case 15:
                ClearPoisonedFighter_candidate(g_effectStaging.bTargetIndex);
                break;
            case 16:
                if (args[2] == 0)
                {
                    SetObjectAnimData(targetFighter->pObject, &g_aFighterAnimTable[targetFighter->pObject->wObjectType].aRecords[4], (void *)g_abFighterIdleAnimData_candidate, 0);
                    SetObjectAnimFrame(targetFighter->pObject, 0);
                }
                else
                {
                    SetPlayerObjectAnim(targetFighter->pObject, 0);
                    InitCharacterSpells_candidate(targetFighter->bFighterType, &targetFighter->wHp);
                }
                break;
            case 19:
                targetFighter->bStatusFlags |= SpellPowerBoost;
                break;
            case 20:
                ClearPoisonedFighter_candidate(g_effectStaging.bTargetIndex);
                ClearParalyzedFighter_candidate(g_effectStaging.bTargetIndex);
                break;
            case 21:
                g_effectStaging.pEmitter_candidate = sub_0801B348(obj, args[2], args[3]);
                g_effectStaging.pEmitter_candidate->bParalysisEffectFlag_candidate = 2;
                break;
            case 24:
                if (args[2] == 0)
                {
                    SetObjectAffineTransform(targetFighter->pObject, 0x10000, 0x10000, 0, 3);
                    StartObjectAffineScaleTween(targetFighter->pObject, 0x18000, 0x4000, 4);
                }
                else if (args[2] == 1)
                    StartObjectAffineScaleTween(targetFighter->pObject, 0x10000, 0x10000, 10);
                else if (args[2] == 2)
                    ReleaseObjectAffineSlot(targetFighter->pObject);
                break;
            case 25:
                {
                    for (n = 0; n < g_pFightState->bFighterCount; n++)
                    {
                        if (g_pFightState->pFighters[n].bFighterType != Enemy && g_pFightState->pFighters[n].wHp != 0)
                        {
                            g_pFightState->pFighters[n].wHp = g_pFightState->pFighters[n].wHp_max;
                            g_aPartyMasterStats[g_pFightState->pFighters[n].bFighterType].wHp = g_pFightState->pFighters[n].wHp_max;
                        }
                    }
                }
                break;
            case 26:
                targetFighter->wMp = targetFighter->wMp_max;
                g_aPartyMasterStats[targetFighter->bFighterType].wMp = targetFighter->wMp_max;
                break;
            case 27:
                g_pFightState->bBonusRewardFlags |= ForceItemDrop;
                break;
            case 28:
                sub_0800E890(g_effectStaging.bTargetIndex);
                break;
            }
            break;
        case 0x98:  // opcode_98: sub_08012A00 call
            sub_08012A00();
            break;
        case 0x99:  // SetLocalAToPartySize: sets local A to the party size
            if (g_GameModeStackContext.dwCurrentGameModeArg3 == 0xFF && g_GameModeStackContext.dwCurrentGameModeArg1 == 3)
                obj->modeState.effect.abLocal[0] = 3;
            else
                obj->modeState.effect.abLocal[0] = GetPartySize();
            break;
        case 0x9A:  // opcode_9A: BG helper call with x
            sub_08007D14(args[1], args[2] << 16, 0);
            break;
        case 0x9D:  // SelectFirstAlly: selects the first ally as target
            {
                g_effectStaging.bTargetIndex = 0xFF;
                for (n = 0; n < g_pFightState->bFighterCount; n++)
                {
                    if (g_pFightState->pFighters[n].bFighterType != Enemy && g_effectStaging.bTargetIndex == 0xFF)
                        g_effectStaging.bTargetIndex = n;
                }
                targetFighter = g_pFightState->pFighters + g_effectStaging.bTargetIndex;
                g_effectStaging.bScriptParam = targetFighter->bSlotParam;
            }
            break;
        case 0x9E:  // SelectNextAlly: selects the next ally as target
            {
                obj->modeState.effect.abLocal[1] = 0;
                n = g_effectStaging.bTargetIndex + 1;
                g_effectStaging.bTargetIndex = 0xFF;
                for (; n < g_pFightState->bFighterCount; n++)
                {
                    if (g_pFightState->pFighters[n].bFighterType != Enemy && g_effectStaging.bTargetIndex == 0xFF)
                        g_effectStaging.bTargetIndex = n;
                }
                if (g_effectStaging.bTargetIndex == 0xFF)
                {
                    obj->modeState.effect.abLocal[1] = 1;
                    break;
                }
                targetFighter = g_pFightState->pFighters + g_effectStaging.bTargetIndex;
                g_effectStaging.bScriptParam = targetFighter->bSlotParam;
            }
            break;
        case 0x9F:  // SelectFirstLiveEnemy: selects the first live enemy as target
            {
                g_effectStaging.bTargetIndex = 0xFF;
                for (n = 0; n < g_pFightState->bFighterCount; n++)
                {
                    if (g_pFightState->pFighters[n].bFighterType == Enemy && g_pFightState->pFighters[n].wHp != 0
                        && (u16)g_pFightState->pFighters[n].nFaintedFlag != 0xFFFF && g_effectStaging.bTargetIndex == 0xFF)
                        g_effectStaging.bTargetIndex = n;
                }
                targetFighter = g_pFightState->pFighters + g_effectStaging.bTargetIndex;
                g_effectStaging.bScriptParam = targetFighter->bSlotParam + 3;
            }
            break;
        case 0xA0:  // SelectNextLiveEnemy: selects the next live enemy as target
            {
                obj->modeState.effect.abLocal[1] = 0;
                n = g_effectStaging.bTargetIndex + 1;
                g_effectStaging.bTargetIndex = 0xFF;
                for (; n < g_pFightState->bFighterCount; n++)
                {
                    if (g_pFightState->pFighters[n].bFighterType == Enemy && g_pFightState->pFighters[n].wHp != 0
                        && (u16)g_pFightState->pFighters[n].nFaintedFlag != 0xFFFF && g_effectStaging.bTargetIndex == 0xFF)
                        g_effectStaging.bTargetIndex = n;
                }
                if (g_effectStaging.bTargetIndex == 0xFF)
                {
                    obj->modeState.effect.abLocal[1] = 1;
                    break;
                }
                targetFighter = g_pFightState->pFighters + g_effectStaging.bTargetIndex;
                g_effectStaging.bScriptParam = targetFighter->bSlotParam + 3;
            }
            break;
        case 0xA2:  // SetLocalRandom
            obj->modeState.effect.abLocal[args[1]] = Mt19937RandMax(args[2]);
            break;
        case 0xA3:  // opcode_A3: sub_080065D4 call
            sub_080065D4(1, sub_08012A84(), 0x180);
            break;
        case 0xA4:  // PlaySoundOrDefault: PlaySound, or sound 0x4B when the context value is 0
            if (g_effectStaging.wContextValue == 0)
            {
                PlaySoundById(0x4B);
                break;
            }
        case 0x06:  // PlaySound
            PlaySoundById(args[1]);
            break;
        case 0xA5:  // DarkenScreenPalette
            DarkenScreenPalette();
            break;
        case 0xA6:  // RestoreScreenPalette
            RestoreScreenPalette();
            break;
        case 0xA7:  // PlaySoundEffect: plays a sound effect
            PlaySoundEffect_candidate(args[1]);
            break;
        case 0x14:  // opcode_14
        case 0x15:  // opcode_15
        case 0x3A:  // opcode_3A
        case 0x3F:  // opcode_3F
        case 0x40:  // opcode_40
        case 0x60:  // Label
        case 0x66:  // opcode_66
        case 0x6D:  // opcode_6D
        case 0x6E:  // opcode_6E
        case 0xA1:  // opcode_A1
        default:
            break;
        }
    } while (!done);
}
