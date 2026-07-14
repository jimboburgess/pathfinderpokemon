//
// Created by james on 7/12/2026.
//

#ifndef PATHFINDERMINIEXTREME_025_COMBAT_H
#define PATHFINDERMINIEXTREME_025_COMBAT_H

//Combat manages turns. It does not decide abilities.

#include <Arduino.h>
#include "../characters/characters.h"

//======================================
// Combat Phases
//======================================

enum CombatPhase
{
    COMBAT_NONE,
    COMBAT_INITIATIVE,
    COMBAT_TURN,
    COMBAT_END
};

const uint8_t DETECTION_RANGE = 6;

struct Combat
{
    bool active = false;

    CombatPhase phase = COMBAT_NONE;
    Character* turnOrder[MAX_DUNGEON_CHARACTERS];
    uint8_t combatantCount = 0;
    uint8_t currentTurnIndex = 0;
    uint8_t round = 1;
    uint8_t movementRemaining = 0;
    bool standardActionUsed = false;
};

extern Combat combat;

//======================================
// Combat State
//======================================

extern Combat combat;

uint8_t round;

//======================================
// Combat Functions
//======================================

void startCombat();

void checkForCombat();

void endCombat();

void updateCombat();

bool isCombatActive();

#endif //PATHFINDERMINIEXTREME_025_COMBAT_H
