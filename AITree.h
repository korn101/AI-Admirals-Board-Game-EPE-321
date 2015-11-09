/* 
 * File:   Tree.h
 * Author: GJ Fouche
 *
 * Created on 17 September 2015, 12:17 PM
 */

#ifndef TREE_H
#define	TREE_H

#include "AIPiece.h"
#include "AIBoard.h"
#include "AINode.h"
#include <vector>
#include <limits.h>

#define AI_MAX 999

class AITree {
public:
    
    AITree(AIBoard & b);
    AITree(AIBoard & b, bool ismax);
    virtual ~AITree();
    void deleteTree(AINode * node);
    void doSomething();
    void expandMinMax(AINode * node, int depth);
    AINode * getRoot();
    void debug();
    void buildMinMax(AINode * node, int depth);
    
    int getMaxOf(int a, int b);
    int getMinOf(int a, int b);    
    
    std::string getBestMoveAB(); // best move using alpha-beta and depth look-ahead for perspective of playerID.
    std::string getBestJumpAB(); // get the best jump move.
    
private:
    AINode *root; // root of the tree.
    int totalNodes;
    AIBoard & currBoard;
    std::string getBestMove();
    unsigned int totalDepth;
    void sortChildNodes(AINode * node);
    int doAlphaBeta(AINode * node, int depth, int a, int b, bool isMax);
    
};

#endif	/* TREE_H */

