#ifndef MOVEVALIDATOR_H
#define MOVEVALIDATOR_H

#include <vector>
#include <cmath> // Для std::abs()

// Определение фигур
enum Piece {
    EMPTY,
    WHITE_PAWN, WHITE_ROOK, WHITE_KNIGHT, WHITE_BISHOP, WHITE_QUEEN, WHITE_KING,
    BLACK_PAWN, BLACK_ROOK, BLACK_KNIGHT, BLACK_BISHOP, BLACK_QUEEN, BLACK_KING
};

// Интерфейс проверки правил хода
class MoveValidator {
public:
    static bool isValidMove(Piece piece, int fromRow, int fromCol, int toRow, int toCol, const std::vector<std::vector<Piece>>& board);
};

#endif
