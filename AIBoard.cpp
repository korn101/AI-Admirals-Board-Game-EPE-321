/* 
 * File:   Board.cpp
 * Author: GJ Fouche
 * p
 * Created on 15 September 2015, 9:36 PM
 */

#include "AIBoard.h"
#include <sstream>
#include <cmath>
#include <cstdlib>

AIBoard::AIBoard() {
    
    // initialization 
    for (int i = 0; i < HEIGHT; i++) {
        for (int k = 0; k < WIDTH; k++)
        {
            // delete the piece at point
            AIBoard::board[i][k] = new AIPiece(); // blank pieces.
        }
    }

    AIBoard::playerPieces.resize(2);
    for (int i=0; i < 2; i++)
        playerPieces[i].clear();
    fleetSize[0] = 0;
    fleetSize[1] = 0;
    lastMoveScore = 0;
    
}

void AIBoard::clear() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int k = 0; k < WIDTH; k++)
        {
            // delete the piece at point
            if (AIBoard::board[i][k] != 0)
                delete(AIBoard::board[i][k]);
            AIBoard::board[i][k] = new AIPiece(); // blank pieces.
        }
    }

    AIBoard::playerPieces.resize(2);
    for (int i=0; i < 2; i++)
        playerPieces[i].clear();
    fleetSize[0] = 0;
    fleetSize[1] = 0;
    lastMoveScore = 0;
}


AIBoard::~AIBoard() {
}

void AIBoard::displayBoard()
{
    // display the board.
     
    for (int i = 0 ; i < WIDTH ; i++)
        std::cout << "-";
    std::cout << std::endl;
    
    std::cout << "0|1|2|3|4|5|6|7" << std::endl;
    
    for (int k = 0; k < HEIGHT; k ++)
    {
        
        for (int i=0; i < WIDTH; i++)
        {
            if (i%WIDTH == 0)
                std::cout << std::endl << board[k][i]->getChar();
            else
                std::cout << "|" << board[k][i]->getChar();
        }
        std::cout << "|  " << k;
            
    }
    std::cout << std::endl << std::endl;
    
    std::cout << "Board score: " << AIBoard::getBoardScore() << std::endl << "Pieces on board: ";
    for (int i=0; i < fleetSize[0]; i++)
            std::cout << playerPieces[0][i]->getChar() << ",";
    std::cout << std::endl;
    for (int i=0; i < fleetSize[1]; i++)
        std::cout << playerPieces[1][i]->getChar() << ",";
    std::cout << std::endl;
    
    
}

void AIBoard::placeOnBoard(int pieceid, int x, int y, int playerID)
{
    // this function places a piece of certain ID onto the board.
    
    if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
        std::cout << "PLACEMENT OUT OF BOUNDS" << std::endl;
    else {
        if (board[y][x]->getPieceID() == 0) // only place if the space is free.
        {
            if (board[y][x] != 0)
                delete(board[y][x]);
            board[y][x] = new AIPiece(pieceid, playerID, x,y);
           
        }
    }
}

