/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information.
 */

#include "AllConditionScript.h"
#include "ScriptMgr.h"
#include "ScriptMgrMacros.h"

// @tswow-begin: global mutable condition evaluation dispatch
void ScriptMgr::OnConditionEvaluation(Condition* condition, ConditionSourceInfo& sourceInfo, bool& result)
{
    CALL_ENABLED_HOOKS(AllConditionScript, ALLCONDITIONHOOK_ON_EVALUATION,
        script->OnConditionEvaluation(condition, sourceInfo, result));
}

AllConditionScript::AllConditionScript(char const* name, std::vector<uint16> enabledHooks)
    : ScriptObject(name, ALLCONDITIONHOOK_END)
{
    if (enabledHooks.empty())
        for (uint16 i = 0; i < ALLCONDITIONHOOK_END; ++i)
            enabledHooks.emplace_back(i);

    ScriptRegistry<AllConditionScript>::AddScript(this, std::move(enabledHooks));
}

template class AC_GAME_API ScriptRegistry<AllConditionScript>;
// @tswow-end
