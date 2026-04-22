#include "CheckValidator.h"

namespace {
Color oppositeColor(Color color) {
    return color == Color::White ? Color::Black : Color::White;
}
}

bool CheckValidator::isKingInCheck(const GameState& state, Color color) {
    const std::optional<Position> kingPosition = MoveValidator::findKing(state.board, color);
    if (!kingPosition) {
        return false;
    }

    return MoveValidator::isSquareAttacked(state.board, *kingPosition, oppositeColor(color));
}

bool CheckValidator::isCheckmate(const GameState& state, Color color) {
    return isKingInCheck(state, color) && MoveValidator::getAllLegalMoves(state, color).empty();
}

bool CheckValidator::isStalemate(const GameState& state, Color color) {
    return !isKingInCheck(state, color) && MoveValidator::getAllLegalMoves(state, color).empty();
}
