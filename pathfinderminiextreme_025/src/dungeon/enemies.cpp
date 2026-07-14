//
// Created by james on 7/12/2026.
//

#include "enemies.h"
#include <Arduino.h>

void generateGoblin()
{
    EnemyType type = (EnemyType)random(1, 4);

    enemy.characterClass = CLASS_FIGHTER;
    enemy.creatureType = CREATURE_GOBLIN;

    enemy.level = 1;
    enemy.xp = 0;

    enemy.inventoryCount = 0;

    enemy.equippedWeapon = -1;
    enemy.equippedArmor = -1;
    enemy.equippedShield = -1;

    switch (type)
    {
        case GOBLIN_SPEARMAN:

            enemy.name = "GOBLIN";

            enemy.abilities.strength = 12;
            enemy.abilities.dexterity = 13;
            enemy.abilities.constitution = 12;
            enemy.abilities.intelligence = 10;
            enemy.abilities.wisdom = 9;
            enemy.abilities.charisma = 8;

            break;

        case GOBLIN_ARCHER:

            enemy.name = "ARCHER";

            enemy.abilities.strength = 10;
            enemy.abilities.dexterity = 15;
            enemy.abilities.constitution = 10;
            enemy.abilities.intelligence = 10;
            enemy.abilities.wisdom = 10;
            enemy.abilities.charisma = 8;

            break;

        case GOBLIN_CHIEF:

            enemy.name = "CHIEF";

            enemy.abilities.strength = 15;
            enemy.abilities.dexterity = 13;
            enemy.abilities.constitution = 14;
            enemy.abilities.intelligence = 11;
            enemy.abilities.wisdom = 11;
            enemy.abilities.charisma = 12;

            break;
    }

    enemy.currentHP = getMaxHP(enemy);
}
