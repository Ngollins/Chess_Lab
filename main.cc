#include <assert.h>

#include "Chess.h"

#include "ChessBoard.hh"

#include "ChessPiece.hh"

#include <iostream>

#include <fstream>




using namespace Student;




// createChessPiece(color, type, row, column)

#include <fstream>
void testCase(std::string fileName)
{
    std::ifstream myfile; 
    myfile.open(fileName);

    std::string reader;






    if (myfile.is_open()) { // always check whether the file is open

    //This uses the first 3 numbers to set the chessboard
    myfile >> reader;
    myfile >> reader;
    int row = std::stoi(reader);
    myfile >> reader;
    int col = std::stoi(reader);
    ChessBoard sBoard(col, row);

    //Start the piece creation loop
    while ( myfile.good() ) {
    myfile >> reader;
    if(reader == "~") {break;}
    Color theCol = (reader == "w" ? White : Black);
    myfile >> reader;
    Type piece = (reader == "r" ? Rook : (reader == "b" ? Bishop : (reader == "p" ? Pawn : Pawn)));
    myfile >> reader;
    int firstInt = std::stoi(reader);
    myfile >> reader;
    int secondInt = std::stoi(reader);
    sBoard.createChessPiece(theCol, piece, firstInt, secondInt);
    }

    std::cout << sBoard.displayBoard().str() << std::endl;

    while (myfile.good() ) {
        myfile >> reader;
        if(reader == "isValidScan")
        {
            for(int i = 0; i < sBoard.getNumRows(); i++)
            {
                for(int j = 0; j < sBoard.getNumCols(); j++)
                {
                    if(!sBoard.isEmpty(i, j))
                    {
                        for(int k = 0; k < sBoard.getNumRows(); k++)
                        {
                            for(int l = 0; l < sBoard.getNumCols(); l++)
                            {
                            if (sBoard.isValidMove(i, j, k, l)) { std::cout << "Valid move from (" << i << ", " << j << ") to (" << k << ", " << l << ") " << std::endl; }
                            }
                        }
                    }
                }
            }
        }
        else if(reader == "underThreatScan")
        {
            std::cout << sBoard.displayBoard().str() << std::endl;
            for(int i = 0; i < sBoard.getNumRows(); i++)
            {
                for(int j = 0; j < sBoard.getNumCols(); j++)
                {
                    if(!sBoard.isEmpty(i, j))
                    {
                            if (sBoard.isPieceUnderThreat(i, j)) { std::cout << "Piece (" << i << ", " << j << ") is under threat " << std::endl; }
                            else {std::cout << "Piece (" << i << ", " << j << ") is NOT under threat " << std::endl;}
                    }
                }
            }
        }
        else if(reader == "movePiece")
        {
            myfile >> reader;
            int curRow = std::stoi(reader);
            myfile >> reader;
            int curCol = std::stoi(reader);
            myfile >> reader;
            int toRow = std::stoi(reader);
            myfile >> reader;
            int toCol = std::stoi(reader);
            if(sBoard.movePiece(curRow, curCol, toRow, toCol)) {std::cout << "Can move" << '\n';} else {std::cout << "Cannot move" << '\n';}
        }
    }

        
}
}

int main()

{

    //test_part1_4x4_1();

    // test_part1_4x4_6();

    // test_part1_6x6_6();

    testCase("test_files/part3_4x4_1.txt");


    return EXIT_SUCCESS;

}

// void test_part1_4x4_1()

// {

//     // Config file content:

//     // 0

//     // 4 4

//     // w r 3 2

//     // b b 1 3

//     // b r 1 1

//     // w r 2 3

//     // ~

//     // isValidScan




//     // Corresponding code

//     ChessBoard sBoard(4, 4);

    // sBoard.createChessPiece(White, Rook, 3, 2);

//     sBoard.createChessPiece(Black, Bishop, 1, 3);

//     sBoard.createChessPiece(Black, Rook, 1, 1);

//     sBoard.createChessPiece(White, Rook, 2, 3);




//     // Calls isValidMove() from every position to every

//     // other position on the chess board for all pieces.




//     std::cout << "part1_4x4_1.txt" << std::endl;

//     std::cout << sBoard.displayBoard().str() << std::endl;

//     for(int i = 0; i < 4; i++)
//     {
//         for(int j = 0; j < 4; j++)
//         {
//             if(!sBoard.isEmpty(i, j))
//             {
//                 for(int k = 0; k < 4; k++)
//                 {
//                     for(int l = 0; l < 4; l++)
//                     {
//                     if (sBoard.isValidMove(i, j, k, l)) { std::cout << "Valid move from (" << i << ", " << j << ") to (" << k << ", " << l << ") " << std::endl; }
//                     }
//                 }
//             }
//         }
        
//     }


//     // White Rook at (3, 2)

//     if (sBoard.isValidMove(3, 2, 0, 2)) { std::cout << "Valid move from (3, 2) to (0, 2)" << std::endl; }

//     else { std::cout << "Invalid move from (3, 2) to (0, 2)" << std::endl; }




//     return;

// }




// void test_part1_4x4_6() {

//     // 0

//     // 4 4

//     // b p 3 0

//     // w p 0 0

//     // b b 2 3

//     // w r 0 0

//     // ~

//     // isValidScan




//     // Corresponding code

//     ChessBoard board(4, 4);

//     board.createChessPiece(Black, Pawn, 3, 0);

//     board.createChessPiece(White, Pawn, 0, 0);

//     board.createChessPiece(Black, Bishop, 2, 3);

//     board.createChessPiece(White, Rook, 0, 0);




//     std::cout << "part1_4x4_6.txt" << std::endl;

//     std::cout << board.displayBoard().str() << std::endl;

//     for(int i = 0; i < 4; i++)
//     {
//         for(int j = 0; j < 4; j++)
//         {
//             if(!board.isEmpty(i, j))
//             {
//                 for(int k = 0; k < 4; k++)
//                 {
//                     for(int l = 0; l < 4; l++)
//                     {
//                     if (board.isValidMove(i, j, k, l)) { std::cout << "Valid move from (" << i << ", " << j << ") to (" << k << ", " << l << ") " << std::endl; }
//                     }
//                 }
//             }
//         }
        
//     }

    

//     // Calls isValidMove() from every position to every

//     // other position on the chess board for all pieces.




// }

// void test_part1_6x6_6() {

//     ChessBoard board(6, 6);

//     board.createChessPiece(White, Rook, 4, 3);

//     board.createChessPiece(White, Pawn, 3, 5);

//     board.createChessPiece(White, Rook, 3, 1);

//     board.createChessPiece(Black, Pawn, 5, 3);

//     board.createChessPiece(White, Pawn, 4, 5);

//     board.createChessPiece(Black, Pawn, 4, 3);
//     //0
//     // 6 6
//     // w r 4 3
//     // w p 3 5
//     // w r 3 1
//     // b p 5 3
//     // w p 4 5
//     // b p 4 3

//     std::cout << "part1_6x6_6.txt" << std::endl;

//     std::cout << board.displayBoard().str() << std::endl;

//     for(int i = 0; i < 6; i++)
//     {
//         for(int j = 0; j < 6; j++)
//         {
//             if(!board.isEmpty(i, j))
//             {
//                 for(int k = 0; k < 6; k++)
//                 {
//                     for(int l = 0; l < 6; l++)
//                     {
//                     if (board.isValidMove(i, j, k, l)) { std::cout << "Valid move from (" << i << ", " << j << ") to (" << k << ", " << l << ") " << std::endl; }
//                     }
//                 }
//             }
//         }
        
//     }
// }





