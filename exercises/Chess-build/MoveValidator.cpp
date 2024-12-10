#include "MoveValidator.h"

bool MoveValidator::isValidMove(Piece piece, int fromRow, int fromCol, int toRow, int toCol, const std::vector<std::vector<Piece>>& board) {
    int rowDiff = toRow - fromRow;
    int colDiff = toCol - fromCol;

    switch (piece) {
        case WHITE_PAWN:
        case BLACK_PAWN:
            if (piece == WHITE_PAWN) {
                if (rowDiff == 1 && colDiff == 0 && board[toRow][toCol] == EMPTY) return true;
                if (rowDiff == 1 && std::abs(colDiff) == 1 && board[toRow][toCol] >= BLACK_PAWN) return true;
            } else if (piece == BLACK_PAWN) {
                if (rowDiff == -1 && colDiff == 0 && board[toRow][toCol] == EMPTY) return true;
                if (rowDiff == -1 && std::abs(colDiff) == 1 && board[toRow][toCol] < BLACK_PAWN && board[toRow][toCol] != EMPTY) return true;
            }
        break;

        case WHITE_ROOK:
        case BLACK_ROOK:
            if (rowDiff == 0 || colDiff == 0) return true;
        break;
        case WHITE_KNIGHT:
        case BLACK_KNIGHT:
            if ((std::abs(rowDiff) == 2 && std::abs(colDiff) == 1) || (std::abs(rowDiff) == 1 && std::abs(colDiff) == 2)) return true;
        break;

        case WHITE_BISHOP:
        case BLACK_BISHOP:
            if (std::abs(rowDiff) == std::abs(colDiff)) return true;
        break;

        case WHITE_QUEEN:
        case BLACK_QUEEN:
            if (std::abs(rowDiff) == std::abs(colDiff) || rowDiff == 0 || colDiff == 0) return true;
        break;

        case WHITE_KING:
        case BLACK_KING:
            if (std::abs(rowDiff) <= 1 && std::abs(colDiff) <= 1) return true;
        break;

        default:
            return false;
    }
    return false;
}