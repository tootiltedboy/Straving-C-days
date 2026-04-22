#ifndef CHECKVALIDATOR_H
#define CHECKVALIDATOR_H

#include "MoveValidator.h"

class CheckValidator {
public:
    static bool isKingInCheck(const GameState& state, Color color);
    static bool isCheckmate(const GameState& state, Color color);
    static bool isStalemate(const GameState& state, Color color);
};

#endif
