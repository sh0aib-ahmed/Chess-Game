#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

class ChessPiece {
public:
    string name;
    string color;

    ChessPiece(string name, string color) : name(name), color(color) {}

    virtual bool isValidMove(int startRow, int startCol, int endRow, int endCol, ChessPiece* dest) const = 0;

    bool isOpponent(const ChessPiece* other) const {
        return other != nullptr && other->color != this->color;
    }

    string toString() const {
        if (color == "Black") {
            return "\033[31m" + color.substr(0, 1) + name.substr(0, 1) + "\033[0m"; // Red for black pieces
        }
        else {
            return color.substr(0, 1) + name.substr(0, 1);
        }
    }
};

class King : public ChessPiece {
public:
    King(string color) : ChessPiece("King", color) {}

    bool isValidMove(int startRow, int startCol, int endRow, int endCol, ChessPiece* dest) const override {
        return (abs(startRow - endRow) <= 1 && abs(startCol - endCol) <= 1) && (dest == nullptr || isOpponent(dest));
    }
};

class Queen : public ChessPiece {
public:
    Queen(string color) : ChessPiece("Queen", color) {}

    bool isValidMove(int startRow, int startCol, int endRow, int endCol, ChessPiece* dest) const override {
        return (startRow == endRow || startCol == endCol || abs(startRow - endRow) == abs(startCol - endCol)) &&
            (dest == nullptr || isOpponent(dest));
    }
};

class Rook : public ChessPiece {
public:
    Rook(string color) : ChessPiece("Rook", color) {}

    bool isValidMove(int startRow, int startCol, int endRow, int endCol, ChessPiece* dest) const override {
        return (startRow == endRow || startCol == endCol) && (dest == nullptr || isOpponent(dest));
    }
};

class Bishop : public ChessPiece {
public:
    Bishop(string color) : ChessPiece("Bishop", color) {}

    bool isValidMove(int startRow, int startCol, int endRow, int endCol, ChessPiece* dest) const override {
        return abs(startRow - endRow) == abs(startCol - endCol) && (dest == nullptr || isOpponent(dest));
    }
};

class Knight : public ChessPiece {
public:
    Knight(string color) : ChessPiece("Knight", color) {}

    bool isValidMove(int startRow, int startCol, int endRow, int endCol, ChessPiece* dest) const override {
        return ((abs(startRow - endRow) == 2 && abs(startCol - endCol) == 1) ||
            (abs(startRow - endRow) == 1 && abs(startCol - endCol) == 2)) && (dest == nullptr || isOpponent(dest));
    }
};

class Pawn : public ChessPiece {
public:
    Pawn(string color) : ChessPiece("Pawn", color) {}

    bool isValidMove(int startRow, int startCol, int endRow, int endCol, ChessPiece* dest) const override {
        if (color == "White") {
            if (startCol == endCol && startRow - endRow == 1 && dest == nullptr)
                return true;
            if (startCol == endCol && startRow == 6 && endRow == 4 && dest == nullptr)
                return true;
            if (abs(startCol - endCol) == 1 && startRow - endRow == 1 && isOpponent(dest))
                return true;
        }
        else {
            if (startCol == endCol && endRow - startRow == 1 && dest == nullptr)
                return true;
            if (startCol == endCol && startRow == 1 && endRow == 3 && dest == nullptr)
                return true;
            if (abs(startCol - endCol) == 1 && endRow - startRow == 1 && isOpponent(dest))
                return true;
        }
        return false;
    }
};

class ChessBoard {
private:
    vector<vector<ChessPiece*>> board;

public:
    ChessBoard() {
        board.resize(8, vector<ChessPiece*>(8, nullptr));
        initializeBoard();
    }

    ~ChessBoard() {
        for (auto& row : board) {
            for (auto& piece : row) {
                delete piece;
            }
        }
    }

