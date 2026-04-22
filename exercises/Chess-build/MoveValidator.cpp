#include "MoveValidator.h"

namespace {
constexpr int BOARD_SIZE = 8;

bool canLandOnSquare(Piece target, Color movingColor) {
    if (target == EMPTY) {
        return true;
    }

    if (MoveValidator::getPieceType(target) == PieceType::King) {
        return false;
    }

    return MoveValidator::getPieceColor(target) != movingColor;
}

Color oppositeColor(Color color) {
    return color == Color::White ? Color::Black : Color::White;
}
}

bool MoveValidator::isInsideBoard(const Position& position) {
    return position.row >= 0 && position.row < BOARD_SIZE &&
           position.col >= 0 && position.col < BOARD_SIZE;
}

bool MoveValidator::isWhitePiece(Piece piece) {
    return piece >= WHITE_PAWN && piece <= WHITE_KING;
}

bool MoveValidator::isBlackPiece(Piece piece) {
    return piece >= BLACK_PAWN && piece <= BLACK_KING;
}

bool MoveValidator::isSameColor(Piece first, Piece second) {
    if (first == EMPTY || second == EMPTY) {
        return false;
    }

    return (isWhitePiece(first) && isWhitePiece(second)) ||
           (isBlackPiece(first) && isBlackPiece(second));
}

Color MoveValidator::getPieceColor(Piece piece) {
    return isWhitePiece(piece) ? Color::White : Color::Black;
}

PieceType MoveValidator::getPieceType(Piece piece) {
    switch (piece) {
        case WHITE_PAWN:
        case BLACK_PAWN:
            return PieceType::Pawn;
        case WHITE_ROOK:
        case BLACK_ROOK:
            return PieceType::Rook;
        case WHITE_KNIGHT:
        case BLACK_KNIGHT:
            return PieceType::Knight;
        case WHITE_BISHOP:
        case BLACK_BISHOP:
            return PieceType::Bishop;
        case WHITE_QUEEN:
        case BLACK_QUEEN:
            return PieceType::Queen;
        case WHITE_KING:
        case BLACK_KING:
            return PieceType::King;
        case EMPTY:
        default:
            return PieceType::Pawn;
    }
}

Piece MoveValidator::makePiece(Color color, PieceType type) {
    if (color == Color::White) {
        switch (type) {
            case PieceType::Pawn:
                return WHITE_PAWN;
            case PieceType::Rook:
                return WHITE_ROOK;
            case PieceType::Knight:
                return WHITE_KNIGHT;
            case PieceType::Bishop:
                return WHITE_BISHOP;
            case PieceType::Queen:
                return WHITE_QUEEN;
            case PieceType::King:
                return WHITE_KING;
        }
    }

    switch (type) {
        case PieceType::Pawn:
            return BLACK_PAWN;
        case PieceType::Rook:
            return BLACK_ROOK;
        case PieceType::Knight:
            return BLACK_KNIGHT;
        case PieceType::Bishop:
            return BLACK_BISHOP;
        case PieceType::Queen:
            return BLACK_QUEEN;
        case PieceType::King:
            return BLACK_KING;
    }

    return EMPTY;
}

std::optional<Position> MoveValidator::findKing(const std::vector<std::vector<Piece>>& board, Color color) {
    const Piece king = makePiece(color, PieceType::King);

    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            if (board[row][col] == king) {
                return Position{row, col};
            }
        }
    }

    return std::nullopt;
}