std::vector < std::string > AIBoard::getAllValidMoves(int player,bool onlyJumps) 
{
    // get a list of all valid moves for a player side.
    // first, traverse the array holding objects for playerID parameter.
    // loop through the board, find a piece belonging to the player.
    // once the piece is found, get the legal moves possible
    
    std::vector < std::string > arrStrTemp;
    arrStrTemp.clear();
    
    
    
    for (int ix =0; ix < WIDTH; ix++)
    {
        for (int iy = 0; iy < HEIGHT; iy++)
        {
            // if the playerID of this piece matches the player parameter then:
            if (board[iy][ix]->getPlayerID() == player && board[iy][ix]->getPieceID() != 8)
            {
                // at this point, the playerID of the piece matches that which we are looking for.
                // so, we can perform a check for legal moves.
                std::vector < std::string > arrTemp;
                
                arrTemp = getValidMovesFor(ix,iy, onlyJumps); // get a vector of strings.
                // now loop through these moves and append them to the temp return vector.
                if (arrTemp.size() > 0)
                {
                    
                    for (int i = 0; i < arrTemp.size() ; i++)
                    {
                        arrStrTemp.push_back(arrTemp.at(i));
                    }
                }
            }
        }
        
    }    // for each block x.
    
    return arrStrTemp;
    
}
    
   
std::vector < std::string >  AIBoard::getValidMovesFor(int x,  int y, bool onlyJumps)
{
        std::vector < std::string > arrStrTemp;
        arrStrTemp.clear();
        
        
        // okay so, now we check if the spaces adjacent are free.
        if (board[y][x]->getPieceID() > 0)
        {
            // generate a list of valid 'adjacents'
            if (getDownOf(x,y) != 0 && getDownOf(x,y)->getPieceID() != -1)
                if (AIBoard::getDownOf(x,y)->getPlayerID() != board[y][x]->getPlayerID()) // if its clear below piece.
                {
                    if (!(board[y][x]->getPieceID() == 9 && getDownOf(x,y)->getPieceID() != 0) || 
                            (board[y][x]->getPieceID() == 9 && getDownOf(x,y)->getPieceID() >= 7))
                    {
                        std::ostringstream stringStream;
                        // minesweepers cannot perform normal attacks.
                        // represent the move in a string.
                        if (onlyJumps == false)
                        {
                            
                            stringStream << x << y << x << y + 1;
                            arrStrTemp.push_back(stringStream.str());
                        }
                        stringStream.str("");
                        // if its NOT open water (!0) below AND the piece even below that is open water (0) then we know we can jump.
                        if (getDownOf(x,y+1) != 0)
                            if (getDownOf(x,y)->getPieceID() > 0 && getDownOf(x,y+1)->getPieceID() ==0)
                            {
                                stringStream << x << y << x << y + 2;
                                arrStrTemp.push_back(stringStream.str());
                            }


                    }
                    else if (board[y][x]->getPieceID() == 9)
                    {
                        std::ostringstream stringStream;
                        if (getDownOf(x, y + 1) != 0)
                            if (getDownOf(x, y)->getPieceID() > 0 && getDownOf(x, y + 1)->getPieceID() == 0) {
                                stringStream << x << y << x << y + 2;
                                arrStrTemp.push_back(stringStream.str());
                            }
                    }
                }

            if (getRightOf(x,y) != 0 && getRightOf(x,y)->getPieceID() != -1)
                if (AIBoard::getRightOf(x,y)->getPlayerID() != board[y][x]->getPlayerID()) {
                    if (!(board[y][x]->getPieceID() == 9 && getRightOf(x,y)->getPieceID() != 0 )|| 
                            (board[y][x]->getPieceID() == 9 && getRightOf(x,y)->getPieceID() >= 7)) {
                        
                        std::ostringstream stringStream;
                        // represent the move in a string.
                        if (onlyJumps == false)
                        {
                            
                            stringStream << x << y << x + 1 << y;
                            arrStrTemp.push_back(stringStream.str());
                        }
                        stringStream.str("");
                        if (getRightOf(x+1,y) != 0)
                            if (getRightOf(x,y)->getPieceID() > 0 && getRightOf(x+1,y)->getPieceID() ==0)
                            {
                                stringStream << x << y << x + 2 << y;
                                arrStrTemp.push_back(stringStream.str());
                            }
                    }
                    else if (board[y][x]->getPieceID() == 9)
                    {
                        std::ostringstream stringStream;
                        if (getRightOf(x+1,y) != 0)
                            if (getRightOf(x,y)->getPieceID() > 0 && getRightOf(x+1,y)->getPieceID() ==0)
                            {
                                stringStream << x << y << x + 2 << y;
                                arrStrTemp.push_back(stringStream.str());
                            }
                    }
                }
            
            if (getLeftOf(x,y) != 0 && getLeftOf(x,y)->getPieceID() != -1)
                if (AIBoard::getLeftOf(x,y)->getPlayerID() != board[y][x]->getPlayerID()) {
                    if (!(board[y][x]->getPieceID() == 9 && getLeftOf(x,y)->getPieceID() != 0 )|| 
                            (board[y][x]->getPieceID() == 9 && getLeftOf(x,y)->getPieceID() >= 7))
                    {
                        std::ostringstream stringStream;
                        if (onlyJumps == false)
                        {
                            // represent the move in a string.
                            
                            stringStream << x << y << x - 1 << y;
                            arrStrTemp.push_back(stringStream.str());
                        }

                    stringStream.str("");
                    if (getLeftOf(x-1,y) != 0)
                        if (getLeftOf(x,y)->getPieceID() > 0 && getLeftOf(x-1,y)->getPieceID() ==0)
                        {
                            stringStream << x << y << x - 2 << y;
                            arrStrTemp.push_back(stringStream.str());
                        }
                    }
                    else if (board[y][x]->getPieceID() == 9)
                    {
                        std::ostringstream stringStream;
                        if (getLeftOf(x-1,y) != 0)
                            if (getLeftOf(x,y)->getPieceID() > 0 && getLeftOf(x-1,y)->getPieceID() ==0)
                            {
                                stringStream << x << y << x - 2 << y;
                                arrStrTemp.push_back(stringStream.str());
                            }
                    }
                    
        
                }
            
            
            if (getUpOf(x,y) != 0 && getUpOf(x,y)->getPieceID() != -1)
                if (AIBoard::getUpOf(x,y)->getPlayerID() != board[y][x]->getPlayerID()) {
                    if (!(board[y][x]->getPieceID() == 9 && getUpOf(x,y)->getPieceID() != 0 )|| 
                            (board[y][x]->getPieceID() == 9 && getUpOf(x,y)->getPieceID() >= 7))
                    {
                        // represent the move in a string.
                        std::ostringstream stringStream;
                        
                        if (onlyJumps == false)
                        {
                            stringStream << x << y << x << y - 1;
                            arrStrTemp.push_back(stringStream.str());
                        }
                        stringStream.str("");
                        if (getUpOf(x,y-1) != 0)
                            if (getUpOf(x,y)->getPieceID() > 0 && getUpOf(x,y-1)->getPieceID() ==0)
                            {
                                stringStream << x << y << x << y - 2;
                                arrStrTemp.push_back(stringStream.str());
                            }
                    }
                    else if (board[y][x]->getPieceID() == 9)
                    {
                        std::ostringstream stringStream;
                        if (getUpOf(x,y-1) != 0)
                            if (getUpOf(x,y)->getPieceID() > 0 && getUpOf(x,y-1)->getPieceID() ==0)
                            {
                                stringStream << x << y << x << y - 2;
                                arrStrTemp.push_back(stringStream.str());
                            }
                    }
                }
            
            
            /////////
            // DIAGONALS
            /////////
            
            if (onlyJumps == false)
            {
                if (board[y][x]->getPieceID() != 7) // if this piece is not an admiral, it can attack diagonally. 
                {
                    if (getUpRightOf(x,y) != 0 && getUpRightOf(x,y)->getPieceID() != -1)
                        if (AIBoard::getUpRightOf(x,y)->getPlayerID() != board[y][x]->getPlayerID()) {
                            if (!(board[y][x]->getPieceID() == 9 && getUpRightOf(x,y)->getPieceID() > 0))
                            {
                                // represent the move in a string.
                                std::ostringstream stringStream;
                                stringStream << x << y << x+1 << y - 1;
                                arrStrTemp.push_back(stringStream.str());
                            }
                        }

                    if (getUpLeftOf(x,y) != 0 && getUpLeftOf(x,y)->getPieceID() != -1)
                        if (AIBoard::getUpLeftOf(x,y)->getPlayerID() != board[y][x]->getPlayerID()) {
                            if (!(board[y][x]->getPieceID() == 9 && getUpLeftOf(x,y)->getPieceID() > 0))
                            {
                                // represent the move in a string.
                                std::ostringstream stringStream;
                                stringStream << x << y << x-1 << y - 1;
                                arrStrTemp.push_back(stringStream.str());
                            }
                        }

                    if (getDnLeftOf(x,y) != 0 && getDnLeftOf(x,y)->getPieceID() != -1)
                        if (AIBoard::getDnLeftOf(x,y)->getPlayerID() != board[y][x]->getPlayerID()) {
                            if (!(board[y][x]->getPieceID() == 9 && getDnLeftOf(x,y)->getPieceID() > 0))
                            {
                                // represent the move in a string.
                                std::ostringstream stringStream;
                                stringStream << x << y << x - 1<< y + 1;
                                arrStrTemp.push_back(stringStream.str());
                            }
                        }         

                    if (getDnRightOf(x,y) != 0 && getDnRightOf(x,y)->getPieceID() != -1)
                        if (AIBoard::getDnRightOf(x,y)->getPlayerID() != board[y][x]->getPlayerID()) {
                            if (!(board[y][x]->getPieceID() == 9 && getDnRightOf(x,y)->getPieceID() > 0))
                            {
                                // represent the move in a string.
                                std::ostringstream stringStream;
                                stringStream << x << y << x +1 << y + 1;
                                arrStrTemp.push_back(stringStream.str());
                            }
                        }               
                }
            }
            // at this point we have all the adjacent 'moves' we can make, yay.
            
        }
        else
        {
            // this is what happens if the piece is invalid.
            std::cout << "getValidMovesFor called on invalid piece." << std::endl;
        }
        
        
         return arrStrTemp;
}

    AIPiece * AIBoard::getLeftOf(int x, int y)
    {
        if (x > 0)
            return board[y][x-1];
        else
            return 0;
    }
    AIPiece * AIBoard::getRightOf(int x, int y)
    {
        if (x +1 < WIDTH)
            return board[y][x+1];
        else
            return 0;
    }
    AIPiece * AIBoard::getDownOf(int x, int y)
    {
        if (y+1 < HEIGHT)
            return board[y+1][x];
        else
            return 0;
    }
    AIPiece * AIBoard::getUpOf(int x, int y)
    {
        if (y > 0)
            return board[y-1][x];
        else
            return 0;
    }
    
    AIPiece * AIBoard::getUpRightOf(int x, int y)
    {
        if (y > 0 && x +1 < WIDTH)
            return board[y-1][x+1];
        else
            return 0;
    }
    
    AIPiece * AIBoard::getUpLeftOf(int x, int y)
   {
        if (y > 0 && x > 0)
            return board[y-1][x-1];
        else
            return 0;
   }
    
    AIPiece * AIBoard::getDnRightOf(int x, int y)
    {
        if (y+1 < HEIGHT && x +1 < WIDTH)
            return board[y+1][x+1];
        else
            return 0;
    }
    
    AIPiece * AIBoard::getDnLeftOf(int x, int y)
    {
        if (y+1 < HEIGHT && x > 0)
            return board[y+1][x-1];
        else
            return 0;
    }
    
    int AIBoard::getBoardScore() {
        // score of the board.
        // this serves as a basic heuristic
        
        // first update the piece list:
        AIBoard::updatePlayerPieces();
        // IMPORTANT: this function is called very often by the AI evaluator.
        // as a result, it must be fast to operate - the burden of counting and keeping 
        // track of player pieces must be handled by another function (not this one.)
        
        // SLOW EVALUATOR = SLOW AI.
        int lowestPiece = 1; // lowest piece to eval.
        int highestPiece = 9; // highest piece to evaluate
        
        int sum = 0;
        
        for (int i = lowestPiece; i <= highestPiece; i++)
            sum += ((getPieceScore(1,i) - getPieceScore(2,i)));
        
        if (getPieceScore(1,7) == 0)
            return -999;
        
        if (getPieceScore(2,7) == 0)
            return 999;
        
        return sum;// + lastMoveScore;
    }
    
    // returns an array with index corresponding to piece counts in integer values.
    int AIBoard::getPieceScore(int player, int pieceType) {
        
        // ensure that this function is called only after updatePlayerPieces();
        int tempScore = 0;
        for (int i = 0; i < fleetSize[player-1]; i++)
        {
            // if the piece is not visible to the AI player we cannot possibly know the board score.
            if (playerPieces[player-1][i]->getPieceID() == pieceType && playerPieces[player-1][i]->visible == true)
            {
                tempScore = tempScore + (pieceType);
            }
            else if (playerPieces[player-1][i]->getPieceID() == pieceType && playerPieces[player-1][i]->visible == false)
            {
                // we dont know the actual priority of the move. but we know that it is a piece, so it must have a value of at
                // least 1.
                tempScore = tempScore + 1;
            }
        }
            
        return tempScore;
    }
    
    std::string AIBoard::getBoardString() {
        
        std::ostringstream stringStream;
        
        // search through the board looking for pieces that aren't nothing..
        for (int iY = 0; iY < HEIGHT; iY++)
            for (int iX = 0; iX < WIDTH; iX++)
            {
                if (board[iY][iX]->getPieceID() > 0)
                {
                    int isVis;
                    if (board[iY][iX]->visible == true)
                        isVis = 1;
                    else
                        isVis = 0;
                    // save this one.
                    stringStream << board[iY][iX]->getPieceID() << iX << iY 
                            << board[iY][iX]->getPlayerID() << isVis;
                }
                else if (board[iY][iX]->getPieceID() == -1)
                    stringStream << 0 << iX << iY << 0 << 0;
                    
            }
        
        // at the end, string stream has a record of all board pieces and there place and playerID.
        
        return stringStream.str();
    }
    
    void AIBoard::loadBoardString(std::string strB){
        
        if (strB.size() % 5 != 0)
        {
            // strB is not right
            std::cout << "Load Board String oddly sized." << std::endl;
        }
        else
        {
            AIBoard::prevBoard = AIBoard::getBoardString();
            AIBoard::clear(); // clear the board. 
            // now loop through the board string, loading and placing each piece.
            int iLooper = 0;
            while (iLooper < strB.size())
            {
                if (strB[iLooper] - '0' == 0 && strB[iLooper+3] - '0' == 0)
                {
                    // place an island
                    AIBoard::placeOnBoard(-1, strB[iLooper+1] - '0', strB[iLooper+2] - '0', 0);
                    
                }
                else
                {
                    AIBoard::placeOnBoard(strB[iLooper] - '0', strB[iLooper+1] - '0', strB[iLooper+2] 
                                                            - '0', strB[iLooper+3] - '0');
                    if (strB[iLooper+4] - '0' == 0)
                        board[strB[iLooper+2] - '0'][strB[iLooper+1] - '0']->visible = false;
                    else
                        board[strB[iLooper+2] - '0'][strB[iLooper+1] - '0']->visible = true;
                }             
                 
                iLooper+= 5;
            }
            AIBoard::updatePlayerPieces();
        }
        
    }
     
