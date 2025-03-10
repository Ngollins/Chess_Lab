#include "BishopPiece.hh"
#include "ChessBoard.hh"

using namespace Student;

// constructor for BishopPiece
BishopPiece::BishopPiece(ChessBoard &board, Color color, int row, int column) : ChessPiece(board, color, row, column) 
{
    this->type = Bishop;
}

bool BishopPiece::canMoveToLocation(int row, int column) 
{
    int bkingRow = board.getBKRow();
    int bkingCol = board.getBKColumn();
    int wkingRow = board.getWKRow();
    int wkingCol = board.getWKColumn();
    if((bkingRow != -1 && color == Black && board.isPieceUnderThreat(bkingRow, bkingCol)) || (wkingRow != -1 && color == White && board.isPieceUnderThreat(wkingRow, wkingCol)))
    {
        if(!(board.willItRemoveCheck(row, column, this -> getColor(), this -> getType())))
        {
            return false;
        }
    }
    if (abs(row - this->getRow()) != abs(column - this->getColumn())) {
        return false;   // can only move diagonally
    }

    int rowStep = (row > this->getRow()) ? 1 : -1;
    int colStep = (column > this->getColumn()) ? 1 : -1;

    for (int r = this->getRow() + rowStep, c = this->getColumn() + colStep; r != row; r += rowStep, c += colStep) {
        if (!board.isEmpty(r, c)) {
            return false;
        }
    }

    return true;
}

bool BishopPiece::canMoveToLocationModified(int row, int column) 
{
    if (abs(row - this->getRow()) != abs(column - this->getColumn())) {
        return false;   // can only move diagonally
    }

    int rowStep = (row > this->getRow()) ? 1 : -1;
    int colStep = (column > this->getColumn()) ? 1 : -1;

    for (int r = this->getRow() + rowStep, c = this->getColumn() + colStep; r != row; r += rowStep, c += colStep) {
        if (!board.isEmpty(r, c)) {
            return false;
        }
    }

    return true;
}

const char *BishopPiece::toString() 
{
    return color == White ? "\u2657" : "\u265D";
}