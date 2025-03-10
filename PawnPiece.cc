#include "PawnPiece.hh"
#include "ChessBoard.hh"

using namespace Student;

PawnPiece::PawnPiece(ChessBoard &board, Color color, int row, int column) : ChessPiece(board, color, row, column) 
{
    this->type = Pawn;
}

bool PawnPiece::canMoveToLocation(int row, int column) {
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
    int direction = (color == Color::White) ? -1 : 1; // White moves up, Black moves down
    int startRow = (color == Color::White) ? board.getNumRows() - 2 : 1;

    // Check if pawn is moving forward in the same column
    if (this->getColumn() == column) {
        // Normal one-step forward move
        if (this->getRow() + direction == row && board.isEmpty(row, column)) {
            return true;
        }
        // Initial two-step move
        if (this->getRow() == startRow && this->getRow() + 2 * direction == row &&
            board.isEmpty(row, column) && board.isEmpty(this->getRow() + direction, column)) {
            return true;
        }
    }

    // Check diagonal capture
    if (abs(this->getColumn() - column) == 1 && this->getRow() + direction == row) {
        if (!board.isEmpty(row, column) && board.getPiece(row, column)->getColor() != this->getColor()) {
            return true;
        }
    }

    return false;
}


bool PawnPiece::canMoveToLocationModified(int row, int column) {
    int direction = (color == Color::White) ? -1 : 1; // White moves up, Black moves down
    int startRow = (color == Color::White) ? board.getNumRows() - 2 : 1;

    // Check if pawn is moving forward in the same column
    if (this->getColumn() == column) {
        // Normal one-step forward move
        if (this->getRow() + direction == row && board.isEmpty(row, column)) {
            return true;
        }
        // Initial two-step move
        if (this->getRow() == startRow && this->getRow() + 2 * direction == row &&
            board.isEmpty(row, column) && board.isEmpty(this->getRow() + direction, column)) {
            return true;
        }
    }

    // Check diagonal capture
    if (abs(this->getColumn() - column) == 1 && this->getRow() + direction == row) {
        if (!board.isEmpty(row, column) && board.getPiece(row, column)->getColor() != this->getColor()) {
            return true;
        }
    }

    return false;
}

const char *PawnPiece::toString() 
{
    return color == White ? "\u2659" : "\u265F";
}