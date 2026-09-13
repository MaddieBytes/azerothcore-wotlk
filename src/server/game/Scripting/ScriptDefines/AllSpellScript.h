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

#ifndef SCRIPT_OBJECT_ALL_SPELL_SCRIPT_H_
#define SCRIPT_OBJECT_ALL_SPELL_SCRIPT_H_

#include "ScriptObject.h"
#include <list>
#include <vector>

enum AllSpellHook
{
    ALLSPELLHOOK_ON_CALC_MAX_DURATION,
    ALLSPELLHOOK_ON_SPELL_CHECK_CAST,
    ALLSPELLHOOK_CAN_PREPARE,
    ALLSPELLHOOK_CAN_SCALING_EVERYTHING,
    ALLSPELLHOOK_CAN_SELECT_SPEC_TALENT,
    ALLSPELLHOOK_ON_SCALE_AURA_UNIT_ADD,
    ALLSPELLHOOK_ON_REMOVE_AURA_SCALE_TARGETS,
    ALLSPELLHOOK_ON_BEFORE_AURA_RANK_FOR_LEVEL,
    ALLSPELLHOOK_ON_DUMMY_EFFECT_GAMEOBJECT,
    ALLSPELLHOOK_ON_DUMMY_EFFECT_CREATURE,
    ALLSPELLHOOK_ON_DUMMY_EFFECT_ITEM,
    ALLSPELLHOOK_ON_CAST_CANCEL,
    ALLSPELLHOOK_ON_CAST,
    ALLSPELLHOOK_ON_PREPARE,
    ALLSPELLHOOK_ON_IS_AURA_EXCLUSIVE_BY_SPECIFIC_WITH,
    // @tswow-begin: generic spell script lifecycle dispatch
    ALLSPELLHOOK_ON_LIFECYCLE,
    // @tswow-end
    // @tswow-begin: generic aura script lifecycle dispatch
    ALLSPELLHOOK_ON_AURA_LIFECYCLE,
    // @tswow-begin: generic spell calculation dispatch
    ALLSPELLHOOK_ON_CALCULATION,
    // @tswow-begin: cancellable spell effect dispatch
    ALLSPELLHOOK_CAN_HANDLE_EFFECT,
    // @tswow-end
    // @tswow-begin: generic spell damage lifecycle dispatch
    ALLSPELLHOOK_ON_DAMAGE,
    // @tswow-end
    // @tswow-begin: generic spell target-selection dispatch
    ALLSPELLHOOK_ON_TARGET_SELECT,
    // @tswow-end
    // @tswow-begin: generic player spellbook dispatch
    ALLSPELLHOOK_ON_SPELLBOOK,
    // @tswow-end
    // @tswow-begin: mutable spell resistance and absorption dispatch
    ALLSPELLHOOK_ON_RESIST_ABSORB,
    // @tswow-end
    // @tswow-end
    // @tswow-end
    ALLSPELLHOOK_END
};

// @tswow-begin: generic spell script lifecycle dispatch
enum class SpellLifecycleEvent : uint8
{
    BeforeCast,
    AfterCast,
    BeforeHit,
    Hit,
    AfterHit,
    Cancel,
    QuestFinish,
    EffectApplyGlyph,
    CalcCrit,
    SuccessfulDispel
};
// @tswow-end

// @tswow-begin: generic spell damage lifecycle dispatch
enum class SpellDamagePhase : uint8
{
    Early,
    Late
};
// @tswow-end

// @tswow-begin: generic aura script lifecycle dispatch
enum class AuraLifecycleEvent : uint8
{
    CheckAreaTarget,
    Dispel,
    AfterDispel,
    EffectApply,
    EffectRemove,
    AfterEffectApply,
    AfterEffectRemove,
    EffectPeriodic,
    Tick,
    EffectCalcAmount,
    EffectCalcPeriodic,
    EffectCalcSpellMod,
    EffectAbsorb,
    EffectAfterAbsorb,
    EffectManaShield,
    EffectAfterManaShield,
    EffectSplit,
    CheckProc,
    CheckEffectProc,
    PrepareProc,
    Proc,
    AfterProc,
    EffectProc,
    AfterEffectProc,
    SetDuration,
    PeriodicDamage,
    CalcAuraCrit
};
// @tswow-end

// @tswow-begin: generic spell calculation dispatch
enum class SpellCalculationEvent : uint8
{
    Miss,
    SpellPowerLevelPenalty,
    Reflect,
    Hit,
    Resist,
    MeleeMiss
};
// @tswow-end

