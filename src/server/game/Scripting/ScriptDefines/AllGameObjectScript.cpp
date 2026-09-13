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

#include "AllGameObjectScript.h"
#include "ScriptMgr.h"
#include "ScriptMgrMacros.h"

// @tswow-begin: cancellable game-object world-add hook
bool ScriptMgr::CanGameObjectAddWorld(GameObject* go)
{
    ASSERT(go);

    bool canAdd = true;
    ExecuteScript<AllGameObjectScript>([&](AllGameObjectScript* script)
    {
        if (!script->CanGameObjectAddWorld(go))
            canAdd = false;
    });
    return canAdd;
}
// @tswow-end

// @tswow-begin: generic game-object interaction and loot notifications
bool ScriptMgr::CanGameObjectUse(GameObject* go, Unit* user)
{
    ASSERT(go);
    ASSERT(user);

    bool canUse = true;
    ExecuteScript<AllGameObjectScript>([&](AllGameObjectScript* script)
    {
        if (!script->CanGameObjectUse(go, user))
            canUse = false;
    });
    return canUse;
}

void ScriptMgr::OnGameObjectDialogStatus(GameObject* go, Player* player)
{
    ExecuteScript<AllGameObjectScript>([&](AllGameObjectScript* script)
    {
        script->OnGameObjectDialogStatus(go, player);
    });
}

void ScriptMgr::OnGameObjectGenerateLoot(GameObject* go, Player* player)
{
    ExecuteScript<AllGameObjectScript>([&](AllGameObjectScript* script)
    {
        script->OnGameObjectGenerateLoot(go, player);
    });
}

void ScriptMgr::OnGameObjectGenerateFishLoot(GameObject* go, Player* player, Loot* loot, bool junk)
{
    ExecuteScript<AllGameObjectScript>([&](AllGameObjectScript* script)
    {
        script->OnGameObjectGenerateFishLoot(go, player, loot, junk);
    });
}
// @tswow-end

void ScriptMgr::OnGameObjectAddWorld(GameObject* go)
{
    ASSERT(go);

    ExecuteScript<AllGameObjectScript>([&](AllGameObjectScript* script)
    {
        script->OnGameObjectAddWorld(go);
    });
}

void ScriptMgr::OnGameObjectRemoveWorld(GameObject* go)
{
    ASSERT(go);

    ExecuteScript<AllGameObjectScript>([&](AllGameObjectScript* script)
    {
        script->OnGameObjectRemoveWorld(go);
    });
}

void ScriptMgr::OnGameObjectSaveToDB(GameObject* go)
{
    ASSERT(go);

    ExecuteScript<AllGameObjectScript>([&](AllGameObjectScript* script)
    {
        script->OnGameObjectSaveToDB(go);
    });
}

AllGameObjectScript::AllGameObjectScript(char const* name) :
    ScriptObject(name)
{
    ScriptRegistry<AllGameObjectScript>::AddScript(this);
}

template class AC_GAME_API ScriptRegistry<AllGameObjectScript>;
