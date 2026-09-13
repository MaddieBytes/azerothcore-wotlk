/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information.
 */

#include "AllSmartScript.h"
#include "ScriptMgr.h"
#include "ScriptMgrMacros.h"

// @tswow-begin: generic SmartAI action lifecycle dispatch
void ScriptMgr::OnSmartAction(uint32 actionType, SmartActionPhase phase, SmartActionContext& context,
    bool& cancelAction, bool& cancelLink)
{
    CALL_ENABLED_HOOKS(AllSmartScript, ALLSMARTHOOK_ON_ACTION,
        script->OnSmartAction(actionType, phase, context, cancelAction, cancelLink));
}

AllSmartScript::AllSmartScript(char const* name, std::vector<uint16> enabledHooks)
    : ScriptObject(name, ALLSMARTHOOK_END)
{
    if (enabledHooks.empty())
        for (uint16 i = 0; i < ALLSMARTHOOK_END; ++i)
            enabledHooks.emplace_back(i);

    ScriptRegistry<AllSmartScript>::AddScript(this, std::move(enabledHooks));
}

template class AC_GAME_API ScriptRegistry<AllSmartScript>;
// @tswow-end