enum SpellCastResult : uint8;
enum SpellEffIndex : uint8;
// @tswow-begin: generic aura script lifecycle dispatch
class Aura;
class AuraApplication;
class AuraEffect;
class DispelInfo;
class DamageInfo;
class ProcEventInfo;
class SpellModifier;
// @tswow-end

class AllSpellScript : public ScriptObject
{
protected:
    AllSpellScript(char const* name, std::vector<uint16> enabledHooks = std::vector<uint16>());

public:
    [[nodiscard]] bool IsDatabaseBound() const override { return false; }

    // Calculate max duration in applying aura
    virtual void OnCalcMaxDuration(Aura const* /*aura*/, int32& /*maxDuration*/) { }

    virtual void OnSpellCheckCast(Spell* /*spell*/, bool /*strict*/, SpellCastResult& /*res*/) { }

    [[nodiscard]] virtual bool CanPrepare(Spell* /*spell*/, SpellCastTargets const* /*targets*/, AuraEffect const* /*triggeredByAura*/) { return true; }

    [[nodiscard]] virtual bool CanScalingEverything(Spell* /*spell*/) { return false; }

    [[nodiscard]] virtual bool CanSelectSpecTalent(Spell* /*spell*/) { return true; }

    virtual void OnScaleAuraUnitAdd(Spell* /*spell*/, Unit* /*target*/, uint32 /*effectMask*/, bool /*checkIfValid*/, bool /*implicit*/, uint8 /*auraScaleMask*/, TargetInfo& /*targetInfo*/) { }

    virtual void OnRemoveAuraScaleTargets(Spell* /*spell*/, TargetInfo& /*targetInfo*/, uint8 /*auraScaleMask*/, bool& /*needErase*/) { }

    virtual void OnBeforeAuraRankForLevel(SpellInfo const* /*spellInfo*/, SpellInfo const* /*latestSpellInfo*/, uint8 /*level*/) { }

    virtual void OnIsAuraExclusiveBySpecificWith(SpellInfo const* /*spellInfo*/, SpellInfo const* /*otherSpellInfo*/, bool& /*isExclusive*/) { }

    /**
     * @brief This hook called after spell dummy effect
     *
     * @param caster Contains information about the WorldObject
     * @param spellID Contains information about the spell id
     * @param effIndex Contains information about the SpellEffIndex
     * @param gameObjTarget Contains information about the GameObject
     */
    virtual void OnDummyEffect(WorldObject* /*caster*/, uint32 /*spellID*/, SpellEffIndex /*effIndex*/, GameObject* /*gameObjTarget*/) { }

    /**
     * @brief This hook called after spell dummy effect
     *
     * @param caster Contains information about the WorldObject
     * @param spellID Contains information about the spell id
     * @param effIndex Contains information about the SpellEffIndex
     * @param creatureTarget Contains information about the Creature
     */
    virtual void OnDummyEffect(WorldObject* /*caster*/, uint32 /*spellID*/, SpellEffIndex /*effIndex*/, Creature* /*creatureTarget*/) { }

    /**
     * @brief This hook called after spell dummy effect
     *
     * @param caster Contains information about the WorldObject
     * @param spellID Contains information about the spell id
     * @param effIndex Contains information about the SpellEffIndex
     * @param itemTarget Contains information about the Item
     */
    virtual void OnDummyEffect(WorldObject* /*caster*/, uint32 /*spellID*/, SpellEffIndex /*effIndex*/, Item* /*itemTarget*/) { }

    virtual void OnSpellCastCancel(Spell* /*spell*/, Unit* /*caster*/, SpellInfo const* /*spellInfo*/, bool /*bySelf*/) { }

    virtual void OnSpellCast(Spell* /*spell*/, Unit* /*caster*/, SpellInfo const* /*spellInfo*/, bool /*skipCheck*/) { }

    virtual void OnSpellPrepare(Spell* /*spell*/, Unit* /*caster*/, SpellInfo const* /*spellInfo*/) { }

    // @tswow-begin: generic spell script lifecycle dispatch
    [[nodiscard]] virtual bool OnSpellLifecycle(Spell* /*spell*/, SpellLifecycleEvent /*type*/,
        uint32 /*value*/, Player* /*player*/ = nullptr, Quest const* /*quest*/ = nullptr,
        bool* /*boolValue*/ = nullptr, float* /*floatValue*/ = nullptr) { return true; }
    // @tswow-end

