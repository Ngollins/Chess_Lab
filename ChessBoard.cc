#include "ChessBoard.hh"
#include "PawnPiece.hh"
#include "RookPiece.hh"
#include "BishopPiece.hh"
#include "KingPiece.hh"
#include <iostream>

using Student::ChessBoard;
using namespace Student;

ChessBoard::ChessBoard(int rows, int cols) : numRows(rows), numCols(cols), board(rows, std::vector<ChessPiece*>(cols, nullptr)) {}

ChessBoard::~ChessBoard() {
    for (int r = 0; r < numRows; r++) {
        for (int c = 0; c < numCols; c++) {
            if (board[r][c] != nullptr) {
                delete board[r][c];
                board[r][c] = nullptr;  // set to nullptr to avoid dangling pointer
            }
        }
    }
}

// create chess piece
void ChessBoard::createChessPiece(Color color, Type type, int row, int column) 
{
    ChessPiece *piece = nullptr;
    if (!isEmpty(row, column)) {
        delete board[row][column];
    }

    if (type == Pawn) {
        piece = new PawnPiece(*this, color, row, column);
    } else if (type == Rook) {
        piece = new RookPiece(*this, color, row, column);
    } else if (type == Bishop) {
        piece = new BishopPiece(*this, color, row, column);
    } else if (type == King) {
        piece = new KingPiece(*this, color, row, column);
        if(color == Black)
        {
            blackKingColumn = column;
            blackKingRow = row;
        }
        else
        {
            whiteKingColumn = column;
            whiteKingRow = row;
        }
    }

    board[row][column] = piece;
}


bool ChessBoard::movePiece(int fromRow, int fromColumn, int toRow, int toColumn) 
{
    if (!isValidMove(fromRow, fromColumn, toRow, toColumn)) return false;
    if(board[fromRow][fromColumn]->getColor() != turn) return false; //Check if correct person's move

    //Start procedure to move
    turn = (turn == White ? Black : White); //Change color of the turn
    ChessPiece *piece = board[fromRow][fromColumn];
    if (board[toRow][toColumn] != nullptr) {
        if(board[toRow][toColumn] -> getType() == King)
        {
            if(turn == White)
            {
                whiteKingColumn = -1;
                whiteKingRow = -1;
            }
            else
            {
                blackKingRow = -1;
                blackKingColumn = -1;
            }
        }
        delete board[toRow][toColumn]; //Capture and delete opponents piece
        board[toRow][toColumn] = nullptr;
    }
    piece -> setPosition(toRow, toColumn);
    board[toRow][toColumn] = piece;
    board[fromRow][fromColumn] = nullptr; //Make swap

    if(piece -> getType() == King)
    {
        if(piece -> getColor() == Black)
        {
            blackKingRow = toRow;
            blackKingColumn = toColumn;
        }
        else
        {
            whiteKingRow = toRow;
            whiteKingColumn = toColumn;
        }
    }

    return true;
}

bool ChessBoard::isValidMove(int fromRow, int fromColumn, int toRow, int toColumn) 
{
    // check boundary conditions
    if (fromRow < 0 || fromRow >= numRows || fromColumn < 0 || fromColumn >= numCols) return false;
    if (toRow < 0 || toRow >= numRows || toColumn < 0 || toColumn >= numCols) return false;

    // check if the destination exists
    if (isEmpty(fromRow, fromColumn)) return false;

    
    ChessPiece *piece = board[fromRow][fromColumn];
    ChessPiece *target = board[toRow][toColumn];

    // check if the piece is acpturing its own color
    if (!isEmpty(toRow, toColumn) && piece->getColor() == target->getColor()) return false;

    if(piece -> getType() != King) //Checking to see if moving non-king piece will cause check
    {
        if(turn == White && whiteKingColumn != -1)
        {
            board[fromRow][fromColumn] = nullptr;
            if(isPieceUnderThreat(whiteKingRow, whiteKingColumn))
            {
                if(!willItRemoveCheck(toRow, toColumn, White, piece -> getType()))
                {
                    board[fromRow][fromColumn] = piece;
                    return false;
                }
            }
            board[fromRow][fromColumn] = piece;
        }
        else if(turn == Black && blackKingColumn != -1)
        {
            board[fromRow][fromColumn] = nullptr;
            if(isPieceUnderThreat(blackKingRow, blackKingColumn))
            {
                if(!willItRemoveCheck(toRow, toColumn, Black, piece -> getType()))
                {
                    board[fromRow][fromColumn] = piece;
                    return false;
                }
            }
            board[fromRow][fromColumn] = piece;
        }
        
    }
    return piece->canMoveToLocation(toRow, toColumn);
}


