#ifndef CHECKVALIDATOR_H
#define CHECKVALIDATOR_H

#include <vector>
#include "MoveValidator.h"

class CheckValidator {
public:
    static bool isKingInCheck(Piece king, int kingRow, int kingCol, const std::vector<std::vector<Piece>>& board);
};

#endif