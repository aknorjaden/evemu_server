/*
    ------------------------------------------------------------------------------------
    LICENSE:
    ------------------------------------------------------------------------------------
    This file is part of EVEmu: EVE Online Server Emulator
    Copyright 2006 - 2011 The EVEmu Team
    For the latest information visit http://evemu.org
    ------------------------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License as published by the Free Software
    Foundation; either version 2 of the License, or (at your option) any later
    version.

    This program is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License along with
    this program; if not, write to the Free Software Foundation, Inc., 59 Temple
    Place - Suite 330, Boston, MA 02111-1307, USA, or go to
    http://www.gnu.org/copyleft/lesser.txt.
    ------------------------------------------------------------------------------------
    Author:        Luck
*/

#ifndef MODULE_DEFS_H
#define MODULE_DEFS_H

#include "inventory/AttributeEnum.h"

// Important constants pertaining to modules and their operation:
#define ONLINE_MODULE_IN_SPACE_CAP_PENALTY					0.75		// 75% of your capacitor will be drained when you online a module while in space, if you have it ;)

//more will go here
//this is to avoid include complications and multiple dependancies etc..
enum ModuleCommand
{
    CMD_ERROR = 1000,
    ONLINE,
    OFFLINE,
    ACTIVATE,
    DEACTIVATE,
    OVERLOAD,       //idk if this is used yet - or what it's called :)
    DEOVERLOAD,     //idk if this is used
    LOAD_CHARGE,
    RELOAD_CHARGE,
    UNLOAD_CHARGE
};

// *** use these values to decode the 'effectAppliedInState' field of the 'dgmEffectsActions' database table
enum ModuleStates
{
    MOD_UNFITTED = 1100,
    MOD_OFFLINE,
    MOD_ONLINE,
    MOD_ACTIVATED,
    MOD_OVERLOADED,
    MOD_DEACTIVATING
};

enum ChargeStates
{
    MOD_UNLOADED = 1200,
    MOD_LOADING,
    MOD_RELOADING,
    MOD_LOADED
};

// These are the module states where an effect will, ahem, take 'effect':
// *** use these values to decode the 'effectAppliedBehavior' field of the 'dgmEffectsInfo' database table
enum ModuleEffectAppliedBehaviors
{
    EFFECT_PERSISTENT = 1300,   // means the effect is active AT ALL TIMES; used ONLY for skill, ship, subsystem effects
    EFFECT_ONLINE,              // means the effect takes effect on the target (see below) upon entering the ONLINE state
    EFFECT_ACTIVE,              // used only for ACTIVE modules operating in non-Overloaded mode
    EFFECT_OVERLOAD             // used only for ACTIVE modules operating in Overloaded mode
};

// These are the target types to which module and other types' effects are applied when activated:
// *** use these values to decode the 'effectTargetEquipmentType' field of the 'dgmEffectsInfo' database table
enum EffectTargetEquipmentTypes
{
    EQUIP_MODULE = 1400,
    EQUIP_CHARGE,
    EQUIP_THIS_SHIP,
    EQUIP_DRONE,
    EQUIP_EXTERNAL_SHIP,
    EQUIP_EXTERNAL_SHIP_MODULE,
    EQUIP_EXTERNAL_SHIP_CHARGE
};