    // @tswow-begin: generic aura script lifecycle dispatch
    [[nodiscard]] virtual bool OnAuraLifecycle(Aura* /*aura*/, AuraLifecycleEvent /*type*/,
        AuraEffect const* /*effect*/ = nullptr, AuraApplication const* /*application*/ = nullptr,
        Unit* /*target*/ = nullptr, DispelInfo* /*dispelInfo*/ = nullptr, DamageInfo* /*damageInfo*/ = nullptr,
        ProcEventInfo* /*procInfo*/ = nullptr, int32* /*intValue*/ = nullptr, uint32* /*uintValue*/ = nullptr,
        bool* /*boolValue*/ = nullptr, SpellModifier* /*spellModifier*/ = nullptr, uint32 /*mode*/ = 0,
        float* /*floatValue*/ = nullptr)
    {
        return true;
    }
    // @tswow-end
    // @tswow-begin: generic spell calculation dispatch
    virtual void OnSpellCalculation(SpellInfo const* /*spellInfo*/, SpellCalculationEvent /*type*/,
        WorldObject* /*caster*/ = nullptr, Unit* /*target*/ = nullptr, Spell* /*spell*/ = nullptr,
        float* /*floatValue*/ = nullptr, int32* /*intValue*/ = nullptr, uint32* /*uintValue*/ = nullptr,
        uint32* /*secondaryUIntValue*/ = nullptr, uint8 /*attackType*/ = 0, int32 /*argument*/ = 0) { }
    // @tswow-end
    // @tswow-begin: cancellable spell effect dispatch
    [[nodiscard]] virtual bool CanHandleSpellEffect(Spell* /*spell*/, SpellEffectInfo const* /*effect*/,
        uint32 /*mode*/, Unit* /*unitTarget*/, Item* /*itemTarget*/, GameObject* /*gameObjectTarget*/,
        Corpse* /*corpseTarget*/) { return true; }
    // @tswow-end
    // @tswow-begin: generic spell damage lifecycle dispatch
    virtual void OnSpellDamage(Spell* /*spell*/, SpellDamagePhase /*phase*/,
        SpellNonMeleeDamage* /*damageInfo*/, int32* /*earlyDamage*/, uint32* /*lateDamage*/,
        uint8 /*attackType*/, bool /*critical*/, uint32 /*effectMask*/) { }
    // @tswow-end
    // @tswow-begin: generic spell target-selection dispatch
    [[nodiscard]] virtual bool CanSelectSpellObjectAreaTarget(Spell* /*spell*/,
        std::list<WorldObject*>& /*targets*/, uint32 /*effectIndex*/,
        SpellImplicitTargetInfo const& /*targetType*/) { return true; }
    [[nodiscard]] virtual bool CanSelectSpellObjectTarget(Spell* /*spell*/, WorldObject*& /*target*/,
        uint32 /*effectIndex*/, SpellImplicitTargetInfo const& /*targetType*/) { return true; }
    [[nodiscard]] virtual bool CanSelectSpellDestinationTarget(Spell* /*spell*/, SpellDestination& /*target*/,
        uint32 /*effectIndex*/, SpellImplicitTargetInfo const& /*targetType*/) { return true; }
    // @tswow-end
    // @tswow-begin: generic player spellbook dispatch
    virtual void OnSpellLearn(SpellInfo const* /*spellInfo*/, Player* /*player*/, bool /*active*/,
        bool /*disabled*/, bool /*superseded*/, uint32 /*fromSkill*/) { }
    virtual void OnSpellUnlearn(SpellInfo const* /*spellInfo*/, Player* /*player*/, bool /*disabled*/,
        bool /*learnLowRank*/) { }
    virtual void OnSpellUnlearnTalent(SpellInfo const* /*spellInfo*/, Player* /*player*/,
        uint32 /*tabIndex*/, uint32 /*tier*/, uint32 /*column*/, uint32 /*rank*/, bool /*direct*/) { }
    // @tswow-end
    // @tswow-begin: mutable spell resistance and absorption dispatch
    [[nodiscard]] virtual bool CanCalculateSpellResistAbsorb(Spell* /*spell*/,
        DamageInfo const& /*damageInfo*/, uint32& /*resistAmount*/, int32& /*absorbAmount*/)
    {
        return true;
    }
    // @tswow-end
};

// Compatibility for old scripts
using SpellSC = AllSpellScript;

#endif