bool MoveValidator::isSquareAttacked(const std::vector<std::vector<Piece>>& board,
                                     const Position& target,
                                     Color attackingColor) {
    const int pawnRow = target.row + (attackingColor == Color::White ? -1 : 1);
    for (int colOffset : {-1, 1}) {
        Position attacker{pawnRow, target.col + colOffset};
        if (!isInsideBoard(attacker)) {
            continue;
        }

        const Piece expectedPawn = makePiece(attackingColor, PieceType::Pawn);
        if (board[attacker.row][attacker.col] == expectedPawn) {
            return true;
        }
    }

    const Position knightOffsets[] = {
        {2, 1}, {2, -1}, {-2, 1}, {-2, -1},
        {1, 2}, {1, -2}, {-1, 2}, {-1, -2}
    };

    for (const Position& offset : knightOffsets) {
        Position attacker{target.row + offset.row, target.col + offset.col};
        if (!isInsideBoard(attacker)) {
            continue;
        }

        if (board[attacker.row][attacker.col] == makePiece(attackingColor, PieceType::Knight)) {
            return true;
        }
    }

    const Position bishopDirections[] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    for (const Position& direction : bishopDirections) {
        Position current{target.row + direction.row, target.col + direction.col};
        while (isInsideBoard(current)) {
            const Piece piece = board[current.row][current.col];
            if (piece != EMPTY) {
                if (getPieceColor(piece) == attackingColor &&
                    (getPieceType(piece) == PieceType::Bishop || getPieceType(piece) == PieceType::Queen)) {
                    return true;
                }
                break;
            }

            current.row += direction.row;
            current.col += direction.col;
        }
    }

    const Position rookDirections[] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    for (const Position& direction : rookDirections) {
        Position current{target.row + direction.row, target.col + direction.col};
        while (isInsideBoard(current)) {
            const Piece piece = board[current.row][current.col];
            if (piece != EMPTY) {
                if (getPieceColor(piece) == attackingColor &&
                    (getPieceType(piece) == PieceType::Rook || getPieceType(piece) == PieceType::Queen)) {
                    return true;
                }
                break;
            }

            current.row += direction.row;
            current.col += direction.col;
        }
    }

    for (int rowOffset = -1; rowOffset <= 1; ++rowOffset) {
        for (int colOffset = -1; colOffset <= 1; ++colOffset) {
            if (rowOffset == 0 && colOffset == 0) {
                continue;
            }

            Position attacker{target.row + rowOffset, target.col + colOffset};
            if (!isInsideBoard(attacker)) {
                continue;
            }

            if (board[attacker.row][attacker.col] == makePiece(attackingColor, PieceType::King)) {
                return true;
            }
        }
    }

    return false;
}

std::vector<Move> MoveValidator::getLegalMovesForPiece(const GameState& state, const Position& from) {
    if (!isInsideBoard(from)) {
        return {};
    }

    const Piece piece = state.board[from.row][from.col];
    if (piece == EMPTY) {
        return {};
    }

    const Color movingColor = getPieceColor(piece);
    std::vector<Move> legalMoves;

    for (const Move& move : getPseudoLegalMovesForPiece(state, from)) {
        if (!isMoveLeavingKingInCheck(state, move, movingColor)) {
            legalMoves.push_back(move);
        }
    }

    return legalMoves;
}

std::vector<Move> MoveValidator::getAllLegalMoves(const GameState& state, Color color) {
    std::vector<Move> moves;

    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            const Piece piece = state.board[row][col];
            if (piece == EMPTY || getPieceColor(piece) != color) {
                continue;
            }

            const std::vector<Move> pieceMoves = getLegalMovesForPiece(state, Position{row, col});
            moves.insert(moves.end(), pieceMoves.begin(), pieceMoves.end());
        }
    }

    return moves;
}

GameState MoveValidator::applyMove(const GameState& state, const Move& move) {
    GameState nextState = state;
    Piece movingPiece = nextState.board[move.from.row][move.from.col];
    Piece capturedPiece = nextState.board[move.to.row][move.to.col];

    nextState.enPassantTarget.reset();
    nextState.board[move.from.row][move.from.col] = EMPTY;

    if (move.isEnPassant) {
        const int capturedPawnRow = move.to.row + (isWhitePiece(movingPiece) ? -1 : 1);
        capturedPiece = nextState.board[capturedPawnRow][move.to.col];
        nextState.board[capturedPawnRow][move.to.col] = EMPTY;
    }

    nextState.board[move.to.row][move.to.col] = movingPiece;

    if (move.isCastling) {
        const int rookFromCol = move.to.col == 6 ? 7 : 0;
        const int rookToCol = move.to.col == 6 ? 5 : 3;
        nextState.board[move.from.row][rookToCol] = nextState.board[move.from.row][rookFromCol];
        nextState.board[move.from.row][rookFromCol] = EMPTY;
    }

    if (move.promotion != EMPTY) {
        nextState.board[move.to.row][move.to.col] = move.promotion;
    }

    if (getPieceType(movingPiece) == PieceType::King) {
        if (isWhitePiece(movingPiece)) {
            nextState.castlingRights.whiteKingSide = false;
            nextState.castlingRights.whiteQueenSide = false;
        } else {
            nextState.castlingRights.blackKingSide = false;
            nextState.castlingRights.blackQueenSide = false;
        }
    }

    if (getPieceType(movingPiece) == PieceType::Rook) {
        if (move.from == Position{0, 0}) {
            nextState.castlingRights.whiteQueenSide = false;
        } else if (move.from == Position{0, 7}) {
            nextState.castlingRights.whiteKingSide = false;
        } else if (move.from == Position{7, 0}) {
            nextState.castlingRights.blackQueenSide = false;
        } else if (move.from == Position{7, 7}) {
            nextState.castlingRights.blackKingSide = false;
        }
    }

    if (capturedPiece != EMPTY && getPieceType(capturedPiece) == PieceType::Rook) {
        if (move.to == Position{0, 0}) {
            nextState.castlingRights.whiteQueenSide = false;
        } else if (move.to == Position{0, 7}) {
            nextState.castlingRights.whiteKingSide = false;
        } else if (move.to == Position{7, 0}) {
            nextState.castlingRights.blackQueenSide = false;
        } else if (move.to == Position{7, 7}) {
            nextState.castlingRights.blackKingSide = false;
        }
    }

    if (move.isDoublePawnPush) {
        nextState.enPassantTarget = Position{(move.from.row + move.to.row) / 2, move.from.col};
    }

    nextState.whiteToMove = !state.whiteToMove;
    return nextState;
}

