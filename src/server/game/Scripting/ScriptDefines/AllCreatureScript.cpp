/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "AllCreatureScript.h"
#include "ScriptMgr.h"
#include "ScriptMgrMacros.h"

// @tswow-begin: cancellable creature world-add hook
bool ScriptMgr::CanCreatureAddWorld(Creature* creature)
{
    ASSERT(creature);

    bool canAdd = true;
    ExecuteScript<AllCreatureScript>([&](AllCreatureScript* script)
    {
        if (!script->CanCreatureAddWorld(creature))
            canAdd = false;
    });
    return canAdd;
}
// @tswow-end

void ScriptMgr::OnCreatureAddWorld(Creature* creature)
{
    ASSERT(creature);

    ExecuteScript<AllCreatureScript>([&](AllCreatureScript* script)
    {
        script->OnCreatureAddWorld(creature);
    });
}

void ScriptMgr::OnCreatureRemoveWorld(Creature* creature)
{
    ASSERT(creature);

    ExecuteScript<AllCreatureScript>([&](AllCreatureScript* script)
    {
        script->OnCreatureRemoveWorld(creature);
    });
}

void ScriptMgr::OnCreatureSaveToDB(Creature* creature)
{
    ASSERT(creature);

    ExecuteScript<AllCreatureScript>([&](AllCreatureScript* script)
    {
        script->OnCreatureSaveToDB(creature);
    });
}

void ScriptMgr::OnBeforeCreatureSelectLevel(CreatureTemplate const* cinfo, Creature* creature, uint8& level)
{
    ExecuteScript<AllCreatureScript>([&](AllCreatureScript* script)
    {
        script->OnBeforeCreatureSelectLevel(cinfo, creature, level);
    });
}

void ScriptMgr::OnCreatureSelectLevel(CreatureTemplate const* cinfo, Creature* creature)
{
    ExecuteScript<AllCreatureScript>([&](AllCreatureScript* script)
    {
        script->OnCreatureSelectLevel(cinfo, creature);
    });
}

// @tswow-begin: generic mutable creature stat calculations
void ScriptMgr::OnCreatureFloatStatCalculation(Creature* creature, CreatureStatCalculation type, float& value,
    bool isGuardian, float argument)
{
    ExecuteScript<AllCreatureScript>([&](AllCreatureScript* script)
    {
        script->OnCreatureFloatStatCalculation(creature, type, value, isGuardian, argument);
    });
}

void ScriptMgr::OnCreatureUIntStatCalculation(Creature* creature, CreatureStatCalculation type, uint32& value,
    float modifier, uint32 base)
{
    ExecuteScript<AllCreatureScript>([&](AllCreatureScript* script)
    {
        script->OnCreatureUIntStatCalculation(creature, type, value, modifier, base);
    });
}

void ScriptMgr::OnCreatureBaseDamageCalculation(Creature* creature, float& minimum, float& maximum,
    float baseDamage)
{
    ExecuteScript<AllCreatureScript>([&](AllCreatureScript* script)
    {
        script->OnCreatureBaseDamageCalculation(creature, minimum, maximum, baseDamage);
    });
}

void ScriptMgr::OnCreatureBaseAttackPowerCalculation(Creature* creature, uint32& attackPower,
    uint32& rangedAttackPower)
{
    ExecuteScript<AllCreatureScript>([&](AllCreatureScript* script)
    {
        script->OnCreatureBaseAttackPowerCalculation(creature, attackPower, rangedAttackPower);
    });
}

void ScriptMgr::OnCreatureAttackPowerCalculation(Creature* creature, float& base, float& modifier,
    float& multiplier, bool isGuardian, bool ranged)
{
    ExecuteScript<AllCreatureScript>([&](AllCreatureScript* script)
    {
        script->OnCreatureAttackPowerCalculation(creature, base, modifier, multiplier, isGuardian, ranged);
    });
}

void ScriptMgr::OnCreatureDamageCalculation(Creature* creature, float& minimum, float& maximum,
    bool isGuardian, uint8 attackType)
{
    ExecuteScript<AllCreatureScript>([&](AllCreatureScript* script)
    {
        script->OnCreatureDamageCalculation(creature, minimum, maximum, isGuardian, attackType);
    });
}
// @tswow-end

// @tswow-begin: generic creature AI lifecycle dispatch
void ScriptMgr::OnCreatureLifecycle(Creature* creature, CreatureLifecycleEvent type, WorldObject* primary,
    WorldObject* secondary, uint32 value, uint32 secondaryValue, bool apply, SpellInfo const* spellInfo,
    Loot* loot, ItemTemplate const* itemTemplate, bool* mutableResult, uint32* mutableValue)
{
    ExecuteScript<AllCreatureScript>([&](AllCreatureScript* script)
    {
        script->OnCreatureLifecycle(creature, type, primary, secondary, value, secondaryValue, apply,
            spellInfo, loot, itemTemplate, mutableResult, mutableValue);
    });
}
// @tswow-end

//bool ScriptMgr::CanCreatureSendListInventory(Player* player, Creature* creature, uint32 vendorEntry)
//{
//    auto ret = IsValidBoolScript<AllCreatureScript>([&](AllCreatureScript* script)
//    {
//        return !script->CanCreatureSendListInventory(player, creature, vendorEntry);
//    });
//
//    if (ret && *ret)
//        return false;
//
//    return true;
//}

AllCreatureScript::AllCreatureScript(char const* name) :
    ScriptObject(name)
{
    ScriptRegistry<AllCreatureScript>::AddScript(this);
}

template class AC_GAME_API ScriptRegistry<AllCreatureScript>;
