#include "types.h"
#include "combat_fx.h"
#include "combat_fx_script.h"

// Points the script PC at the Label opcode with this id.
void JumpToScriptLabel(Actor *actor, u8 label)
{
    const u8 *script;
    u16 *pc;
    u32 opcode;
    u8 effectId;

    effectId = actor->modeState.effect.bEffectId;
    script = g_apEffectScripts[effectId];
    pc = &actor->scriptState.wScriptPc;
    *pc = 1;
    opcode = script[0];
    for (;;)
    {
        if (opcode == BSOP_Label && script[*pc] == label)
        {
            (*pc)--;
            break;
        }
        *pc += g_abScriptOpcodeLengths[opcode];
        opcode = script[(*pc)++];
    }
}