    void initializeBoard() {
        board[0] = { new Rook("Black"), new Knight("Black"), new Bishop("Black"), new Queen("Black"),
                    new King("Black"), new Bishop("Black"), new Knight("Black"), new Rook("Black") };
        board[1] = { new Pawn("Black"), new Pawn("Black"), new Pawn("Black"), new Pawn("Black"),
                    new Pawn("Black"), new Pawn("Black"), new Pawn("Black"), new Pawn("Black") };

        board[7] = { new Rook("White"), new Knight("White"), new Bishop("White"), new Queen("White"),
                    new King("White"), new Bishop("White"), new Knight("White"), new Rook("White") };
        board[6] = { new Pawn("White"), new Pawn("White"), new Pawn("White"), new Pawn("White"),
                    new Pawn("White"), new Pawn("White"), new Pawn("White"), new Pawn("White") };
    }

    void printBoard() const {
        for (int row = 0; row < 8; ++row) {
            cout << (8 - row) << " ";
            for (int col = 0; col < 8; ++col) {
                if (board[row][col] != nullptr) {
                    cout << board[row][col]->toString() << " ";
                }
                else {
                    cout << ".  ";
                }
            }
            cout << endl;
        }
        cout << "   a  b  c  d  e  f  g  h" << endl;
    }

    // Check if any piece can attack the king
    bool isKingInCheck(string color) {
        int kingRow, kingCol;
        // Find the king's position
        for (int row = 0; row < 8; ++row) {
            for (int col = 0; col < 8; ++col) {
                if (board[row][col] != nullptr && board[row][col]->name == "King" && board[row][col]->color == color) {
                    kingRow = row;
                    kingCol = col;
                    break;
                }
            }
        }
        // Check if any opponent piece can attack the king
        for (int row = 0; row < 8; ++row) {
            for (int col = 0; col < 8; ++col) {
                ChessPiece* piece = board[row][col];
                if (piece != nullptr && piece->color != color) {
                    if (piece->isValidMove(row, col, kingRow, kingCol, board[kingRow][kingCol])) {
                        return true;
                    }
                }
            }
        }
        return false;
    }

    // Simulate a move to check if it results in check
    bool simulateMoveAndCheck(string start, string end, string color) {
        int startRow = 8 - (start[1] - '0');
        int startCol = start[0] - 'a';
        int endRow = 8 - (end[1] - '0');
        int endCol = end[0] - 'a';

        ChessPiece* piece = board[startRow][startCol];
        ChessPiece* dest = board[endRow][endCol];

        // Simulate the move
        board[endRow][endCol] = piece;
        board[startRow][startCol] = nullptr;

        bool kingInCheck = isKingInCheck(color);

        // Undo the move
        board[startRow][startCol] = piece;
        board[endRow][endCol] = dest;

        return kingInCheck;
    }

    void movePiece(string start, string end) {
        int startRow = 8 - (start[1] - '0');
        int startCol = start[0] - 'a';
        int endRow = 8 - (end[1] - '0');
        int endCol = end[0] - 'a';

        ChessPiece* piece = board[startRow][startCol];
        ChessPiece* dest = board[endRow][endCol];

        if (piece != nullptr && piece->isValidMove(startRow, startCol, endRow, endCol, dest)) {
            string playerColor = piece->color;
            if (!simulateMoveAndCheck(start, end, playerColor)) {
                board[endRow][endCol] = piece;
                board[startRow][startCol] = nullptr;

                if (isKingInCheck(piece->color == "White" ? "Black" : "White")) {
                    cout << "Check!" << endl;
                }
            }
            else {
                cout << "Invalid move! Your King would be in check." << endl;
            }
        }
        else {
            cout << "Invalid move!" << endl;
        }
    }
};

int main() {
    ChessBoard board;
    board.printBoard();
    string start, end;

    while (true) {
        cout << "Enter the start position : ";
        cin >> start;
        cout << "Enter the end position : ";
        cin >> end;
        board.movePiece(start, end);
        board.printBoard();
    }
}
