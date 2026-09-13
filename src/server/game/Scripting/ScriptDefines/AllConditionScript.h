/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information.
 */

#ifndef SCRIPT_OBJECT_ALL_CONDITION_SCRIPT_H_
#define SCRIPT_OBJECT_ALL_CONDITION_SCRIPT_H_

#include "ScriptObject.h"
#include <vector>

// @tswow-begin: generic mutable condition evaluation interface
enum AllConditionHook
{
    ALLCONDITIONHOOK_ON_EVALUATION,
    ALLCONDITIONHOOK_END
};

class AllConditionScript : public ScriptObject
{
protected:
    AllConditionScript(char const* name, std::vector<uint16> enabledHooks = {});

public:
    [[nodiscard]] bool IsDatabaseBound() const override { return false; }
    virtual void OnConditionEvaluation(Condition* /*condition*/, ConditionSourceInfo& /*sourceInfo*/,
        bool& /*result*/) { }
};
// @tswow-end

#endif
