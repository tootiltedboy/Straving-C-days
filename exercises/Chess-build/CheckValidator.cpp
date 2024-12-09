#include "CheckValidator.h"

// Проверка, находится ли король в шахе
bool CheckValidator::isKingInCheck(Piece king, int kingRow, int kingCol, const std::vector<std::vector<Piece>>& board) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Piece attacker = board[i][j];
            if (attacker != EMPTY && (attacker < BLACK_PAWN) == (king < BLACK_PAWN)) {
                // Игнорируем союзные фигуры
                continue;
            }
            if (MoveValidator::isValidMove(attacker, i, j, kingRow, kingCol, board)) {
                return true;
            }
        }
    }
    return false;
}