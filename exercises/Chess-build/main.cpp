#include <algorithm>
#include <cctype>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

#include "CheckValidator.h"
#include "MoveValidator.h"

namespace {
std::string toUpper(std::string value) {
    std::transform(value.begin(), value.end(), value.begin(), [](unsigned char ch) {
        return static_cast<char>(std::toupper(ch));
    });
    return value;
}

std::optional<PieceType> parsePieceType(const std::string& token) {
    const std::string upper = toUpper(token);
    if (upper == "PA") {
        return PieceType::Pawn;
    }
    if (upper == "RO") {
        return PieceType::Rook;
    }
    if (upper == "KN") {
        return PieceType::Knight;
    }
    if (upper == "BI") {
        return PieceType::Bishop;
    }
    if (upper == "QU") {
        return PieceType::Queen;
    }
    if (upper == "KI") {
        return PieceType::King;
    }
    return std::nullopt;
}

std::string pieceCode(PieceType type) {
    switch (type) {
        case PieceType::Pawn:
            return "PA";
        case PieceType::Rook:
            return "RO";
        case PieceType::Knight:
            return "KN";
        case PieceType::Bishop:
            return "BI";
        case PieceType::Queen:
            return "QU";
        case PieceType::King:
            return "KI";
    }

    return "??";
}

std::string pieceSymbol(Piece piece) {
    switch (piece) {
        case WHITE_PAWN:
            return "♙";
        case WHITE_ROOK:
            return "♖";
        case WHITE_KNIGHT:
            return "♘";
        case WHITE_BISHOP:
            return "♗";
        case WHITE_QUEEN:
            return "♕";
        case WHITE_KING:
            return "♔";
        case BLACK_PAWN:
            return "♟";
        case BLACK_ROOK:
            return "♜";
        case BLACK_KNIGHT:
            return "♞";
        case BLACK_BISHOP:
            return "♝";
        case BLACK_QUEEN:
            return "♛";
        case BLACK_KING:
            return "♚";
        case EMPTY:
        default:
            return ".";
    }
}

std::optional<Position> parseSquare(const std::string& token) {
    const std::string upper = toUpper(token);
    if (upper.size() != 2) {
        return std::nullopt;
    }

    if (upper[0] < 'A' || upper[0] > 'H' || upper[1] < '1' || upper[1] > '8') {
        return std::nullopt;
    }

    return Position{upper[1] - '1', upper[0] - 'A'};
}

std::string squareToString(const Position& square) {
    std::string value;
    value += static_cast<char>('A' + square.col);
    value += static_cast<char>('1' + square.row);
    return value;
}

std::string playerName(Color color) {
    return color == Color::White ? "Белые" : "Черные";
}

std::string playerNameLower(Color color) {
    return color == Color::White ? "белые" : "черные";
}

std::string describeMove(const Move& move, Piece movingPiece) {
    std::string notation = pieceCode(MoveValidator::getPieceType(movingPiece)) + " " +
                           squareToString(move.from) + " " + squareToString(move.to);

    if (move.promotion != EMPTY) {
        notation += " =" + pieceCode(MoveValidator::getPieceType(move.promotion));
    }

    if (move.isCastling) {
        notation += move.to.col == 6 ? " (O-O)" : " (O-O-O)";
    } else if (move.isEnPassant) {
        notation += " e.p.";
    }

    return notation;
}

std::vector<std::string> tokenize(const std::string& line) {
    std::vector<std::string> tokens;
    std::istringstream stream(line);
    std::string token;
    while (stream >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

std::string joinStrings(std::vector<std::string> values) {
    std::sort(values.begin(), values.end());
    values.erase(std::unique(values.begin(), values.end()), values.end());

    std::ostringstream stream;
    for (std::size_t i = 0; i < values.size(); ++i) {
        if (i != 0) {
            stream << ", ";
        }
        stream << values[i];
    }
    return stream.str();
}

struct ParsedInput {
    std::optional<PieceType> requestedPieceType;
    std::optional<Position> from;
    std::optional<Position> to;
    std::optional<PieceType> promotionType;
    bool shortCastle = false;
    bool longCastle = false;
    bool help = false;
    bool quit = false;
};

std::optional<ParsedInput> parseInput(const std::string& line, std::string& error) {
    const std::vector<std::string> tokens = tokenize(line);
    if (tokens.empty()) {
        error = "Пустая команда. Введите ход или команду help.";
        return std::nullopt;
    }

    if (tokens.size() == 1) {
        const std::string token = toUpper(tokens[0]);
        if (token == "HELP") {
            ParsedInput result;
            result.help = true;
            return result;
        }

        if (token == "QUIT" || token == "EXIT") {
            ParsedInput result;
            result.quit = true;
            return result;
        }

        if (token == "O-O" || token == "0-0") {
            ParsedInput result;
            result.shortCastle = true;
            return result;
        }

        if (token == "O-O-O" || token == "0-0-0") {
            ParsedInput result;
            result.longCastle = true;
            return result;
        }

        error = "Непонятная команда. Используйте help для подсказки.";
        return std::nullopt;
    }

    ParsedInput result;

    if (tokens.size() == 2) {
        if (const std::optional<PieceType> type = parsePieceType(tokens[0])) {
            result.requestedPieceType = type;
            result.to = parseSquare(tokens[1]);
        } else {
            result.from = parseSquare(tokens[0]);
            result.to = parseSquare(tokens[1]);
        }
    } else if (tokens.size() == 3) {
        if (const std::optional<PieceType> type = parsePieceType(tokens[0])) {
            result.requestedPieceType = type;
            result.from = parseSquare(tokens[1]);
            result.to = parseSquare(tokens[2]);
        } else {
            result.from = parseSquare(tokens[0]);
            result.to = parseSquare(tokens[1]);
            result.promotionType = parsePieceType(tokens[2]);
        }
    } else if (tokens.size() == 4) {
        result.requestedPieceType = parsePieceType(tokens[0]);
        result.from = parseSquare(tokens[1]);
        result.to = parseSquare(tokens[2]);
        result.promotionType = parsePieceType(tokens[3]);
    } else {
        error = "Слишком много частей в команде. Используйте help для примеров.";
        return std::nullopt;
    }

    if (!result.to && !result.shortCastle && !result.longCastle) {
        error = "Не удалось разобрать координаты хода.";
        return std::nullopt;
    }

    if (tokens.size() >= 3 && parsePieceType(tokens[0]) && !result.requestedPieceType) {
        error = "Не удалось распознать тип фигуры.";
        return std::nullopt;
    }

    if ((tokens.size() == 3 && !parsePieceType(tokens[0]) && !result.promotionType) ||
        (tokens.size() == 4 && !result.promotionType)) {
        error = "Некорректная фигура для превращения пешки.";
        return std::nullopt;
    }

    return result;
}
}

class ChessGame {
public:
    ChessGame() : state_(createInitialState()) {}

    void run() {
        printHelp();

        while (true) {
            printBoard();
            if (!statusMessage_.empty()) {
                std::cout << statusMessage_ << '\n';
            }

            const Color currentColor = state_.whiteToMove ? Color::White : Color::Black;
            if (CheckValidator::isKingInCheck(state_, currentColor)) {
                std::cout << playerName(currentColor) << " под шахом.\n";
            }

            std::cout << playerName(currentColor) << ", введите ход: ";
            std::string line;
            if (!std::getline(std::cin, line)) {
                break;
            }

            const bool shouldContinue = processInput(line);
            if (gameOver_) {
                printBoard();
                if (!statusMessage_.empty()) {
                    std::cout << statusMessage_ << '\n';
                }
                break;
            }

            if (!shouldContinue) {
                if (!statusMessage_.empty()) {
                    std::cout << '\n' << statusMessage_ << '\n';
                }
                break;
            }
        }
    }

private:
    GameState state_;
    std::string statusMessage_;
    bool gameOver_ = false;

    static GameState createInitialState() {
        GameState state;
        state.board.assign(8, std::vector<Piece>(8, EMPTY));

        for (int col = 0; col < 8; ++col) {
            state.board[1][col] = WHITE_PAWN;
            state.board[6][col] = BLACK_PAWN;
        }

        state.board[0][0] = WHITE_ROOK;
        state.board[0][1] = WHITE_KNIGHT;
        state.board[0][2] = WHITE_BISHOP;
        state.board[0][3] = WHITE_QUEEN;
        state.board[0][4] = WHITE_KING;
        state.board[0][5] = WHITE_BISHOP;
        state.board[0][6] = WHITE_KNIGHT;
        state.board[0][7] = WHITE_ROOK;

        state.board[7][0] = BLACK_ROOK;
        state.board[7][1] = BLACK_KNIGHT;
        state.board[7][2] = BLACK_BISHOP;
        state.board[7][3] = BLACK_QUEEN;
        state.board[7][4] = BLACK_KING;
        state.board[7][5] = BLACK_BISHOP;
        state.board[7][6] = BLACK_KNIGHT;
        state.board[7][7] = BLACK_ROOK;

        return state;
    }

    void printHelp() const {
        std::cout << "Форматы хода:\n"
                  << "  E2 E4      - ход из клетки в клетку\n"
                  << "  PA E2 E4   - то же, но с указанием фигуры\n"
                  << "  QU H4      - выбрать фигуру по типу и конечной клетке\n"
                  << "  E7 E8 QU   - превращение пешки\n"
                  << "  O-O / O-O-O - рокировка\n"
                  << "Команды: help, quit\n\n";
    }

    void printBoard() const {
        std::cout << "\n    A  B  C  D  E  F  G  H\n";
        std::cout << "  +--+--+--+--+--+--+--+--+\n";

        for (int row = 7; row >= 0; --row) {
            std::cout << row + 1 << " |";
            for (int col = 0; col < 8; ++col) {
                std::cout << pieceSymbol(state_.board[row][col]) << ' ' << '|';
            }
            std::cout << ' ' << row + 1 << '\n';
            std::cout << "  +--+--+--+--+--+--+--+--+\n";
        }

        std::cout << "    A  B  C  D  E  F  G  H\n\n";
    }

    bool processInput(const std::string& line) {
        std::string error;
        const std::optional<ParsedInput> input = parseInput(line, error);
        if (!input) {
            statusMessage_ = error;
            return true;
        }

        if (input->help) {
            statusMessage_.clear();
            printHelp();
            return true;
        }

        if (input->quit) {
            statusMessage_ = "Игра завершена пользователем.";
            return false;
        }

        const std::optional<Move> resolvedMove = resolveMove(*input, error);
        if (!resolvedMove) {
            statusMessage_ = error;
            return true;
        }

        const Color movingColor = state_.whiteToMove ? Color::White : Color::Black;
        const Piece movingPiece = state_.board[resolvedMove->from.row][resolvedMove->from.col];
        const std::string moveNotation = describeMove(*resolvedMove, movingPiece);

        state_ = MoveValidator::applyMove(state_, *resolvedMove);

        if (CheckValidator::isCheckmate(state_, state_.whiteToMove ? Color::White : Color::Black)) {
            gameOver_ = true;
            statusMessage_ = "Мат. Победили " + playerName(movingColor) + ". Последний ход: " + moveNotation;
            return true;
        }

        if (CheckValidator::isStalemate(state_, state_.whiteToMove ? Color::White : Color::Black)) {
            gameOver_ = true;
            statusMessage_ = "Пат. Ничья. Последний ход: " + moveNotation;
            return true;
        }

        if (CheckValidator::isKingInCheck(state_, state_.whiteToMove ? Color::White : Color::Black)) {
            statusMessage_ = playerName(movingColor) + " сделали ход " + moveNotation + ". Шах.";
        } else {
            statusMessage_ = playerName(movingColor) + " сделали ход " + moveNotation + ".";
        }

        return true;
    }

    std::optional<Move> resolveMove(const ParsedInput& input, std::string& error) const {
        const Color currentColor = state_.whiteToMove ? Color::White : Color::Black;
        const std::vector<Move> allMoves = MoveValidator::getAllLegalMoves(state_, currentColor);

        if (input.from) {
            const Piece piece = state_.board[input.from->row][input.from->col];
            if (piece == EMPTY) {
                error = "На клетке " + squareToString(*input.from) + " нет фигуры.";
                return std::nullopt;
            }

            if (MoveValidator::getPieceColor(piece) != currentColor) {
                error = "Сейчас ходят " + playerNameLower(currentColor) + ".";
                return std::nullopt;
            }

            if (input.requestedPieceType && MoveValidator::getPieceType(piece) != *input.requestedPieceType) {
                error = "На клетке " + squareToString(*input.from) + " стоит другая фигура.";
                return std::nullopt;
            }
        }

        std::vector<Move> candidates;
        for (const Move& move : allMoves) {
            if (input.shortCastle && (!move.isCastling || move.to.col != 6)) {
                continue;
            }

            if (input.longCastle && (!move.isCastling || move.to.col != 2)) {
                continue;
            }

            if (input.to && move.to != *input.to) {
                continue;
            }

            if (input.from && move.from != *input.from) {
                continue;
            }

            const Piece movingPiece = state_.board[move.from.row][move.from.col];
            if (input.requestedPieceType && MoveValidator::getPieceType(movingPiece) != *input.requestedPieceType) {
                continue;
            }

            if (input.promotionType) {
                if (move.promotion == EMPTY || MoveValidator::getPieceType(move.promotion) != *input.promotionType) {
                    continue;
                }
            }

            candidates.push_back(move);
        }

        if (!input.promotionType) {
            std::vector<Move> queenPromotions;
            for (const Move& move : candidates) {
                if (move.promotion != EMPTY && MoveValidator::getPieceType(move.promotion) == PieceType::Queen) {
                    queenPromotions.push_back(move);
                }
            }
            if (!queenPromotions.empty()) {
                candidates = queenPromotions;
            }
        }

        if (candidates.empty()) {
            if (input.from) {
                std::vector<std::string> availableSquares;
                for (const Move& move : MoveValidator::getLegalMovesForPiece(state_, *input.from)) {
                    availableSquares.push_back(squareToString(move.to));
                }

                if (!availableSquares.empty()) {
                    error = "Нелегальный ход. Для " + squareToString(*input.from) +
                            " доступны: " + joinStrings(availableSquares) + '.';
                } else {
                    error = "У выбранной фигуры нет допустимых ходов.";
                }
            } else if (input.requestedPieceType && input.to) {
                error = "Ни одна фигура " + pieceCode(*input.requestedPieceType) +
                        " не может пойти на " + squareToString(*input.to) + '.';
            } else {
                error = "Такой ход сейчас невозможен.";
            }
            return std::nullopt;
        }

        if (candidates.size() > 1) {
            std::vector<std::string> sources;
            for (const Move& move : candidates) {
                sources.push_back(squareToString(move.from));
            }

            error = "Ход неоднозначен. Уточните исходную клетку: " + joinStrings(sources) + '.';
            return std::nullopt;
        }

        return candidates.front();
    }
};

int main() {
    ChessGame game;
    game.run();
    return 0;
}