// These are the target types to which module effects are applied when activated:
// *** use these values to decode the 'effectAppliedTo' field of the 'dgmEffectsInfo' database table
enum ModuleEffectAppliedToTargetTypes
{
    EFFECT_TARGET_SELF  = 1500, // 1500: means the target of the effect is the module's own attribute(s)
    EFFECT_TARGET_SHIP,         // 1501: means the target of the effect is the attribute(s) of the ship to which the module is fitted
    EFFECT_TARGET_EXTERNAL,     // 1502: means the target of the effect is the attribute(s) of the current target of the ship to which the module is fitted
	EFFECT_MODULE_ON_SHIP,		// 1503: means a module or modules that are fitted to the current ship, this special case will indicate when the effect is
								// applied to other modules applied to the same ship - the dgmEffectsActions table fields of targetEquipmentType and
								// targetGroupIDs will have additional information for the Module Manager to make use of this effect
	EFFECT_LOADED_CHARGE,		// 1504: means that the effect is from a charge loaded into a weapon module so this will affect the weapon module the charge
								// is loaded into
	EFFECT_CHARGE,				// 1505: means that the effect acts upon a charge loaded into a weapon module so this will affect charges of the specified
								// groupID loaded into any module on the ship
	EFFECT_CHARACTER			// 1506: means that the effect acts upon the character's attribute specific to the effect

};

// These are the methods by which module effects are applied to the designated target:
// *** use these values to decode the 'effectApplicationType' field of the 'dgmEffectsInfo' database table
enum ModuleApplicationTypes
{
    EFFECT_ONLINE_MAINTAIN = 1600,  // applied by PASSIVE or ACTIVE modules where an effect is maintained; means the effect takes effect on the
                                    // target (see below) upon entering the ONLINE state, then reversed when going out of ONLINE state
    EFFECT_ACTIVE_MAINTAIN,         // applied by ACTIVE modules where an effect is maintained; means the effect takes effect on the
                                    // target (see below) upon entering the ACTIVATE state, then reversed when going out of ACTIVATE state
    EFFECT_ACTIVE_ACCUMULATE        // applied by ACTIVE modules where an effect is applied cumulatively on each cycle; means the effect takes
};                                  // effect on the target (see below) one extra time when in ACTIVATE state after each CYCLE duration expires

// These are the methods by which module effects are applied to the designated target:
// *** use these values to decode the 'stackingPenaltyApplied' field of the 'dgmEffectsInfo' database table
enum ModuleStackingPenaltyState
{
    NO_STACKING_PENALTY = 1700,
    STACKING_PENALTY_APPLIES
};

//this may or may not be redundant...idk
enum ModulePowerLevel
{
    MODULE_BANK_RIG = 1800,
    MODULE_BANK_LOW_POWER,
    MODULE_BANK_MEDIUM_POWER,
    MODULE_BANK_HIGH_POWER,
    MODULE_BANK_SUBSYSTEM
};

//calculation types
// *** use these values to decode the 'calculationTypeID' and the 'reverseCalculationTypeID' fields of the 'dgmEffectsInfo' database table
enum EVECalculationType
{
    CALC_NONE = 2000,
    CALC_AUTO,
    CALC_ADD,
    CALC_SUBTRACT,
    CALC_DIVIDE,
    CALC_MULTIPLY,
    CALC_ADD_PERCENT,
    CALC_REV_ADD_PERCENT,
    CALC_SUBTRACT_PERCENT,
    CALC_REV_SUBTRACT_PERCENT,
    CALC_ADD_AS_PERCENT,
    CALC_SUBTRACT_AS_PERCENT,
    CALC_MODIFY_PERCENT_W_PERCENT,
    CALC_REV_MODIFY_PERCENT_W_PERCENT,
    CALC_MWD_AB_EQUATION,
	CALC_ECM_JAM_EQUATION,
	CALC_REDUCE_BY_PERCENT,
	CALC_REV_REDUCE_BY_PERCENT
    //more will show up, im sure
};


//TODO - check mem usage
static EvilNumber Add(EvilNumber &val1, EvilNumber &val2)
{
    return val1 + val2;
}

static EvilNumber Subtract(EvilNumber &val1, EvilNumber &val2)
{
    return val1 - val2;
}

static EvilNumber Divide(EvilNumber &val1, EvilNumber &val2)
{
    return ( val1 / val2 );
}

static EvilNumber Multiply(EvilNumber &val1, EvilNumber &val2)
{
    return val1 * val2;
}

static EvilNumber AddPercent(EvilNumber &val1, EvilNumber &val2)
{
    return val1 + ( val1 * val2 );
}

