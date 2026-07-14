//
// Created by james on 7/12/2026.
//

#include "characters.h"
#include "Arduino.h"
#include "data/progression.h"


//void initializeCharacter(Character& character,

int getAbilityModifier(const Character& character, Ability ability) {
  int score = 10;

  switch (ability) {
    case ABILITY_STRENGTH:
      score = character.abilities.strength;
      break;

    case ABILITY_DEXTERITY:
      score = character.abilities.dexterity;
      break;

    case ABILITY_CONSTITUTION:
      score = character.abilities.constitution;
      break;

    case ABILITY_INTELLIGENCE:
      score = character.abilities.intelligence;
      break;

    case ABILITY_WISDOM:
      score = character.abilities.wisdom;
      break;

    case ABILITY_CHARISMA:
      score = character.abilities.charisma;
      break;
  }

  if (score >= 10)
    return (score - 10) / 2;

  return (score - 11) / 2;
}

int getMaxHP(const Character& character)
{
  return getBaseHitPoints(
      character.characterClass,
      character.level)
      + getAbilityModifier(character, ABILITY_CONSTITUTION);
}

int getArmorClass(const Character& character)
{
  return 10 + getAbilityModifier(character, ABILITY_DEXTERITY);
}

int getMeleeAttackBonus(const Character& character)
{
  return getBaseAttackBonus(
      character.characterClass,
      character.level)
      + getAbilityModifier(character, ABILITY_STRENGTH);
}

int getRangedAttackBonus(const Character& character)
{
  return getBaseAttackBonus(
      character.characterClass,
      character.level)
      + getAbilityModifier(character, ABILITY_DEXTERITY);
}