bool ChessBoard::isValidMoveModified(int fromRow, int fromColumn, int toRow, int toColumn) 
{   
    // check boundary conditions
    if (fromRow < 0 || fromRow >= numRows || fromColumn < 0 || fromColumn >= numCols) return false;
    if (toRow < 0 || toRow >= numRows || toColumn < 0 || toColumn >= numCols) return false;

    // check if the destination exists
    if (isEmpty(fromRow, fromColumn)) return false;

    
    ChessPiece *piece = board[fromRow][fromColumn];
    ChessPiece *target = board[toRow][toColumn];

    // check if the piece is acpturing its own color
    if (!isEmpty(toRow, toColumn) && piece->getColor() == target->getColor()) return false;
    
    return piece->canMoveToLocationModified(toRow, toColumn);
}

bool ChessBoard::isValidMoveExtraModified(int fromRow, int fromColumn, int toRow, int toColumn) 
{   

    // check boundary conditions
    if (fromRow < 0 || fromRow >= numRows || fromColumn < 0 || fromColumn >= numCols) return false;
    if (toRow < 0 || toRow >= numRows || toColumn < 0 || toColumn >= numCols) return false;

    // check if the destination exists
    if (isEmpty(fromRow, fromColumn)) return false;

    
    ChessPiece *piece = board[fromRow][fromColumn];
    ChessPiece *target = board[toRow][toColumn];

    // check if the piece is acpturing its own color
    if (!isEmpty(toRow, toColumn) && piece->getColor() != target->getColor()) return false;


    return piece->canMoveToLocationModified(toRow, toColumn);
}

bool ChessBoard::isPieceUnderThreat(int row, int column) {
    if (isEmpty(row, column)) {return false;}
    if (numRows == 0 || numCols == 0) {return false;}
    for (int r = 0; r < numRows; r++) {
        for (int c = 0; c < numCols; c++) {
            if(isValidMoveModified(r, c, row, column) && board[r][c]->getColor() != board[row][column]->getColor())
            {
                return true;
            }
        }
    }
    return false;
}

//If youre taking a piece with the king, the color of the isValidMoveModified checker needs to flip

bool ChessBoard::wouldKingBeUnderThreat(int row, int column, int oldCol, int oldRow, Color color, bool capture) {
    ChessPiece* Oldspot = board[oldRow][oldCol];
    ChessPiece* newSpot = board[row][column];
    board[row][column] =  board[oldRow][oldCol];
    board[oldRow][oldCol] = nullptr;
    if (numRows == 0 || numCols == 0) {return false;}
    for (int r = 0; r < numRows; r++) {
        for (int c = 0; c < numCols; c++) {
            if(isValidMoveModified(r, c, row, column) && board[r][c]->getColor() != color)
                {
                    board[row][column] = newSpot;
                    board[oldRow][oldCol] = Oldspot;
                    return true;
                }
            
        }
    }
    board[row][column] = newSpot;
    board[oldRow][oldCol] = Oldspot;
    return false;
}


bool ChessBoard::willItRemoveCheck(int row, int column, Color col, Type typ) {
    ChessPiece* orig = board[row][column];
    board[row][column] = nullptr;

    createChessPiece(col, typ, row, column);
    if((col == White && !isPieceUnderThreat(whiteKingRow, whiteKingColumn)) || (col == Black && !isPieceUnderThreat(blackKingRow, blackKingColumn)))
    {
        delete board[row][column];
        board[row][column] = orig;
        return true;
    }
    delete board[row][column];
    board[row][column] = orig;
    return false;
}

bool ChessBoard::isEmpty(int row, int column) const {
    return (board[row][column] == nullptr);
}


// given function
std::ostringstream ChessBoard::displayBoard()
{
    std::ostringstream outputString;
    // top scale
    outputString << "  ";
    for (int i = 0; i < numCols; i++)
    {
        outputString << i;
    }
    outputString << std::endl
                 << "  ";
    // top border
    for (int i = 0; i < numCols; i++)
    {
        outputString << "-";
    }
    outputString << std::endl;

    for (int row = 0; row < numRows; row++)
    {
        outputString << row << "|";
        for (int column = 0; column < numCols; column++)
        {
            ChessPiece *piece = board.at(row).at(column);
            outputString << (piece == nullptr ? " " : piece->toString());
        }
        outputString << "|" << std::endl;
    }

    // bottom border
    outputString << "  ";
    for (int i = 0; i < numCols; i++)
    {
        outputString << "-";
    }
    outputString << std::endl
                 << std::endl;

    return outputString;
}