std::vector<Move> MoveValidator::getPseudoLegalMovesForPiece(const GameState& state, const Position& from) {
    std::vector<Move> moves;
    const Piece piece = state.board[from.row][from.col];
    const Color movingColor = getPieceColor(piece);

    switch (getPieceType(piece)) {
        case PieceType::Pawn: {
            const int direction = movingColor == Color::White ? 1 : -1;
            const int startRow = movingColor == Color::White ? 1 : 6;
            const int promotionRow = movingColor == Color::White ? 7 : 0;

            const Position oneStep{from.row + direction, from.col};
            if (isInsideBoard(oneStep) && state.board[oneStep.row][oneStep.col] == EMPTY) {
                if (oneStep.row == promotionRow) {
                    addPromotionMoves(moves, from, oneStep, movingColor == Color::White);
                } else {
                    moves.push_back(Move{from, oneStep});
                }

                const Position twoSteps{from.row + 2 * direction, from.col};
                if (from.row == startRow && isInsideBoard(twoSteps) &&
                    state.board[twoSteps.row][twoSteps.col] == EMPTY) {
                    Move move{from, twoSteps};
                    move.isDoublePawnPush = true;
                    moves.push_back(move);
                }
            }

            for (int colOffset : {-1, 1}) {
                const Position target{from.row + direction, from.col + colOffset};
                if (!isInsideBoard(target)) {
                    continue;
                }

                const Piece targetPiece = state.board[target.row][target.col];
                if (targetPiece != EMPTY && canLandOnSquare(targetPiece, movingColor)) {
                    if (target.row == promotionRow) {
                        addPromotionMoves(moves, from, target, movingColor == Color::White);
                    } else {
                        moves.push_back(Move{from, target});
                    }
                    continue;
                }

                if (state.enPassantTarget && target == *state.enPassantTarget) {
                    const Position capturedPawn{from.row, target.col};
                    const Piece adjacentPiece = state.board[capturedPawn.row][capturedPawn.col];
                    if (adjacentPiece != EMPTY &&
                        getPieceType(adjacentPiece) == PieceType::Pawn &&
                        getPieceColor(adjacentPiece) != movingColor) {
                        Move move{from, target};
                        move.isEnPassant = true;
                        moves.push_back(move);
                    }
                }
            }
            break;
        }
        case PieceType::Rook:
            addSlidingMoves(moves, state, from, {{1, 0}, {-1, 0}, {0, 1}, {0, -1}});
            break;
        case PieceType::Bishop:
            addSlidingMoves(moves, state, from, {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}});
            break;
        case PieceType::Queen:
            addSlidingMoves(moves, state, from,
                            {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}});
            break;
        case PieceType::Knight: {
            const Position offsets[] = {
                {2, 1}, {2, -1}, {-2, 1}, {-2, -1},
                {1, 2}, {1, -2}, {-1, 2}, {-1, -2}
            };

            for (const Position& offset : offsets) {
                const Position target{from.row + offset.row, from.col + offset.col};
                if (!isInsideBoard(target)) {
                    continue;
                }

                if (canLandOnSquare(state.board[target.row][target.col], movingColor)) {
                    moves.push_back(Move{from, target});
                }
            }
            break;
        }
        case PieceType::King: {
            for (int rowOffset = -1; rowOffset <= 1; ++rowOffset) {
                for (int colOffset = -1; colOffset <= 1; ++colOffset) {
                    if (rowOffset == 0 && colOffset == 0) {
                        continue;
                    }

                    const Position target{from.row + rowOffset, from.col + colOffset};
                    if (!isInsideBoard(target)) {
                        continue;
                    }

                    if (canLandOnSquare(state.board[target.row][target.col], movingColor)) {
                        moves.push_back(Move{from, target});
                    }
                }
            }

            const Color enemyColor = oppositeColor(movingColor);
            if (movingColor == Color::White && from == Position{0, 4} &&
                !isSquareAttacked(state.board, from, enemyColor)) {
                if (state.castlingRights.whiteKingSide &&
                    state.board[0][5] == EMPTY &&
                    state.board[0][6] == EMPTY &&
                    state.board[0][7] == WHITE_ROOK &&
                    !isSquareAttacked(state.board, Position{0, 5}, enemyColor) &&
                    !isSquareAttacked(state.board, Position{0, 6}, enemyColor)) {
                    Move move{from, Position{0, 6}};
                    move.isCastling = true;
                    moves.push_back(move);
                }

                if (state.castlingRights.whiteQueenSide &&
                    state.board[0][1] == EMPTY &&
                    state.board[0][2] == EMPTY &&
                    state.board[0][3] == EMPTY &&
                    state.board[0][0] == WHITE_ROOK &&
                    !isSquareAttacked(state.board, Position{0, 3}, enemyColor) &&
                    !isSquareAttacked(state.board, Position{0, 2}, enemyColor)) {
                    Move move{from, Position{0, 2}};
                    move.isCastling = true;
                    moves.push_back(move);
                }
            }

            if (movingColor == Color::Black && from == Position{7, 4} &&
                !isSquareAttacked(state.board, from, enemyColor)) {
                if (state.castlingRights.blackKingSide &&
                    state.board[7][5] == EMPTY &&
                    state.board[7][6] == EMPTY &&
                    state.board[7][7] == BLACK_ROOK &&
                    !isSquareAttacked(state.board, Position{7, 5}, enemyColor) &&
                    !isSquareAttacked(state.board, Position{7, 6}, enemyColor)) {
                    Move move{from, Position{7, 6}};
                    move.isCastling = true;
                    moves.push_back(move);
                }

                if (state.castlingRights.blackQueenSide &&
                    state.board[7][1] == EMPTY &&
                    state.board[7][2] == EMPTY &&
                    state.board[7][3] == EMPTY &&
                    state.board[7][0] == BLACK_ROOK &&
                    !isSquareAttacked(state.board, Position{7, 3}, enemyColor) &&
                    !isSquareAttacked(state.board, Position{7, 2}, enemyColor)) {
                    Move move{from, Position{7, 2}};
                    move.isCastling = true;
                    moves.push_back(move);
                }
            }
            break;
        }
    }

    return moves;
}

