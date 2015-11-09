/* 
 * File:   Piece.h
 * Author: GJ Fouche
 *
 * Created on 15 September 2015, 8:57 PM
 */

#ifndef PIECE_H
#define	PIECE_H

#include <string>

class AIPiece {
public:
    AIPiece();
    AIPiece(int id, int player, int x, int y);
    AIPiece(const AIPiece& orig);
    virtual ~AIPiece();
    char getChar(); // get the character representation of this piece. for display.
    int getPieceID(); // return the pieceID.
    int getPlayerID(); // get the playerID associated.
    
    bool visible; // is the piece visible to the AI ? has it been discovered?
private:
    int pieceID; // ID of the piece
    int playerID; // owner.
    int coords[2]; // coordinates of this piece on the board.
    
};

#endif	/* PIECE_H */