// takes a LAN string, produces a SAN string of the result.
 std::string AIBoard::makeAIMove(std::string strLAN)
 {
     // make a move from a LAN string and,
     if (strLAN.size() < 4 || strLAN == "xx")
         return "xx";
     
     
     // first, extract the origin position from the LAN string.
     int ox = strLAN[0] - '0';
     int oy = strLAN[1] - '0';
     
     // then destination
     int dx = strLAN[2] - '0';
     int dy = strLAN[3] - '0';
     
     
     

    if (dy - oy == 2) // jump move down.
    {
        // if we dont know what piece this is, assume we can kill it anyway. (this is usually the case)

        if (board[dy-1][dx]->visible == false)
        {
            board[dy][dx] = board[oy][ox];
            board[oy][ox] = new AIPiece();
            board[dy - 1][dx] = new AIPiece();

            AIBoard::updatePlayerPieces();
            std::ostringstream stringStream;
            stringStream << board[dy][dx]->getChar() << dx << dy << "J+";

            return (stringStream.str());
        }
        else if  (((board[dy - 1][dx]->getPieceID() == 8 && board[oy][ox]->getPieceID() == 9) || board[dy - 1][dx]->getPieceID() != 8)) {
            board[dy][dx] = board[oy][ox];
            board[oy][ox] = new AIPiece();
            board[dy - 1][dx] = new AIPiece();

            AIBoard::updatePlayerPieces();
            std::ostringstream stringStream;
            stringStream << board[dy][dx]->getChar() << dx << dy << "J+";

            return (stringStream.str());
        } else {
            std::ostringstream stringStream;
            stringStream << board[oy][ox]->getChar() << dx << dy << "J-";

            board[oy][ox] = new AIPiece(); // we died. reveal the mine:
            board[dy - 1][dx]->visible = true;

            AIBoard::updatePlayerPieces();


            return (stringStream.str());
        }
    } else if (dy - oy == -2) // jump move up
    {
         if (board[dy+1][dx]->visible == false)
        {
            board[dy][dx] = board[oy][ox];
            board[oy][ox] = new AIPiece();
            board[dy + 1][dx] = new AIPiece();

            AIBoard::updatePlayerPieces();
            std::ostringstream stringStream;
            stringStream << board[dy][dx]->getChar() << dx << dy << "J+";

            return (stringStream.str());
        }
        else if ((board[dy + 1][dx]->getPieceID() == 8 && board[oy][ox]->getPieceID() == 9) || board[dy + 1][dx]->getPieceID() != 8) {
            board[dy][dx] = board[oy][ox];
            board[oy][ox] = new AIPiece();
            board[dy + 1][dx] = new AIPiece();

            AIBoard::updatePlayerPieces();
            std::ostringstream stringStream;
            stringStream << board[dy][dx]->getChar() << dx << dy << "J+";

            return (stringStream.str());
        } else {
            std::ostringstream stringStream;
            stringStream << board[oy][ox]->getChar() << dx << dy << "J-";

            board[oy][ox] = new AIPiece(); // we died. reveal the mine:
            board[dy + 1][dx]->visible = true;

            AIBoard::updatePlayerPieces();


            return (stringStream.str());
        }
    } else if (dx - ox == 2) // jump move right
    {
        if (board[dy][dx-1]->visible == false)
        {
            board[dy][dx] = board[oy][ox];
            board[oy][ox] = new AIPiece();
            board[dy][dx - 1] = new AIPiece();

            AIBoard::updatePlayerPieces();
            std::ostringstream stringStream;
            stringStream << board[dy][dx]->getChar() << dx << dy << "J+";

            return (stringStream.str());
        }
        else if ((board[dy][dx - 1]->getPieceID() == 8 && board[oy][ox]->getPieceID() == 9) || board[dy][dx - 1]->getPieceID() != 8) {
            board[dy][dx] = board[oy][ox];
            board[oy][ox] = new AIPiece();
            board[dy][dx - 1] = new AIPiece();

            AIBoard::updatePlayerPieces();
            std::ostringstream stringStream;
            stringStream << board[dy][dx]->getChar() << dx << dy << "J+";

            return (stringStream.str());
        } else {
            std::ostringstream stringStream;
            stringStream << board[oy][ox]->getChar() << dx << dy << "J-";

            board[oy][ox] = new AIPiece(); // we died. reveal the mine:
            board[dy][dx - 1]->visible = true;

            AIBoard::updatePlayerPieces();


            return (stringStream.str());
        }

    } else if (dx - ox == -2) // jump move left
    {
        if (board[dy][dx+1]->visible == false)
        {
            board[dy][dx] = board[oy][ox];
            board[oy][ox] = new AIPiece();
            board[dy][dx + 1] = new AIPiece();

            AIBoard::updatePlayerPieces();
            std::ostringstream stringStream;
            stringStream << board[dy][dx]->getChar() << dx << dy << "J+";

            return (stringStream.str());
        }
        else if ((board[dy][dx + 1]->getPieceID() == 8 && board[oy][ox]->getPieceID() == 9) || board[dy][dx + 1]->getPieceID() != 8) {
            board[dy][dx] = board[oy][ox];
            board[oy][ox] = new AIPiece();
            board[dy][dx + 1] = new AIPiece();

            AIBoard::updatePlayerPieces();
            std::ostringstream stringStream;
            stringStream << board[dy][dx]->getChar() << dx << dy << "J+";

            return (stringStream.str());
        } else {
            std::ostringstream stringStream;
            stringStream << board[oy][ox]->getChar() << dx << dy << "J-";

            board[oy][ox] = new AIPiece(); // we died. reveal the mine:
            board[dy][dx + 1]->visible = true;

            AIBoard::updatePlayerPieces();


            return (stringStream.str());
        }
    }
     else if (board[dy][dx]->visible == false && 
                           board[dy][dx]->getPlayerID() != board[oy][ox]->getPlayerID() && board[dy][dx]->getPlayerID() > 0)
     {
         // we are trying to attack a piece that is unknown to us right now.
         // we can assume, that this piece is weaker than ours.
         
         // we need to make a probabilistic decision as to whether or not we actually take the piece.
         
         // take a 50/50 chance : rand()&1;
         srand(time(NULL));
         if (std::rand()&1 == true)
         {
            // assume we take the other piece:
            board[dy][dx] = board[oy][ox];
            board[oy][ox] = new AIPiece();
            // the piece is removed, now refresh the player piece array.
            AIBoard::updatePlayerPieces();
         
         
            lastMoveScore = 0; // TODO was -1
            std::ostringstream stringStream;
            stringStream << board[oy][ox]->getChar() << dx << dy << "?"; // attacking an unknown piece.
            return (stringStream.str());
         }
         else
         {
             // assume we get taken.
            std::ostringstream stringStream;
            stringStream << board[oy][ox]->getChar() << dx << dy << "-";

            board[oy][ox] = new AIPiece();
            board[dy][dx]->visible = true; // reveal the piece.
            AIBoard::updatePlayerPieces();         
            lastMoveScore = 0;
            
            return stringStream.str();
         }
         
         
            
     }
     else{
        // now we can check for what piece corresponds to the position we want to move to.
        if (board[dy][dx]->getPieceID() == 0)
        {
            // we know this is just a normal move.
            board[dy][dx] = board[oy][ox];
            board[oy][ox] = new AIPiece();

            std::ostringstream stringStream;
            stringStream << board[dy][dx]->getChar() << dx << dy;

            // this was a normal move:
            lastMoveScore = 0;

            return stringStream.str();
        }
        else if (board[dy][dx]->getPieceID() < board[oy][ox]->getPieceID() && 
                           board[dy][dx]->getPlayerID() != board[oy][ox]->getPlayerID())
        {
            // remember to pop it from the players piece list.
            // (the one we are trying to take)

            // we are stronger than the current piece.
            // so take the other one.

           // then destination
            board[dy][dx] = board[oy][ox];
            board[oy][ox] = new AIPiece();
            // the piece is removed, now refresh the player piece array.
            AIBoard::updatePlayerPieces();
            std::ostringstream stringStream;
            stringStream << board[dy][dx]->getChar() << dx << dy << "+";

            // lastly, set our piece as visible because it has now been revealed.
            board[dy][dx]->visible = true;

            lastMoveScore = 0; // add -1 to the boardScore because taking a piece is better than doing nothing.

            return stringStream.str();
        }
        else if (board[dy][dx]->getPieceID() == 7 && 
            board[dy][dx]->getPlayerID() != board[oy][ox]->getPlayerID())
        {
            // We attacked an admiral! that means the admiral dies.
            
           // then destination
            board[dy][dx] = board[oy][ox];
            board[oy][ox] = new AIPiece();
            // the piece is removed, now refresh the player piece array.
            AIBoard::updatePlayerPieces();
            std::ostringstream stringStream;
            stringStream << board[dy][dx]->getChar() << dx << dy << "+";
            
            // lastly, set our piece as visible because it has now been revealed.
            board[dy][dx]->visible = true;
            
            return stringStream.str();
            
        }
        else if (board[dy][dx]->getPieceID() == board[oy][ox]->getPieceID() && 
                           board[dy][dx]->getPlayerID() != board[oy][ox]->getPlayerID())
        {
            // oops! we took a piece that is equal. We are both sunk.
            if (board[oy][ox] != NULL)
               delete(board[oy][ox]);
            if (board[oy][ox] != NULL)
               delete(board[dy][dx]);
            board[oy][ox] = new AIPiece();
            board[dy][dx] = new AIPiece();
            lastMoveScore = 0;
            return "++";
        }
        else if (board[dy][dx]->getPieceID() > board[oy][ox]->getPieceID() && 
                           board[dy][dx]->getPlayerID() != board[oy][ox]->getPlayerID())
        {
            // oops, we tried to challenge a piece and lost.

            // we are dead, delete our piece and keep the other - but reveal the opponents piece.

            std::ostringstream stringStream;
            stringStream << board[oy][ox]->getChar() << dx << dy << "-";

            board[oy][ox] = new AIPiece();
            board[dy][dx]->visible = true; // reveal the piece.
            AIBoard::updatePlayerPieces();         
            lastMoveScore = 0;
            
            return stringStream.str();
        }
        else
        {
            lastMoveScore = 0;
            return "xx";
        }
    }
     
     
     // return the move made with a SAN string.
 }
 
  std::string AIBoard::makeMove(std::string strLAN)
 {
        // make a move from a LAN string and,
        if (strLAN.size() < 4 || strLAN == "xx")
            return "xx";


        // first, extract the origin position from the LAN string.
        int ox = strLAN[0] - '0';
        int oy = strLAN[1] - '0';

        // then destination
        int dx = strLAN[2] - '0';
        int dy = strLAN[3] - '0';

        // now we can check for what piece corresponds to the position we want to move to.
        if (dy - oy == 2) // jump move down.
        {
            // 
            if ((board[dy-1][dx]->getPieceID() == 8  && board[oy][ox]->getPieceID() == 9) || board[dy-1][dx]->getPieceID() != 8)
            {    
                board[dy][dx] = board[oy][ox];
                board[oy][ox] = new AIPiece();
                board[dy-1][dx] = new AIPiece();

                AIBoard::updatePlayerPieces();
                std::ostringstream stringStream;
                stringStream << board[dy][dx]->getChar() << dx << dy << "J+";
                
                return (stringStream.str());
            }
            else
            {
                std::ostringstream stringStream;
                stringStream << board[oy][ox]->getChar() << dx << dy << "J-";
                
                board[oy][ox] = new AIPiece(); // we died. reveal the mine:
                board[dy-1][dx]->visible = true;
                
                AIBoard::updatePlayerPieces();

                
                return (stringStream.str());
            }
        }
        else if (dy - oy == -2) // jump move up
        {
            if ((board[dy+1][dx]->getPieceID() == 8  && board[oy][ox]->getPieceID() == 9) || board[dy+1][dx]->getPieceID() != 8)
            {    
                board[dy][dx] = board[oy][ox];
                board[oy][ox] = new AIPiece();
                board[dy+1][dx] = new AIPiece();

                AIBoard::updatePlayerPieces();
                std::ostringstream stringStream;
                stringStream << board[dy][dx]->getChar() << dx << dy << "J+";
                
                return (stringStream.str());
            }
            else
            {
                std::ostringstream stringStream;
                stringStream << board[oy][ox]->getChar() << dx << dy << "J-";
                
                board[oy][ox] = new AIPiece(); // we died. reveal the mine:
                board[dy+1][dx]->visible = true;
                
                AIBoard::updatePlayerPieces();

                
                return (stringStream.str());
            }
        }
        else if (dx - ox == 2) // jump move right
        {
            if ((board[dy][dx-1]->getPieceID() == 8  && board[oy][ox]->getPieceID() == 9) || board[dy][dx-1]->getPieceID() != 8)
            {    
                board[dy][dx] = board[oy][ox];
                board[oy][ox] = new AIPiece();
                board[dy][dx-1] = new AIPiece();

                AIBoard::updatePlayerPieces();
                std::ostringstream stringStream;
                stringStream << board[dy][dx]->getChar() << dx << dy << "J+";
                
                return (stringStream.str());
            }
            else
            {
                std::ostringstream stringStream;
                stringStream << board[oy][ox]->getChar() << dx << dy << "J-";
                
                board[oy][ox] = new AIPiece(); // we died. reveal the mine:
                board[dy][dx-1]->visible = true;
                
                AIBoard::updatePlayerPieces();

                
                return (stringStream.str());
            }
            
        }
        else if (dx - ox == -2) // jump move left
        {   
            if ((board[dy][dx+1]->getPieceID() == 8  && board[oy][ox]->getPieceID() == 9) || board[dy][dx+1]->getPieceID() != 8)
            {    
                board[dy][dx] = board[oy][ox];
                board[oy][ox] = new AIPiece();
                board[dy][dx+1] = new AIPiece();

                AIBoard::updatePlayerPieces();
                std::ostringstream stringStream;
                stringStream << board[dy][dx]->getChar() << dx << dy << "J+";
                
                return (stringStream.str());
            }
            else
            {
                std::ostringstream stringStream;
                stringStream << board[oy][ox]->getChar() << dx << dy << "J-";
                
                board[oy][ox] = new AIPiece(); // we died. reveal the mine:
                board[dy][dx+1]->visible = true;
                
                AIBoard::updatePlayerPieces();

                
                return (stringStream.str());
            }
        }
        else if (board[dy][dx]->getPieceID() == 0)
        {
            // we know this is just a normal move.
            board[dy][dx] = board[oy][ox];
            board[oy][ox] = new AIPiece();

            std::ostringstream stringStream;
            stringStream << board[dy][dx]->getChar() << dx << dy;

            
            // this was a normal move:
            return stringStream.str();
        }
        else if (board[dy][dx]->getPieceID() < board[oy][ox]->getPieceID() && 
                           board[dy][dx]->getPlayerID() != board[oy][ox]->getPlayerID())
        {
            // remember to pop it from the players piece list.
            // (the one we are trying to take)

            // we are stronger than the current piece.
            // so take the other one.

           // then destination
            board[dy][dx] = board[oy][ox];
            board[oy][ox] = new AIPiece();
            // the piece is removed, now refresh the player piece array.
            AIBoard::updatePlayerPieces();
            std::ostringstream stringStream;
            stringStream << board[dy][dx]->getChar() << dx << dy << "+";
            
            // lastly, set our piece as visible because it has now been revealed.
            board[dy][dx]->visible = true;
            
            return stringStream.str();
        }
        else if (board[dy][dx]->getPieceID() == board[oy][ox]->getPieceID() && 
                           board[dy][dx]->getPlayerID() != board[oy][ox]->getPlayerID())
        {
            // oops! we took a piece that is equal. We are both sunk.
            if (board[oy][ox] != NULL)
               delete(board[oy][ox]);
            if (board[oy][ox] != NULL)
               delete(board[dy][dx]);
            board[oy][ox] = new AIPiece();
            board[dy][dx] = new AIPiece();
            AIBoard::updatePlayerPieces();  
            
            return "++";
        }
        else if (board[dy][dx]->getPieceID() == 7 && 
                           board[dy][dx]->getPlayerID() != board[oy][ox]->getPlayerID())
        {
            // We attacked an admiral! that means the admiral dies.
            
           // then destination
            board[dy][dx] = board[oy][ox];
            board[oy][ox] = new AIPiece();
            // the piece is removed, now refresh the player piece array.
            AIBoard::updatePlayerPieces();
            std::ostringstream stringStream;
            stringStream << board[dy][dx]->getChar() << dx << dy << "+";
            
            // lastly, set our piece as visible because it has now been revealed.
            board[dy][dx]->visible = true;
            
            return stringStream.str();
            
        }
        else if (board[dy][dx]->getPieceID() > board[oy][ox]->getPieceID() && 
                           board[dy][dx]->getPlayerID() != board[oy][ox]->getPlayerID())
        {
            // oops, we tried to challenge a piece and lost.

            // we are dead, delete our piece and keep the other - but reveal the opponents piece.

            std::ostringstream stringStream;
            stringStream << board[oy][ox]->getChar() << dx << dy << "-";

            board[oy][ox] = new AIPiece();
            board[dy][dx]->visible = true; // reveal the piece.
            AIBoard::updatePlayerPieces();         
            
            
            return stringStream.str();
        }
        else
        {
            
            return "xx";
        }
     // return the move made with a SAN string.
 }
 
 
 
 void AIBoard::undo()
 {
     // undo the last move, restore prev board.
     AIBoard::loadBoardString(AIBoard::prevBoard);
 }
 
 void AIBoard::updatePlayerPieces()
 {
     playerPieces[0].clear();
     playerPieces[1].clear();
     fleetSize[0] = 0;
     fleetSize[1] = 0;
     // this function is to update the number of board pieces and references to them.
     for (int iY = 0; iY < HEIGHT; iY++)
         for (int iX = 0; iX < WIDTH; iX++)
             if (board[iY][iX]->getPieceID() > 0)
             {
                 playerPieces[board[iY][iX]->getPlayerID() - 1].push_back(board[iY][iX]);
                 fleetSize[board[iY][iX]->getPlayerID()-1] ++;
             }
 }
 
 void AIBoard::loadIntBoard(int _board[][8], int aiplayer)
 {
     
     AIBoard::clear();

    // loop through the board, look for pieces and their player ID.
    for (int iY = 0; iY < HEIGHT; iY++)
        for (int iX = 0; iX < WIDTH; iX++)
        {
            
            if (_board[iY][iX] != -1 ) // if not open water
            {
                if (_board[iY][iX] == 0)
                {
                    // island, place an island:
                    AIBoard::placeOnBoard(-1, iX,iY, 0);
                    
                }
                else
                {
                    // if its a regular piece type.
                    // first digit is player , second digit is piece type, third digit is whether or not its visible.
                    int tempplayer = 0;
                    int temppiece = 0;
                    bool tempvisible = false;

                    std::ostringstream stringStream;
                    // if the board piece is not island, or open water.
                    stringStream << _board[iY][iX]; // load the int 
                    std::string strTemp = stringStream.str();
                    tempplayer = strTemp[0] - '0';
                    temppiece = strTemp[1] - '0';
                    tempvisible = (strTemp[2]-'0' == 1);
                    
                    if (temppiece < 8)
                    {
                        temppiece = 8 - temppiece; // convert to the AI understood piece ID.
                    }

                    AIBoard::placeOnBoard(temppiece, iX, iY, tempplayer);
                    board[iY][iX]->visible = tempvisible;
                    if (tempplayer == aiplayer)
                        board[iY][iX]->visible = true;
                    
                }  
            }
        }
    
    // at this point the board is AI board is fully populated.
     AIBoard::updatePlayerPieces();
     
 }
 
 bool AIBoard::rollTheDice(int ourPieceID)
 {
     // the P(A) = no. of A on board / total pieces on board.
 }