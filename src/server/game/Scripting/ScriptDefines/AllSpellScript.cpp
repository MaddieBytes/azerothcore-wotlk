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

#include "AllSpellScript.h"
#include "ScriptMgr.h"
#include "ScriptMgrMacros.h"

void ScriptMgr::OnCalcMaxDuration(Aura const* aura, int32& maxDuration)
{
    CALL_ENABLED_HOOKS(AllSpellScript, ALLSPELLHOOK_ON_CALC_MAX_DURATION, script->OnCalcMaxDuration(aura, maxDuration));
}

void ScriptMgr::OnSpellCheckCast(Spell* spell, bool strict, SpellCastResult& res)
{
    CALL_ENABLED_HOOKS(AllSpellScript, ALLSPELLHOOK_ON_SPELL_CHECK_CAST, script->OnSpellCheckCast(spell, strict, res));
}

bool ScriptMgr::CanPrepare(Spell* spell, SpellCastTargets const* targets, AuraEffect const* triggeredByAura)
{
    CALL_ENABLED_BOOLEAN_HOOKS(AllSpellScript, ALLSPELLHOOK_CAN_PREPARE, !script->CanPrepare(spell, targets, triggeredByAura));
}

bool ScriptMgr::CanScalingEverything(Spell* spell)
{
    CALL_ENABLED_BOOLEAN_HOOKS_WITH_DEFAULT_FALSE(AllSpellScript, ALLSPELLHOOK_CAN_SCALING_EVERYTHING, script->CanScalingEverything(spell));
}

bool ScriptMgr::CanSelectSpecTalent(Spell* spell)
{
    CALL_ENABLED_BOOLEAN_HOOKS(AllSpellScript, ALLSPELLHOOK_CAN_SELECT_SPEC_TALENT, !script->CanSelectSpecTalent(spell));
}

void ScriptMgr::OnScaleAuraUnitAdd(Spell* spell, Unit* target, uint32 effectMask, bool checkIfValid, bool implicit, uint8 auraScaleMask, TargetInfo& targetInfo)
{
    CALL_ENABLED_HOOKS(AllSpellScript, ALLSPELLHOOK_ON_SCALE_AURA_UNIT_ADD, script->OnScaleAuraUnitAdd(spell, target, effectMask, checkIfValid, implicit, auraScaleMask, targetInfo));
}

void ScriptMgr::OnRemoveAuraScaleTargets(Spell* spell, TargetInfo& targetInfo, uint8 auraScaleMask, bool& needErase)
{
    CALL_ENABLED_HOOKS(AllSpellScript, ALLSPELLHOOK_ON_REMOVE_AURA_SCALE_TARGETS, script->OnRemoveAuraScaleTargets(spell, targetInfo, auraScaleMask, needErase));
}

void ScriptMgr::OnBeforeAuraRankForLevel(SpellInfo const* spellInfo, SpellInfo const* latestSpellInfo, uint8 level)
{
    CALL_ENABLED_HOOKS(AllSpellScript, ALLSPELLHOOK_ON_BEFORE_AURA_RANK_FOR_LEVEL, script->OnBeforeAuraRankForLevel(spellInfo, latestSpellInfo, level));
}

void ScriptMgr::OnIsAuraExclusiveBySpecificWith(SpellInfo const* spellInfo, SpellInfo const* otherSpellInfo, bool& isExclusive)
{
    CALL_ENABLED_HOOKS(AllSpellScript, ALLSPELLHOOK_ON_IS_AURA_EXCLUSIVE_BY_SPECIFIC_WITH, script->OnIsAuraExclusiveBySpecificWith(spellInfo, otherSpellInfo, isExclusive));
}

void ScriptMgr::OnDummyEffect(WorldObject* caster, uint32 spellID, SpellEffIndex effIndex, GameObject* gameObjTarget)
{
    CALL_ENABLED_HOOKS(AllSpellScript, ALLSPELLHOOK_ON_DUMMY_EFFECT_GAMEOBJECT, script->OnDummyEffect(caster, spellID, effIndex, gameObjTarget));
}

void ScriptMgr::OnDummyEffect(WorldObject* caster, uint32 spellID, SpellEffIndex effIndex, Creature* creatureTarget)
{
    CALL_ENABLED_HOOKS(AllSpellScript, ALLSPELLHOOK_ON_DUMMY_EFFECT_CREATURE, script->OnDummyEffect(caster, spellID, effIndex, creatureTarget));
}

