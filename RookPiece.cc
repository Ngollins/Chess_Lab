#include "RookPiece.hh"
#include "ChessBoard.hh"
#include <iostream>

using namespace Student;

RookPiece::RookPiece(ChessBoard &board, Color color, int row, int column) : ChessPiece(board, color, row, column) 
{
    this->type = Rook;
}

bool RookPiece::canMoveToLocation(int row, int column) 
{
    int bkingRow = board.getBKRow();
    int bkingCol = board.getBKColumn();
    int wkingRow = board.getWKRow();
    int wkingCol = board.getWKColumn();
    if((bkingRow != -1 && color == Black && board.isPieceUnderThreat(bkingRow, bkingCol)) || (wkingRow != -1 && color == White && board.isPieceUnderThreat(wkingRow, wkingCol)))
    {
        //std::cout << "Better not" << std::endl;
        if(!(board.willItRemoveCheck(row, column, this -> getColor(), this -> getType())))
        {
            //std::cout << "Be there" << std::endl;
            return false;
        }
    }
    if (this->getRow() != row && this->getColumn() != column) return false; // can only move in a straight line

    // horizontal movement
    if (this->getRow() == row) {
        int step = (column > this->getColumn()) ? 1 : -1;
        for (int col = this->getColumn() + step; col != column; col += step) {
            if (!board.isEmpty(this->getRow(), col)) return false;
        }
    }

    // vertical movement
    if (this->getColumn() == column) {
        int step = (row > this->getRow()) ? 1 : -1;
        for (int r = this->getRow() + step; r != row; r += step) {
            if (!board.isEmpty(r, this->getColumn())) return false;
        }
    }

    // else
    return true;
}

bool RookPiece::canMoveToLocationModified(int row, int column) 
{
    if (this->getRow() != row && this->getColumn() != column) return false; // can only move in a straight line

    // horizontal movement
    if (this->getRow() == row) {
        int step = (column > this->getColumn()) ? 1 : -1;
        for (int col = this->getColumn() + step; col != column; col += step) {
            if (!board.isEmpty(this->getRow(), col)) return false;
        }
    }

    // vertical movement
    if (this->getColumn() == column) {
        int step = (row > this->getRow()) ? 1 : -1;
        for (int r = this->getRow() + step; r != row; r += step) {
            if (!board.isEmpty(r, this->getColumn())) return false;
        }
    }

    // else
    return true;
}

const char *RookPiece::toString() 
{
    return color == White ? "\u2656" : "\u265C";
}