bool MoveValidator::isMoveLeavingKingInCheck(const GameState& state, const Move& move, Color movingColor) {
    const GameState nextState = applyMove(state, move);
    const std::optional<Position> kingPosition = findKing(nextState.board, movingColor);

    if (!kingPosition) {
        return true;
    }

    return isSquareAttacked(nextState.board, *kingPosition, oppositeColor(movingColor));
}

void MoveValidator::addPromotionMoves(std::vector<Move>& moves,
                                      const Position& from,
                                      const Position& to,
                                      bool whitePiece) {
    const Color color = whitePiece ? Color::White : Color::Black;
    for (PieceType type : {PieceType::Queen, PieceType::Rook, PieceType::Bishop, PieceType::Knight}) {
        Move move{from, to};
        move.promotion = makePiece(color, type);
        moves.push_back(move);
    }
}

void MoveValidator::addSlidingMoves(std::vector<Move>& moves,
                                    const GameState& state,
                                    const Position& from,
                                    const std::vector<Position>& directions) {
    const Color movingColor = getPieceColor(state.board[from.row][from.col]);

    for (const Position& direction : directions) {
        Position current{from.row + direction.row, from.col + direction.col};
        while (isInsideBoard(current)) {
            const Piece targetPiece = state.board[current.row][current.col];
            if (targetPiece == EMPTY) {
                moves.push_back(Move{from, current});
            } else {
                if (canLandOnSquare(targetPiece, movingColor)) {
                    moves.push_back(Move{from, current});
                }
                break;
            }

            current.row += direction.row;
            current.col += direction.col;
        }
    }
}
