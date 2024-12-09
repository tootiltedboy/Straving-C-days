#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include "MoveValidator.h"
#include "CheckValidator.h"

using namespace std;

// Определение символов для фигур (для вывода)
const string WHITE_PIECES[] = {"♙", "♖", "♘", "♗", "♕", "♔"};
const string BLACK_PIECES[] = {"♟", "♜", "♞", "♝", "♛", "♚"};

class ChessBoard {
private:
    vector<vector<Piece>> board;

public:
    ChessBoard() {
        board.resize(8, vector<Piece>(8, EMPTY));
        initializeBoard();
    }

    void initializeBoard() {
        for (int i = 0; i < 8; i++) {
            board[1][i] = WHITE_PAWN;
            board[6][i] = BLACK_PAWN;
        }
        board[0][0] = board[0][7] = WHITE_ROOK;
        board[0][1] = board[0][6] = WHITE_KNIGHT;
        board[0][2] = board[0][5] = WHITE_BISHOP;
        board[0][3] = WHITE_QUEEN;
        board[0][4] = WHITE_KING;

        board[7][0] = board[7][7] = BLACK_ROOK;
        board[7][1] = board[7][6] = BLACK_KNIGHT;
        board[7][2] = board[7][5] = BLACK_BISHOP;
        board[7][3] = BLACK_QUEEN;
        board[7][4] = BLACK_KING;
    }

    void printBoard() {
        cout << "   A  B  C  D  E  F  G  H" << endl;
        for (int i = 7; i >= 0; i--) {
            cout << i + 1 << " ";
            for (int j = 0; j < 8; j++) {
                cout << "|";
                if (board[i][j] == EMPTY) {
                    cout << "  ";
                } else if (board[i][j] < BLACK_PAWN) {
                    cout << WHITE_PIECES[board[i][j] - 1];
                } else {
                    cout << BLACK_PIECES[board[i][j] - BLACK_PAWN];
                }
            }
            cout << "|" << endl;
            cout << "  ------------------------" << endl;
        }
    }

    bool movePiece(const string& move) {
        if (move.length() < 7) {
            cout << "Неверный формат хода. Используйте формат: KI E2 E4" << endl;
            return false;
        }

        int fromCol = tolower(move[3]) - 'a';
        int fromRow = move[4] - '1';
        int toCol = tolower(move[6]) - 'a';
        int toRow = move[7] - '1';

        if (fromCol < 0 || fromCol >= 8 || fromRow < 0 || fromRow >= 8 ||
            toCol < 0 || toCol >= 8 || toRow < 0 || toRow >= 8) {
            cout << "Некорректные координаты. Повторите ввод." << endl;
            return false;
        }

        Piece piece = board[fromRow][fromCol];
        if (piece == EMPTY) {
            cout << "На клетке " << move.substr(3, 2) << " нет фигуры!" << endl;
            return false;
        }

        if (!MoveValidator::isValidMove(piece, fromRow, fromCol, toRow, toCol, board)) {
            cout << "Неправильный ход для данной фигуры!" << endl;
            return false;
        }

        board[toRow][toCol] = piece;
        board[fromRow][fromCol] = EMPTY;

        Piece king = (piece < BLACK_PAWN) ? WHITE_KING : BLACK_KING;
        int kingRow, kingCol;

        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (board[i][j] == king) {
                    kingRow = i;
                    kingCol = j;
                    break;
                }
            }
        }

        if (CheckValidator::isKingInCheck(king, kingRow, kingCol, board)) {
            cout << "Король находится под шахом! Ход отменен." << endl