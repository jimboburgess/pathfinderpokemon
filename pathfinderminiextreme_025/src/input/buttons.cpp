//
// Created by james on 7/12/2026.
//

#include "buttons.h"
#include "Arduino.h"
#include "characters/sheet.h"

//======================================
// Input State
//======================================

bool encoderLastCLK = HIGH;
unsigned long encoderLastMove = 0;

bool selectLast = HIGH;
bool aLast = HIGH;
bool bLast = HIGH;

const uint16_t ENCODER_DEBOUNCE = 3;

//======================================================
// Start Screen
//======================================================

void handleStartButtons()
{
    bool selectNow = digitalRead(ENCODER_SW);
    bool aNow = digitalRead(BUTTON_A);
    bool bNow = digitalRead(BUTTON_B);

    if ((selectNow == LOW && selectLast == HIGH) ||
        (aNow == LOW && aLast == HIGH) ||
        (bNow == LOW && bLast == HIGH))
    {
        playSound(SoundEffect::MENU_SELECT);
        resetButtonStates();
        gameState = GAME_CHARACTER_CREATION;
        needsRedraw = true;
    }

    selectLast = selectNow;
    aLast = aNow;
    bLast = bNow;
}

//======================================================
// Character Creation
//======================================================

void handleCharacterCreationButtons()
{
    bool selectNow = digitalRead(ENCODER_SW);
    bool aNow      = digitalRead(BUTTON_A);
    bool bNow      = digitalRead(BUTTON_B);
    bool clkNow    = digitalRead(ENCODER_CLK);
    bool dtNow     = digitalRead(ENCODER_DT);

    //--------------------------------------------------
    // Encoder Rotation
    //--------------------------------------------------

    if (clkNow != encoderLastCLK && clkNow == LOW)
    {
        if (millis() - encoderLastMove > ENCODER_DEBOUNCE)
        {
            encoderLastMove = millis();

            bool clockwise = (dtNow != clkNow);

            switch (getCharacterCreationState())
            {
                case CCS_CLASS_SELECT:

                    if (clockwise)
                        rotateCharacterClassCW();
                    else
                        rotateCharacterClassCCW();

                    playSound(SoundEffect::MENU_MOVE);
                    break;

                case CCS_VIEW_STATS:

                    if (clockwise)
                        scrollCharacterSheetDown();
                    else
                        scrollCharacterSheetUp();

                    needsRedraw = true;
                    playSound(SoundEffect::MENU_MOVE);
                    break;

                case CCS_MENU:

                    if (clockwise)
                        menuDown();
                    else
                        menuUp();

                    playSound(SoundEffect::MENU_MOVE);

                    // Menu redraws itself.
                    break;
            }
        }
    }

    encoderLastCLK = clkNow;

    //--------------------------------------------------
    // Encoder Click
    //--------------------------------------------------

    if (selectNow == LOW && selectLast == HIGH)
    {
        playSound(SoundEffect::MENU_SELECT);

        switch (getCharacterCreationState())
        {
            case CCS_CLASS_SELECT:

                createPreviewCharacter();
                break;

            case CCS_VIEW_STATS:

                // Nothing to select.
                break;

            case CCS_MENU:

                menuSelect();
                break;
        }
    }

    //--------------------------------------------------
    // A Button
    //--------------------------------------------------

    if (aNow == LOW && aLast == HIGH)
    {
        switch (getCharacterCreationState())
        {
            case CCS_CLASS_SELECT:

                // No action.
                break;

            case CCS_VIEW_STATS:

                openCharacterMenu();
                playSound(SoundEffect::MENU_SELECT);
                break;

            case CCS_MENU:

                // Reserved for future submenus.
                break;
        }
    }

    //--------------------------------------------------
    // B Button
    //--------------------------------------------------

    if (bNow == LOW && bLast == HIGH)
    {
        switch (getCharacterCreationState())
        {
            case CCS_CLASS_SELECT:

                // Nothing.
                break;

            case CCS_VIEW_STATS:

                enterCharacterCreation();

                playSound(SoundEffect::MENU_SELECT);
                break;

            case CCS_MENU:

                closeCharacterMenu();
                playSound(SoundEffect::MENU_SELECT);
                break;
        }
    }

    //--------------------------------------------------
    // Save Button States
    //--------------------------------------------------

    selectLast = selectNow;
    aLast = aNow;
    bLast = bNow;
}

//======================================================
// Town
//======================================================

void handleTownButtons()
{
    bool selectNow = digitalRead(ENCODER_SW);
    bool clkNow = digitalRead(ENCODER_CLK);

    if (clkNow != encoderLastCLK && clkNow == LOW)
    {
        if (millis() - encoderLastMove > ENCODER_DEBOUNCE)
        {
            encoderLastMove = millis();

            if (digitalRead(ENCODER_DT) != clkNow)
            {
                townSelection =
                    (TownOption)((townSelection + 1) % TOWN_OPTION_COUNT);
            }
            else
            {
                townSelection =
                    (TownOption)((townSelection - 1 + TOWN_OPTION_COUNT) % TOWN_OPTION_COUNT);
            }

            playSound(SoundEffect::MENU_MOVE);
            needsRedraw = true;
        }
    }

    encoderLastCLK = clkNow;

    if (selectNow == LOW && selectLast == HIGH)
    {
        playSound(SoundEffect::MENU_SELECT);

        switch (townSelection)
        {
            case TOWN_GOBLINS:

                // TODO:
                // Generate goblin dungeon.

                break;

            case TOWN_STAY_HOME:

                break;

            case TOWN_DUNGEON:

                generateDungeon(dungeon);
                gameState = GAME_DUNGEON;
                break;
        }

        needsRedraw = true;
    }

    selectLast = selectNow;
}

//======================================================
// Dungeon
//======================================================

void handleDungeonButtons()
{
    bool selectNow = digitalRead(ENCODER_SW);
    bool clkNow = digitalRead(ENCODER_CLK);

    if (clkNow != encoderLastCLK && clkNow == LOW)
    {
        if (millis() - encoderLastMove > ENCODER_DEBOUNCE)
        {
            encoderLastMove = millis();

            if (digitalRead(ENCODER_DT) != clkNow)
            {
                rotateDirectionCW();
            }
            else
            {
                rotateDirectionCCW();
            }

            playSound(SoundEffect::MENU_MOVE);
            needsRedraw = true;
        }
    }

    encoderLastCLK = clkNow;

    if (selectNow == LOW && selectLast == HIGH)
    {
        if (tryMovePlayer(dungeon))
        {
            needsRedraw = true;
        }
    }

    selectLast = selectNow;
}

//======================================================
// Main Button Handler
//======================================================

void resetButtonStates()
{
    encoderLastCLK = digitalRead(ENCODER_CLK);

    selectLast = digitalRead(ENCODER_SW);
    aLast = digitalRead(BUTTON_A);
    bLast = digitalRead(BUTTON_B);

    encoderLastMove = millis();
}

void handleButtons()
{
    switch (gameState)
    {
        case GAME_START:
            handleStartButtons();
            break;

        case GAME_CHARACTER_CREATION:
            handleCharacterCreationButtons();
            break;

        case GAME_TOWN:
            handleTownButtons();
            break;

        case GAME_DUNGEON:
            handleDungeonButtons();
            break;
    }
}