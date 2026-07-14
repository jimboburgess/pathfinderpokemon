//
// Created by james on 7/13/2026.
//

#include "charactercreation.h"

static const Ability fighterPriority[6] =
{
    ABILITY_STRENGTH,
    ABILITY_CONSTITUTION,
    ABILITY_DEXTERITY,
    ABILITY_WISDOM,
    ABILITY_INTELLIGENCE,
    ABILITY_CHARISMA
};

static const Ability roguePriority[6] =
{
    ABILITY_DEXTERITY,
    ABILITY_INTELLIGENCE,
    ABILITY_WISDOM,
    ABILITY_CHARISMA,
    ABILITY_CONSTITUTION,
    ABILITY_STRENGTH
};

static const Ability wizardPriority[6] =
{
    ABILITY_INTELLIGENCE,
    ABILITY_DEXTERITY,
    ABILITY_WISDOM,
    ABILITY_CONSTITUTION,
    ABILITY_CHARISMA,
    ABILITY_STRENGTH
};

static const Ability clericPriority[6] =
{
    ABILITY_WISDOM,
    ABILITY_CONSTITUTION,
    ABILITY_STRENGTH,
    ABILITY_CHARISMA,
    ABILITY_DEXTERITY,
    ABILITY_INTELLIGENCE
};

struct StartingEquipment
{
    ItemID meleeWeapon;
    ItemID rangedWeapon;

    ItemID armor;
    ItemID shield;
};

static const StartingEquipment startingEquipment[] =
{
    // Fighter
    {
        ITEM_LONGSWORD,
        ITEM_SHORTBOW,
        ITEM_CHAINMAIL,
        ITEM_HEAVY_SHIELD
    },

    // Rogue
    {
        ITEM_DAGGER,
        ITEM_CROSSBOW,
        ITEM_LEATHER,
        ITEM_NONE
    },

    // Wizard
    {
        ITEM_STAFF,
        ITEM_SHORTBOW,
        ITEM_NONE,
        ITEM_NONE
    },

    // Cleric
    {
        ITEM_MACE,
        ITEM_CROSSBOW,
        ITEM_CHAINMAIL,
        ITEM_HEAVY_SHIELD
    }
};

void createCharacter(
    Character& character,
    CharacterClass characterClass,
    const String& name);