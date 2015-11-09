/* 
 * File:   AIPlayer.cpp
 * Author: GJ Fouche
 * 
 * Created on 06 October 2015, 2:36 PM
 * 
 * The AI player class abstracts the operations (tree building, function calls, etc) 
 */

#include <sstream>
#include <iostream>

#include "AIPlayer.h"

AIPlayer::AIPlayer(int diff, int player){
    
    
    //AIPlayer::cBoard = b;
    
    if (diff > 10)
        AIPlayer::difficulty = 10;
    else if (diff < 1)
        AIPlayer::difficulty = 1;
    else
        AIPlayer::difficulty = diff;
    
    if (player < 1)
        AIPlayer::player = 1;
    else if (player > 2)
        AIPlayer::player = 2;
    else
        AIPlayer::player = player;
   
}

std::string AIPlayer::getJumpMove(int _board[][8])
{
    // create the board.
    
    AIBoard b1 = AIBoard(); // init the board.
    b1.loadIntBoard(_board, AIPlayer::player); // load from int board array.
    
    // at this point the board AI board is fully populated.

    std::string strBestMoveAB;
    
    if (AIPlayer::player == 2)
    {
        AITree t1 = AITree(b1);

        t1.buildMinMax(t1.getRoot(), AIPlayer::difficulty);
        t1.debug();
        
        strBestMoveAB = t1.getBestJumpAB();
        
    }
    else if (AIPlayer::player == 1)
    {
        AITree t1 = AITree(b1, true);

        t1.buildMinMax(t1.getRoot(), AIPlayer::difficulty);
        

        strBestMoveAB = t1.getBestJumpAB();
        
    }
    

        std::string strSan = b1.makeMove(strBestMoveAB);

        int isAttack = 0;

        if (strSan.find('J') !=std::string::npos)
            isAttack = 2;    // it was a jump move.
        else if (strSan.find('+') !=std::string::npos || strSan.find('-') !=std::string::npos || strSan.find('?') !=std::string::npos)
            isAttack = 1; // its an attack move.
        else
            isAttack = 0; // its a normal move

        std::ostringstream stringStream;
        stringStream << isAttack << strBestMoveAB;

        
        
        
        return stringStream.str();
    }


std::string AIPlayer::getMove(int _board[][8])
{
    // parse the board passed as a parameter (2d int) and translate it to the AI board object (2d piece).
    
    // create the board.
    
    AIBoard b1 = AIBoard(); // init the board.
    b1.loadIntBoard(_board, AIPlayer::player); // load from int board array.

    // at this point the board is AI board is fully populated.

    
    std::string strBestMoveAB;
    
    if (AIPlayer::player == 2)
    {
        AITree t1 = AITree(b1);

        t1.buildMinMax(t1.getRoot(), AIPlayer::difficulty);
        //t1.debug();
        
        strBestMoveAB = t1.getBestMoveAB();
    }
    else if (AIPlayer::player == 1)
    {
        AITree t1 = AITree(b1, true);

        t1.buildMinMax(t1.getRoot(), AIPlayer::difficulty);
        

        strBestMoveAB = t1.getBestMoveAB();
        
    }

        std::string strSan = b1.makeMove(strBestMoveAB);

        int isAttack = 0;

        if (strSan.find('J') !=std::string::npos)
            isAttack = 2;    // it was a jump move.
        else if (strSan.find('+') !=std::string::npos || strSan.find('-') !=std::string::npos || strSan.find('?') !=std::string::npos)
            isAttack = 1; // its an attack move.
        else
            isAttack = 0; // its a normal move

        std::ostringstream stringStream;
        stringStream << isAttack << strBestMoveAB;

        
        
        
        return stringStream.str();
    }
