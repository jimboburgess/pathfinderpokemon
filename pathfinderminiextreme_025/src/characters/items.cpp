//
// Created by james on 7/12/2026.
//

#include "items.h"
#include <Arduino.h>

void usePotion(Character& character, PotionType type) {

    switch (type) {

        case POTION_HEALING:
        {

            if (character.potions[POTION_HEALING] <= 0) {

                battleMessage = "No healing potions!";
                return;
            }

            character.potions[POTION_HEALING]--;

            int healAmount = random(1, 9) + 1;  // 1d8+1

            character.hp += healAmount;

            if (character.hp > character.maxHP) {
                character.hp = character.maxHP;
            }

            playSound(SoundEffect::POTION);

            battleMessage =
              String(character.name) + " healed " + String(healAmount) + " HP!";

            break;
        }
    }
}

const Weapon weaponDatabase[] =
{
    { "Club", 1, 4, DAMAGE_BLUDGEONING },
    { "Dagger", 1, 4, DAMAGE_PIERCING },
    { "Shortsword", 1, 6, DAMAGE_PIERCING },
    { "Longsword", 1, 8, DAMAGE_SLASHING },
    { "Battleaxe", 1, 8, DAMAGE_SLASHING }
};

const Armor armorDatabase[] =
{
    {"None",0},
    {"Leather",2},
    {"Studded Leather",3},
    {"Chain Shirt",4},
    {"Chainmail",6},
    {"Full Plate",9}
};

const Shield shieldDatabase[] =
{
    {"None",0},
    {"Buckler",1},
    {"Light Shield",1},
    {"Heavy Shield",2},
    {"Tower Shield",4}
};