static EvilNumber ReverseAddPercent(EvilNumber &val1, EvilNumber &val2)
{
    EvilNumber val3 = 1;
    return val1 / ( val3 + val2 );
}

static EvilNumber SubtractPercent(EvilNumber &val1, EvilNumber &val2)
{
    return val1 - ( val1 * val2 );
}

static EvilNumber ReverseSubtractPercent(EvilNumber &val1, EvilNumber &val2)
{
    EvilNumber val3 = 1;
    return val1 / ( val3 - val2 );
}

static EvilNumber AddAsPercent(EvilNumber &val1, EvilNumber &val2)
{
    EvilNumber val3 = 100;
    return val1 + ( val1 * (val2 / val3) );
}

static EvilNumber SubtractAsPercent(EvilNumber &val1, EvilNumber &val2)
{
    EvilNumber val3 = 1;
    EvilNumber val4 = 100;

    return val1 / ( val3 + (val2 / val4) );
}

static EvilNumber ModifyPercentWithPercent(EvilNumber &val1, EvilNumber &val2)
{
    EvilNumber val3 = 1;
    EvilNumber val4 = 100;

    return val1 * (val3 + (val2 / val4) );
}

static EvilNumber ReverseModifyPercentWithPercent(EvilNumber &val1, EvilNumber &val2)
{
    EvilNumber val3 = 1;
    EvilNumber val4 = 100;

    return val4 * ( (val1 / val2) - 1 );
}

static EvilNumber ReduceByPercent(EvilNumber &val1, EvilNumber &val2)
{
	EvilNumber val3 = 1;
	EvilNumber val4 = 100;

	return val1 * ( val3 - (val2 / val4) );
}

static EvilNumber ReverseReduceByPercent(EvilNumber &val1, EvilNumber &val2)
{
	EvilNumber val3 = 1;
	EvilNumber val4 = 100;

	return val1 / ( val3 - (val2 / val4) );
}

static EvilNumber CalculateNewAttributeValue(EvilNumber attrVal, EvilNumber attrMod, EVECalculationType type)
{
    switch(type)
    {
        case CALC_NONE :                            return attrVal;
        case CALC_AUTO :                            return attrVal;                             // AUTO NOT SUPPORTED AT THIS TIME !!!
        case CALC_ADD :                             return Add(attrVal, attrMod);
        case CALC_SUBTRACT :                        return Subtract(attrVal, attrMod);
        case CALC_DIVIDE :                          return Divide(attrVal, attrMod);
        case CALC_MULTIPLY :                        return Multiply(attrVal, attrMod);
        case CALC_ADD_PERCENT :                     return AddPercent(attrVal, attrMod);
        case CALC_REV_ADD_PERCENT :                 return ReverseAddPercent(attrVal, attrMod);
        case CALC_SUBTRACT_PERCENT :                return SubtractPercent(attrVal, attrMod);
        case CALC_REV_SUBTRACT_PERCENT :            return ReverseSubtractPercent(attrVal, attrMod);
        case CALC_ADD_AS_PERCENT :                  return AddAsPercent(attrVal, attrMod);
        case CALC_SUBTRACT_AS_PERCENT :             return SubtractAsPercent(attrVal, attrMod);
        case CALC_MODIFY_PERCENT_W_PERCENT :        return ModifyPercentWithPercent(attrVal, attrMod);
        case CALC_REV_MODIFY_PERCENT_W_PERCENT :    return ReverseModifyPercentWithPercent(attrVal, attrMod);
		case CALC_REDUCE_BY_PERCENT:				return ReduceByPercent(attrVal, attrMod);
		case CALC_REV_REDUCE_BY_PERCENT :			return ReverseReduceByPercent(attrVal, attrMod);
    }

    sLog.Error("CalculateNewAttributeValue", "Unknown EveCalculationType used");
    assert(false);
    return 0;
}

#endif