void ScriptMgr::OnDummyEffect(WorldObject* caster, uint32 spellID, SpellEffIndex effIndex, Item* itemTarget)
{
    CALL_ENABLED_HOOKS(AllSpellScript, ALLSPELLHOOK_ON_DUMMY_EFFECT_ITEM, script->OnDummyEffect(caster, spellID, effIndex, itemTarget));
}

void ScriptMgr::OnSpellCastCancel(Spell* spell, Unit* caster, SpellInfo const* spellInfo, bool bySelf)
{
    CALL_ENABLED_HOOKS(AllSpellScript, ALLSPELLHOOK_ON_CAST_CANCEL, script->OnSpellCastCancel(spell, caster, spellInfo, bySelf));
}

void ScriptMgr::OnSpellCast(Spell* spell, Unit* caster, SpellInfo const* spellInfo, bool skipCheck)
{
    CALL_ENABLED_HOOKS(AllSpellScript, ALLSPELLHOOK_ON_CAST, script->OnSpellCast(spell, caster, spellInfo, skipCheck));
}

void ScriptMgr::OnSpellPrepare(Spell* spell, Unit* caster, SpellInfo const* spellInfo)
{
    CALL_ENABLED_HOOKS(AllSpellScript, ALLSPELLHOOK_ON_PREPARE, script->OnSpellPrepare(spell, caster, spellInfo));
}

// @tswow-begin: generic spell script lifecycle dispatch
bool ScriptMgr::OnSpellLifecycle(Spell* spell, SpellLifecycleEvent type, uint32 value,
    Player* player, Quest const* quest, bool* boolValue, float* floatValue)
{
    CALL_ENABLED_BOOLEAN_HOOKS(AllSpellScript, ALLSPELLHOOK_ON_LIFECYCLE,
        !script->OnSpellLifecycle(spell, type, value, player, quest, boolValue, floatValue));
}
// @tswow-end

// @tswow-begin: generic aura script lifecycle dispatch
bool ScriptMgr::OnAuraLifecycle(Aura* aura, AuraLifecycleEvent type, AuraEffect const* effect,
    AuraApplication const* application, Unit* target, DispelInfo* dispelInfo, DamageInfo* damageInfo,
    ProcEventInfo* procInfo, int32* intValue, uint32* uintValue, bool* boolValue,
    SpellModifier* spellModifier, uint32 mode, float* floatValue)
{
    CALL_ENABLED_BOOLEAN_HOOKS(AllSpellScript, ALLSPELLHOOK_ON_AURA_LIFECYCLE,
        !script->OnAuraLifecycle(aura, type, effect, application, target, dispelInfo, damageInfo, procInfo,
            intValue, uintValue, boolValue, spellModifier, mode, floatValue));
}
// @tswow-end
// @tswow-begin: generic spell calculation dispatch
void ScriptMgr::OnSpellCalculation(SpellInfo const* spellInfo, SpellCalculationEvent type,
    WorldObject* caster, Unit* target, Spell* spell, float* floatValue, int32* intValue,
    uint32* uintValue, uint32* secondaryUIntValue, uint8 attackType, int32 argument)
{
    CALL_ENABLED_HOOKS(AllSpellScript, ALLSPELLHOOK_ON_CALCULATION,
        script->OnSpellCalculation(spellInfo, type, caster, target, spell, floatValue, intValue,
            uintValue, secondaryUIntValue, attackType, argument));
}
// @tswow-end

// @tswow-begin: cancellable spell effect dispatch
bool ScriptMgr::CanHandleSpellEffect(Spell* spell, SpellEffectInfo const* effect, uint32 mode,
    Unit* unitTarget, Item* itemTarget, GameObject* gameObjectTarget, Corpse* corpseTarget)
{
    CALL_ENABLED_BOOLEAN_HOOKS(AllSpellScript, ALLSPELLHOOK_CAN_HANDLE_EFFECT,
        !script->CanHandleSpellEffect(spell, effect, mode, unitTarget, itemTarget, gameObjectTarget,
            corpseTarget));
}
// @tswow-end

