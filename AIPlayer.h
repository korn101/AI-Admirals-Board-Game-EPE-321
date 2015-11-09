/* 
 * File:   AIPlayer.h
 * Author: d-savant
 *
 * Created on 06 October 2015, 2:36 PM
 * 
 * The AI player is the direct interaction between the AI component and the main program.
 * Inputs: 
 * 2 dimensional integer array (board representation)
 * 
 * Process: 
 * Read the board state into the current board for the AI player object,
 * build minimax tree
 * get best move with alpha-beta pruning
 * 
 * Output: A string corresponding to a move to make.
 */

#include "AITree.h"

#ifndef AIPLAYER_H
#define	AIPLAYER_H

class AIPlayer {
public:
    AIPlayer(int diff, int player); // initialise the AI player and associated it with a board.
    std::string getMove( int _board[][8]);
    std::string getJumpMove( int _board[][8]);
    //std::string makeMove(AIBoard & b );
    //AIBoard * stdBoardToAIBoard(int _board[][8]);
private:
    int difficulty; // difficulty of the AI
    int player;
};

#endif	/* AIPLAYER_H */

