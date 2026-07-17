//
// Created by james on 7/16/2026.
//

#include "sheet.h"
#include "graphics/display.h"
#include "graphics/sprites.h"
#include <cstring>


static Character* currentCharacter = nullptr;
static int scrollOffset = 0;

static void drawText(int x, int y, const char* text)
{
    y -= scrollOffset;

    if (y < -12 || y > 240)
        return;

    tft.setCursor(x, y);
    tft.print(text);
}

static void drawValue(int x, int y, int value)
{
    y -= scrollOffset;

    if (y < -12 || y > 240)
        return;

    tft.setCursor(x, y);
    tft.print(value);
}

static void drawDivider(int y)
{
    y -= scrollOffset;

    if (y < 0 || y > 240)
        return;

    tft.drawFastHLine(0, y, 240, ST77XX_WHITE);
}

static void drawLabelValue(int labelX,
                           int valueX,
                           int y,
                           const char* label,
                           int value)
{
    drawText(labelX, y, label);
    drawValue(valueX, y, value);
}

void scrollCharacterSheetUp()
{
    if (scrollOffset >= 10)
        scrollOffset -= 10;
}

void scrollCharacterSheetDown()
{
    scrollOffset += 10;
}

void enterCharacterSheet(Character* character)
{
    currentCharacter = character;
    scrollOffset = 0;
}

void drawCharacterSheet()
{
    if (currentCharacter == nullptr)
        return;

    const int LEFT_X = 5;
    const int RIGHT_X = 125;

    const int LEFT_VALUE_X = 85;
    const int RIGHT_VALUE_X = 205;

    tft.fillScreen(ST77XX_BLACK);
    tft.setTextColor(ST77XX_WHITE);
    tft.setTextSize(1);

    //----------------------------------
    // Header
    //----------------------------------

    drawText(70, 5, getCharacterClassName(currentCharacter->characterClass));

    drawText(LEFT_X, 22, "HP");
    drawValue(30, 22, currentCharacter->currentHP);

    drawText(50, 22, "/");
    drawValue(60, 22, getMaxHP(*currentCharacter));

    drawText(RIGHT_X, 22, "AC");
    drawValue(155, 22, getArmorClass(*currentCharacter));

    drawText(LEFT_X, 34, "XP");
    drawValue(30, 34, currentCharacter->xp);

    drawText(RIGHT_X, 34, "Lv");
    drawValue(155, 34, currentCharacter->level);

    drawDivider(48);

    //--------------------------------------------------
    // Left Column - Abilities
    //--------------------------------------------------

    int y = 60;

    drawText(LEFT_X, y, "Abilities");
    y += 12;

    drawLabelValue(LEFT_X, LEFT_VALUE_X, y, "Strength",     currentCharacter->abilities.strength);      y += 10;
    drawLabelValue(LEFT_X, LEFT_VALUE_X, y, "Dexterity",    currentCharacter->abilities.dexterity);     y += 10;
    drawLabelValue(LEFT_X, LEFT_VALUE_X, y, "Constitution", currentCharacter->abilities.constitution);  y += 10;
    drawLabelValue(LEFT_X, LEFT_VALUE_X, y, "Intelligence", currentCharacter->abilities.intelligence);  y += 10;
    drawLabelValue(LEFT_X, LEFT_VALUE_X, y, "Wisdom",       currentCharacter->abilities.wisdom);        y += 10;
    drawLabelValue(LEFT_X, LEFT_VALUE_X, y, "Charisma",     currentCharacter->abilities.charisma);

    //--------------------------------------------------
    // Right Column - Combat
    //--------------------------------------------------

    y = 60;

    drawText(RIGHT_X, y, "Combat");
    y += 12;

    drawLabelValue(RIGHT_X, RIGHT_VALUE_X, y, "Armor Class", getArmorClass(*currentCharacter));          y += 10;
    drawLabelValue(RIGHT_X, RIGHT_VALUE_X, y, "Melee",       getMeleeAttackBonus(*currentCharacter));    y += 10;
    drawLabelValue(RIGHT_X, RIGHT_VALUE_X, y, "Ranged",      getRangedAttackBonus(*currentCharacter));   y += 16;

    drawText(RIGHT_X, y, "Saving Throws");
    y += 12;

    drawLabelValue(RIGHT_X, RIGHT_VALUE_X, y, "Fortitude", getFortitudeSave(*currentCharacter));         y += 10;
    drawLabelValue(RIGHT_X, RIGHT_VALUE_X, y, "Reflex",    getReflexSave(*currentCharacter));            y += 10;
    drawLabelValue(RIGHT_X, RIGHT_VALUE_X, y, "Will",      getWillSave(*currentCharacter));

    //--------------------------------------------------
    // Bottom Section
    //--------------------------------------------------

    drawDivider(150);

    y = 162;

    drawText(LEFT_X, y, "Skills");
    y += 12;

    drawLabelValue(LEFT_X, LEFT_VALUE_X, y, "Acrobatics",     getSkillBonus(*currentCharacter, SKILL_ACROBATICS));      y += 10;
    drawLabelValue(LEFT_X, LEFT_VALUE_X, y, "Diplomacy",      getSkillBonus(*currentCharacter, SKILL_DIPLOMACY));       y += 10;
    drawLabelValue(LEFT_X, LEFT_VALUE_X, y, "Dsable Dvice", getSkillBonus(*currentCharacter, SKILL_DISABLE_DEVICE));  y += 10;
    drawLabelValue(LEFT_X, LEFT_VALUE_X, y, "Intimidate",     getSkillBonus(*currentCharacter, SKILL_INTIMIDATE));      y += 10;
    drawLabelValue(LEFT_X, LEFT_VALUE_X, y, "Perception",     getSkillBonus(*currentCharacter, SKILL_PERCEPTION));      y += 10;
    drawLabelValue(LEFT_X, LEFT_VALUE_X, y, "Stealth",        getSkillBonus(*currentCharacter, SKILL_STEALTH));

    drawText(RIGHT_X, 162, "Equipment");

    drawText(RIGHT_X, 174, "Weapon");
    drawText(RIGHT_X, 186, "Armor");
    drawText(RIGHT_X, 198, "Shield");

    drawText(RIGHT_X, 220, "Inventory");
    drawValue(205, 220, currentCharacter->inventoryCount);
}