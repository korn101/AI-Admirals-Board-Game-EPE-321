/* 
 * File:   Piece.cpp
 * Author: GJ Fouche
 *
 * Created on 15 September 2015, 8:57 PM
 */

#include <ios>
#include <iostream>

#include "AIPiece.h"

AIPiece::AIPiece() {
    AIPiece::pieceID = 0;
    AIPiece::playerID = 0;
    AIPiece::visible = true;
}

AIPiece::AIPiece(int id, int player,int x,int y)
{

    
    if ( (player > 2 || player < 1) && id != -1)
        AIPiece::pieceID = 0;
    else{
        AIPiece::pieceID = id;
        if (id != -1 && player == 1)
            AIPiece::visible = false;
    }
        
      
    AIPiece::playerID = player;
    
    AIPiece::coords[0] = x;
    AIPiece::coords[1] = y;
    
    
}

AIPiece::AIPiece(const AIPiece& orig) {
    AIPiece::pieceID = orig.pieceID;
    AIPiece::playerID = orig.playerID;
}

AIPiece::~AIPiece() {
}

char AIPiece::getChar() {
    
    char tempChar;
    
    if (pieceID == 7)
        tempChar = ('a'); // admiral ?
    else if (pieceID == 6)
        tempChar = 'q'; // aircraft carrier
    else if (pieceID == 5)
        tempChar = 'h'; // helicopter carrier
    else if (pieceID == 4)
        tempChar = 'c'; // cruiser
    else if (pieceID == 3)
        tempChar = 'd'; // destroyer
    else if (pieceID == 2)
        tempChar = 'k'; // convoy
    else if (pieceID == 1)
        tempChar = 's'; // submarine
    else if (pieceID == 8)
        tempChar = '+'; // mine
    else if (pieceID == 9)
        tempChar = '#';// mine sweeper.
    else if (pieceID == -1)
        tempChar = 'x';
    
    if (AIPiece::getPieceID() == -1)
        return ('x');
    
    if (AIPiece::getPieceID() == 0)
        return ('_');
    
    if (AIPiece::visible == true)
    {
        if (AIPiece::getPlayerID() == 1)
            return toupper(tempChar);
        else if (AIPiece::getPlayerID() == 2)
            return tolower(tempChar);
    }
    else
        return ('?');
    
}

int AIPiece::getPieceID() {
    return AIPiece::pieceID;
}

int AIPiece::getPlayerID() {
    return AIPiece::playerID;
}