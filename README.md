# Console-Based Chess Game in C++
## Overview
This project is a fully functional chess game implemented in C++, playable entirely through a console interface. The game focuses on enforcing the core rules of chess, including move validation for all pieces and detection of check conditions. By emphasizing game logic over graphics, the project showcases the use of object-oriented design in a complex system.

## Features
Object-Oriented Design: Each chess piece (King, Queen, Rook, Bishop, Knight, and Pawn) is represented as a class derived from a base ChessPiece class. This modular design makes the code easy to extend and maintain.
Move Validation: The game enforces proper movement for all pieces, ensuring that no invalid moves can be made. For example, rooks can only move in straight lines, bishops diagonally, and pawns have special rules for initial two-square moves and capturing.
Check Detection: The game constantly checks for whether a move puts the player's own King in check. If a move leaves the King in check, the game deems it invalid, adding a critical layer of strategy.
Text-Based Input/Output: The board is displayed in an 8x8 grid, with each piece represented by initials (e.g., "WP" for White Pawn, "BK" for Black King). Moves are entered using standard chess notation (e.g., "e2 to e4").
## How to Play
After launching the game, the chessboard will be displayed with pieces arranged in their starting positions.
Players take turns entering their moves in the format start_position end_position (e.g., e2 e4 to move a White Pawn from e2 to e4).
Invalid moves (such as moving into check or violating piece movement rules) will prompt an error message, and the player will need to enter a valid move.
The game continues until the players decide to stop or a winner is manually declared (checkmate detection will be added in future versions).
## How It Works
Chess Pieces: Each piece type is represented by a separate class (e.g., Pawn, King), and all share common functionality through the ChessPiece base class. Each piece class implements its own movement logic, ensuring that only legal moves are permitted.
Move Simulation: Before a piece is moved, the game simulates the move to check if it leaves the King in check. If the King is put in check by the player's own move, the move is rejected.
Check Detection: The game can detect whether the opponent's King is in check after a move, alerting the players.
## Code Structure
ChessPiece: Base class for all chess pieces, providing common attributes and functions.
Pawn, Rook, Knight, Bishop, Queen, King: Individual classes for each piece, implementing their specific movement rules.
ChessBoard: Manages the board state, handles piece movement, and checks game conditions (e.g., check).
## Future Enhancements
Add checkmate detection and game-ending logic.
Implement advanced rules like castling and en passant.
Potential AI opponent for single-player mode.
## Installation
To run the game, clone this repository and compile the source code using a C++ compiler:

```bash
git clone <repository-url>
cd chess-game
g++ chess_game.cpp -o chess_game
./chess_game
