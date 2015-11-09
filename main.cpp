/* 
 * File:   main.cpp
 * Author: GJ Fouche
 *
 * Created on 14 September 2015, 8:54 PM
 */

#include <cstdlib>
#include <sstream>
#include "AIBoard.h"
#include "AITree.h"
#include "AIPlayer.h"

using namespace std;

// this function, used for debugging, simply prints the available moves for a player.
void printMoves(AIBoard& b, int playerID)
{
    std::vector < std::string > arrResults;
    arrResults = b.getAllValidMoves(playerID, false);
    if (arrResults.size() < 1)
    {
        cout << "No Moves Available!" << endl;
    }
    else
    {
        for (int i =0; i < arrResults.size(); i++)
            cout << arrResults[i] << " ; ";
    }
    cout << endl;
    
}

int main() {

    // the AI should interact like a human player:
    // * Generate a MakeMove based on the state of the board.
    // * Heuristics, decide what moves are good and bad.
    // * GetMove from AI.
    
    // test the AIplayer.
    
    // SORT OF FIXED.
    
    
    // test board
    int mainBoard[10][8] = 
    {
        {-1,-1,-1,-1,-1,-1,-1,-1},
        {-1,-1,-1,111,251,-1,-1,-1},
        {-1,130,-1,-1,-1,-1,-1,-1},
        {-1,-1,-1,250,-1,-1,-1,-1},
        {-1,-1,-1,-1,-1,-1,-1,-1},
        {-1,-1,-1,-1,-1,-1,-1,-1},
        {-1,-1,-1,-1,-1,-1,-1,-1},
        {-1,-1,-1,211,-1,0,-1,-1},
        {-1,-1,-1,-1,-1,0,-1,-1},
        {-1,-1,-1,-1,-1,-1,-1,-1},
        
    };
    
    srand(time(NULL));
    
    
    /*
    for (int i =0; i < 4; i++)
        for (int k = 0; k < WIDTH; k++)
        {
             mainBoard[i][k] = 100 + ((1 + ( std::rand() % ( 7 - 1 + 1 ) ))*10) + 0;
             cout << mainBoard[i][k]  << endl;
        }
    for (int i =6; i < HEIGHT; i++)
        for (int k = 0; k < WIDTH; k++)
        {
            mainBoard[i][k] = 200 + ((1 + ( std::rand() % ( 7 - 1 + 1 ) ) *10)) + 0;
            cout << mainBoard[i][k]  << endl;
        }
    */
    
    AIBoard b1 = AIBoard();
    b1.loadIntBoard(mainBoard, 2);
    //std::vector < std::string > strVec = b1.getAllValidMoves(2, false);
    
    //for (int i =0; i < strVec.size(); i++)
    //    cout << strVec[i] << endl;
    
    
    
    //AIPlayer ai2 = AIPlayer(10, 2);
    //cout << ai2.getMove(mainBoard) << endl;
    
    //AITree t1 = AITree(b1);
    //t1.buildMinMax(t1.getRoot(), 1);
    //t1.debug();
    
    
    /*
    b1.loadIntBoard(mainBoard);
    b1.displayBoard();
    // get the move:
    AITree t1 = AITree(b1);
    t1.buildMinMax(t1.getRoot(), 1);
    string strMove = t1.getBestMoveAB();
    cout << strMove << endl;
    b1.makeMove(strMove);
    b1.displayBoard();
    */
    
    
    // now load a board string, which is [pieceType][x][y][playerID]
    //b1.loadBoardString("410155223231035004507552626243617662617137710390"); 
    //b1.loadBoardString("50017202");
    
    AIPlayer * player1 = new AIPlayer(10,1);
    AIPlayer * player2 = new AIPlayer(10,2);
    
    
    bool currPlayer = 0;
    int noRounds = 0;
    while (b1.getAllValidMoves(1, false).size() > 0 && b1.getAllValidMoves(2, false).size() > 0 && noRounds < 100)
    {
        b1.displayBoard();
        
        if (currPlayer == 0)
        {
            // white player.
            // get the players desired move.
            std::string move;
            cout << "-> Player 1 make a move. " << endl;
 
            cin >> move;
            b1.makeMove(move);
            currPlayer = 1;
        }
        else if (currPlayer == 1)
        {
            // red player or whatever
            cout << "-> AI Player 2 Thinking please wait..." << endl;
            std::string move;

            AITree t1 = AITree(b1);
            t1.buildMinMax(t1.getRoot(), 10);
            cout << "->" << b1.makeMove(t1.getBestMoveAB()) << endl;
            
            currPlayer = 0;
        }
        
        noRounds++;
    }
    
    cout << "\n-> We have a winner at " << noRounds << endl;
    b1.displayBoard();
   
    
    return 0;
}

