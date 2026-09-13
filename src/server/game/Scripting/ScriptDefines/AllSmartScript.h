/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information.
 */

#ifndef SCRIPT_OBJECT_ALL_SMART_SCRIPT_H_
#define SCRIPT_OBJECT_ALL_SMART_SCRIPT_H_

#include "ScriptObject.h"
#include <vector>

// @tswow-begin: generic SmartAI action lifecycle interface
class SmartScript;
struct SmartScriptHolder;

enum AllSmartHook
{
    ALLSMARTHOOK_ON_ACTION,
    ALLSMARTHOOK_END
};

enum class SmartActionPhase : uint8
{
    Early,
    Late
};

struct SmartActionContext
{
    SmartScriptHolder* holder;
    SmartScript* script;
    Unit* unit;
    uint32 value0;
    uint32 value1;
    bool boolValue;
    SpellInfo const* spell;
    GameObject* gameObject;
    std::vector<WorldObject*>* targets;
};

class AllSmartScript : public ScriptObject
{
protected:
    AllSmartScript(char const* name, std::vector<uint16> enabledHooks = {});

public:
    [[nodiscard]] bool IsDatabaseBound() const override { return false; }
    virtual void OnSmartAction(uint32 /*actionType*/, SmartActionPhase /*phase*/,
        SmartActionContext& /*context*/, bool& /*cancelAction*/, bool& /*cancelLink*/) { }
};
// @tswow-end

#endif
