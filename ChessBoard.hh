#ifndef _CHESSBOARD_H__
#define _CHESSBOARD_H__

#include "ChessPiece.hh"
#include "Chess.h"
#include <list>
#include <vector>
#include <sstream>

namespace Student
{
    class ChessBoard
    {
    private:
        int numRows = 0;
        int numCols = 0;
        int blackKingRow = -1;
        int whiteKingColumn = -1;
        int blackKingColumn = -1;
        int whiteKingRow = -1;
        Color turn = White;
        /**
         * @brief
         * A 2D vector of pointers to ChessPiece objects.
         * board.at(row) returns the entire row.
         * board.at(row).at(col) returns a pointer to a ChessPiece object.
         * *(board.at(row).at(col)) returns the ChessPiece object itself.
         */
        std::vector<std::vector<ChessPiece *>> board;

    public:
        /**
         * @brief
         * Allocates memory on the heap for the board.
         * Remember to initialise all pointers to nullptr.
         * @param numRow
         * Number of rows of the chess board.
         * @param numCol
         * Number of columns of the chessboard
         */
        ChessBoard(int numRow, int numCol);

        /**
         * @return
         * Number of rows in chess board.
         */
        int getNumRows() { return numRows; }

        int getBKRow() { return blackKingRow; }
        int getWKRow() { return whiteKingRow; }
        int getWKColumn() { return whiteKingColumn; }
        int getBKColumn() { return blackKingColumn; }

        /**
         * @return
         * Number of columns in chess board.
         */
        int getNumCols() { return numCols; }

        /**
         * @brief
         * Default destructor for ChessBoard.
         * Deallocates memory for all pieces on the board.
         */
        virtual ~ChessBoard();

        /**
         * @return
         * Pointer to a piece.
         */
        ChessPiece *getPiece(int r, int c) { return board.at(r).at(c); }

        /**
         * @brief
         * Allocates memory for a new chess piece and assigns its
         * address to the corresponding pointer in the 'board' variable.
         * Remove any existing piece first before adding the new piece.
         * @param col
         * Color of the piece to be created.
         * @param ty
         * Type of the piece to be created.
         * @param startRow
         * Starting row of the piece to be created.
         * @param startColumn
         * Starting column of the piece to be created.
         */
        void createChessPiece(Color col, Type ty, int startRow, int startColumn);

        /**
         * @brief
         * Performs the move if the move is valid.
         * Account for the turn, staying within bounds and validity of the move.
         * This function is only needed for Part 2 and Part 3.
         * You can define a dummy implementation for Part 1 to get the code to compile.
         * @param fromRow
         * The row of the piece to be moved.
         * @param fromColumn
         * The column of the piece to be moved.
         * @param toRow
         * The row of the destination position.
         * @param toColumn
         * The column of the destination position.
         * @return
         * A boolean indicating whether move was executed successfully.
         */
        bool movePiece(int fromRow, int fromColumn, int toRow, int toColumn);

        /**
         * @brief
         * Checks if a move is valid without accounting for turns.
         * @param fromRow
         * The row of the piece to be moved.
         * @param fromColumn
         * The column of the piece to be moved.
         * @param toRow
         * The row of the destination position.
         * @param toColumn
         * The column of the destination position.
         * @return
         * Returns true if move may be executed without accounting for turn.
         */
        bool isValidMove(int fromRow, int fromColumn, int toRow, int toColumn);
        bool isValidMoveModified(int fromRow, int fromColumn, int toRow, int toColumn);
        bool willItRemoveCheck(int row, int column, Color col, Type typ);

        /**
         * @brief
         * Checks if the piece at a position is under threat.
         * This function is only needed for Part 2 and Part 3.
         * You can define a dummy implementation for Part 1 to get the code to compile.
         * @param row
         * Row of piece being checked.
         * @param column
         * Column of piece being checked.
         * @return
         * Returns true if a piece exists at the stated position, and an opponent
         * piece may move to the position.
         */
        bool isPieceUnderThreat(int row, int column);

        bool wouldKingBeUnderThreat(int row, int column, Color color);

        /**
         * @brief
         * Returns an output string stream displaying the layout of the board.
         * An ostringstream is used to automatically handle formatting of integers
         * and special characters into their string representations.
         * @return
         * An output stream containing the full board layout.
         */
        std::ostringstream displayBoard();

        /** STUDENT FUNCTION
         * @brief
         * Checks if a position on the board is empty.
         * @param row
         * The row of the position to be checked.
         * @param column
         * The column of the position to be checked.
         * @return
         * Returns true if the position is empty.
         */
        bool isEmpty(int row, int column) const;
    };
}

#endif