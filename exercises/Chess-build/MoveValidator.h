#ifndef MOVEVALIDATOR_H
#define MOVEVALIDATOR_H

#include <optional>
#include <vector>

enum Piece {
    EMPTY,
    WHITE_PAWN, WHITE_ROOK, WHITE_KNIGHT, WHITE_BISHOP, WHITE_QUEEN, WHITE_KING,
    BLACK_PAWN, BLACK_ROOK, BLACK_KNIGHT, BLACK_BISHOP, BLACK_QUEEN, BLACK_KING
};

enum class Color {
    White,
    Black
};

enum class PieceType {
    Pawn,
    Rook,
    Knight,
    Bishop,
    Queen,
    King
};

struct Position {
    int row = -1;
    int col = -1;

    bool operator==(const Position& other) const {
        return row == other.row && col == other.col;
    }

    bool operator!=(const Position& other) const {
        return !(*this == other);
    }
};

struct CastlingRights {
    bool whiteKingSide = true;
    bool whiteQueenSide = true;
    bool blackKingSide = true;
    bool blackQueenSide = true;
};

struct Move {
    Position from;
    Position to;
    Piece promotion = EMPTY;
    bool isEnPassant = false;
    bool isCastling = false;
    bool isDoublePawnPush = false;
};

struct GameState {
    std::vector<std::vector<Piece>> board;
    bool whiteToMove = true;
    CastlingRights castlingRights;
    std::optional<Position> enPassantTarget;
};

class MoveValidator {
public:
    static bool isInsideBoard(const Position& position);
    static bool isWhitePiece(Piece piece);
    static bool isBlackPiece(Piece piece);
    static bool isSameColor(Piece first, Piece second);
    static Color getPieceColor(Piece piece);
    static PieceType getPieceType(Piece piece);
    static Piece makePiece(Color color, PieceType type);
    static std::optional<Position> findKing(const std::vector<std::vector<Piece>>& board, Color color);
    static bool isSquareAttacked(const std::vector<std::vector<Piece>>& board, const Position& target, Color attackingColor);
    static std::vector<Move> getLegalMovesForPiece(const GameState& state, const Position& from);
    static std::vector<Move> getAllLegalMoves(const GameState& state, Color color);
    static GameState applyMove(const GameState& state, const Move& move);

private:
    static std::vector<Move> getPseudoLegalMovesForPiece(const GameState& state, const Position& from);
    static bool isMoveLeavingKingInCheck(const GameState& state, const Move& move, Color movingColor);
    static void addPromotionMoves(std::vector<Move>& moves, const Position& from, const Position& to, bool whitePiece);
    static void addSlidingMoves(std::vector<Move>& moves,
                                const GameState& state,
                                const Position& from,
                                const std::vector<Position>& directions);
};

#endif