// @tswow-begin: generic spell damage lifecycle dispatch
void ScriptMgr::OnSpellDamage(Spell* spell, SpellDamagePhase phase, SpellNonMeleeDamage* damageInfo,
    int32* earlyDamage, uint32* lateDamage, uint8 attackType, bool critical, uint32 effectMask)
{
    CALL_ENABLED_HOOKS(AllSpellScript, ALLSPELLHOOK_ON_DAMAGE,
        script->OnSpellDamage(spell, phase, damageInfo, earlyDamage, lateDamage, attackType,
            critical, effectMask));
}
// @tswow-end

// @tswow-begin: generic spell target-selection dispatch
bool ScriptMgr::CanSelectSpellObjectAreaTarget(Spell* spell, std::list<WorldObject*>& targets,
    uint32 effectIndex, SpellImplicitTargetInfo const& targetType)
{
    CALL_ENABLED_BOOLEAN_HOOKS(AllSpellScript, ALLSPELLHOOK_ON_TARGET_SELECT,
        !script->CanSelectSpellObjectAreaTarget(spell, targets, effectIndex, targetType));
}

bool ScriptMgr::CanSelectSpellObjectTarget(Spell* spell, WorldObject*& target, uint32 effectIndex,
    SpellImplicitTargetInfo const& targetType)
{
    CALL_ENABLED_BOOLEAN_HOOKS(AllSpellScript, ALLSPELLHOOK_ON_TARGET_SELECT,
        !script->CanSelectSpellObjectTarget(spell, target, effectIndex, targetType));
}

bool ScriptMgr::CanSelectSpellDestinationTarget(Spell* spell, SpellDestination& target,
    uint32 effectIndex, SpellImplicitTargetInfo const& targetType)
{
    CALL_ENABLED_BOOLEAN_HOOKS(AllSpellScript, ALLSPELLHOOK_ON_TARGET_SELECT,
        !script->CanSelectSpellDestinationTarget(spell, target, effectIndex, targetType));
}
// @tswow-end

// @tswow-begin: generic player spellbook dispatch
void ScriptMgr::OnSpellLearn(SpellInfo const* spellInfo, Player* player, bool active, bool disabled,
    bool superseded, uint32 fromSkill)
{
    CALL_ENABLED_HOOKS(AllSpellScript, ALLSPELLHOOK_ON_SPELLBOOK,
        script->OnSpellLearn(spellInfo, player, active, disabled, superseded, fromSkill));
}

void ScriptMgr::OnSpellUnlearn(SpellInfo const* spellInfo, Player* player, bool disabled,
    bool learnLowRank)
{
    CALL_ENABLED_HOOKS(AllSpellScript, ALLSPELLHOOK_ON_SPELLBOOK,
        script->OnSpellUnlearn(spellInfo, player, disabled, learnLowRank));
}

void ScriptMgr::OnSpellUnlearnTalent(SpellInfo const* spellInfo, Player* player, uint32 tabIndex,
    uint32 tier, uint32 column, uint32 rank, bool direct)
{
    CALL_ENABLED_HOOKS(AllSpellScript, ALLSPELLHOOK_ON_SPELLBOOK,
        script->OnSpellUnlearnTalent(spellInfo, player, tabIndex, tier, column, rank, direct));
}
// @tswow-end

// @tswow-begin: mutable spell resistance and absorption dispatch
bool ScriptMgr::CanCalculateSpellResistAbsorb(Spell* spell, DamageInfo const& damageInfo,
    uint32& resistAmount, int32& absorbAmount)
{
    CALL_ENABLED_BOOLEAN_HOOKS(AllSpellScript, ALLSPELLHOOK_ON_RESIST_ABSORB,
        !script->CanCalculateSpellResistAbsorb(spell, damageInfo, resistAmount, absorbAmount));
}
// @tswow-end

AllSpellScript::AllSpellScript(char const* name, std::vector<uint16> enabledHooks)
    : ScriptObject(name, ALLSPELLHOOK_END)
{
    // If empty - enable all available hooks.
    if (enabledHooks.empty())
        for (uint16 i = 0; i < ALLSPELLHOOK_END; ++i)
            enabledHooks.emplace_back(i);

    ScriptRegistry<AllSpellScript>::AddScript(this, std::move(enabledHooks));
}

template class AC_GAME_API ScriptRegistry<AllSpellScript>;
