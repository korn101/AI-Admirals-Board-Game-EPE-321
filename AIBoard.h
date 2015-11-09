/* 
 * File:   Board.h
 * Author: GJ Fouche
 *
 * Created on 15 September 2015, 9:36 PM
 */

#ifndef BOARD_H
#define	BOARD_H

/** @brief Board class used by the AI to save or simulate a given board state.
      @author GJ Fouche
      @date 15 September 2015, 9:36 PM
 */

#define HEIGHT 10
#define WIDTH 8


#include "AIPiece.h"
#include <iostream>
#include <vector>


class AIBoard {
public:
    AIBoard();
    virtual ~AIBoard();
    void displayBoard(); // display the current board.
    void placeOnBoard(int pieceid, int x, int y, int playerID); // place on the board, the pieceID at coordinates x, y. [y][x]
    
    std::vector < std::string > getAllValidMoves(int player, bool onlyJumps); // returns all possible valid moves.
    std::vector< std::string > getValidMovesFor(int x, int y, bool onlyJumps); // find valid moves for Piece at x,y.
    
    AIPiece * getPieceAt(int x, int y){
        return (board[y][x]);
    }
    AIPiece * getLeftOf(int x, int y);
    AIPiece * getRightOf(int x, int y);
    AIPiece * getDownOf(int x, int y);
    AIPiece * getUpOf(int x, int y);
    
    AIPiece * getUpRightOf(int x, int y);
    AIPiece * getUpLeftOf(int x, int y);
    AIPiece * getDnRightOf(int x, int y);
    AIPiece * getDnLeftOf(int x, int y);
    
    
    std::string makeAIMove(std::string strLAN); // takes a LAN string, produces a SAN string of the result. ASSUMING AI RULES.
    
    std::string makeMove(std::string strLAN); // make an actual valid move.
    
    // heuristics
    int getBoardScore(); 
    int getPieceScore(int player, int pieceType); // get the cumulative score of a specific piece of a specific player.
    
    std::string getBoardString();
    
    void loadBoardString(std::string strB);
    void loadIntBoard(int _board[][8], int aiplayer);
   
    int lastMoveScore; // the effect that the last move had. How does it contribute to board state?
    
    void undo();
    
    bool rollTheDice(int ourPieceID); // get the probabilistic decision as to whether we will win with this piece.
    
    
    
private:
    AIPiece * board[HEIGHT][WIDTH];
    
    std::vector < std::vector < AIPiece * > > playerPieces; // player piece array.
    
    std::string prevBoard; // store the previous board.
    
    void clear();
    void updatePlayerPieces();
    
    int fleetSize[2];
    
};

#endif	/* BOARD_H */

