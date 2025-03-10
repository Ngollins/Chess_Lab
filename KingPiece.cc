
// king piece class

#include "KingPiece.hh"
#include "ChessBoard.hh"
#include <iostream>

using namespace Student;

KingPiece::KingPiece(ChessBoard &board, Color color, int row, int column) : ChessPiece(board, color, row, column) 
{ 
    this->type = King; 
}

bool KingPiece::canMoveToLocation(int row, int column) 
{
        if((this -> getColumn() - column) > 1 || (this -> getColumn() - column) < -1 || ((this -> getRow()) - row) > 1 || (this -> getRow() - row) < -1) //Illegal movement
    {
        //std::cout << this -> getColumn() - column << " " <<  row << std::endl;
        return false;
    }
    if(board.wouldKingBeUnderThreat(row, column, this -> getColor())) //Moving king puts himself in check
    {
        //std::cout << "OrHere" << std::endl;
        return false;
    }
    //std::cout << "Here" << std::endl;
    return true;

    //Bad move cases: 

    //If king is in check, then no other move can occur

//Moving the king and putting him in check : wouldKingBeUnderThreat
    //moving another piece which puts the king in check : temporarily store piece, declare it's spot as null, run isUnderThreat, if not, put piece back into place
    //^^this requires having global black & white king int rows and columns which is chill
//moving beyond the bounds of the board
//illegal king movement (or moving on top of own pieces)
}

bool KingPiece::canMoveToLocationModified(int row, int column) 
{
        if((this -> getColumn() - column) > 1 || (this -> getColumn() - column) < -1 || ((this -> getRow()) - row) > 1 || (this -> getRow() - row) < -1) //Illegal movement
    {
        //std::cout << this -> getColumn() - column << " " <<  row << std::endl;
        return false;
    }
    return true;
}

const char *KingPiece::toString() 
{
    return color == White ? "\u2654" : "\u265A";
}

// #endif