/* 
 * File:   Tree.cpp
 * Author: GJ Fouche
 * 
 * Created on 17 September 2015, 12:17 PM
 */

#include "AITree.h"
#include "AITimer.h"


AITree::AITree(AIBoard & b) : currBoard(b) {
     //currBoard = b;
    
    // first create the tree by plotting moves.
    // assume that we are playing the MAX player.
    AINode * newNode = new AINode(b.getBoardString(), "root", b.getBoardScore(), false, false);
    
    AITree::root = newNode;
    AITree::totalNodes = 1;
    AITree::totalDepth = 0;
    b.loadBoardString(b.getBoardString());
    
    //std::cout << "Created tree root with board string: " << b.getBoardString() << endl;
    
    
}

AITree::AITree(AIBoard & b, bool ismax) : currBoard(b) {
     //currBoard = b;
    
    // first create the tree by plotting moves.
    // assume that we are playing the MAX player.
    AINode * newNode = new AINode(b.getBoardString(), "root", b.getBoardScore(), ismax, false);
    
    AITree::root = newNode;
    AITree::totalNodes = 1;
    AITree::totalDepth = 0;
    b.loadBoardString(b.getBoardString());
}


AITree::~AITree() {
    
    // de-constructor to stop memory leaks.
    
    // proceed down to the leaf nodes of the tree and free.
    deleteTree(root);
    
    
}

void AITree::deleteTree(AINode* node)
{
    if (node != NULL)
    {
        for (int i =0; i < node->numberOfNodes; i++)
            deleteTree(node->nodes[i]);

        delete node;
        node = NULL;
    }
}

void AITree::doSomething(){
    
}

void AITree::buildMinMax(AINode * node, int depth)
{
    unsigned long maxTimeSec = 1;
    if (depth > 0)
    {
        
        // TODO
        //AITree::expandMinMax(root, depth);
        //AITree::totalDepth = depth;
        
        
        AITimer t1;
        t1.start();
        
        for (int i2 = 1; i2 <= depth; i2++)
        {
            if (t1.elapsedTime() >= maxTimeSec)
            {
                // finish current depth
                std::cout << "Forced finish at depth " << i2-1 << " at time: " << t1.elapsedTime() <<  std::endl;
                AITree::totalDepth = i2-1;
                break;
            }
            else
            {
                // expand to depth i2.
                std::cout << "Expanding to depth " << i2 << " time passed: " << t1.elapsedTime() << std::endl;
                AITree::expandMinMax(AITree::root, i2);
                AITree::totalDepth = i2;
            }
        }
         
    }
        
}

void AITree::expandMinMax(AINode * node, int depth)
{
    
    if (depth < 1 || node == NULL || (node->priority) > 999 || node->priority < -999)
    {
        // terminal reached
        ;
    }
    else
    {
        // load the current nodes FEN.
        //std::cout << "Loading the FEN..";
        AITree::currBoard.loadBoardString(node->strBoard);
        //cout << "Fen Loaded...";
        
        if (node->boolExpanded == false) // if we haven't already expanded this node.
        {
            // now we need to get all the possible moves
            std::vector < std::string > arrAllMoves;
            arrAllMoves.clear();

           // cout << "Getting all moves... ";
            if (node->boolMax == true)
                arrAllMoves = AITree::currBoard.getAllValidMoves(1, node->boolJumpOnly); //max
            else
                arrAllMoves = AITree::currBoard.getAllValidMoves(2, node->boolJumpOnly); // min
            
            // at this point, we have this vector of strings,
            // containing all possible moves.
            // now perform every move using LAN string, then get the SAN string result,
            // then undo the move and repeat for every move.

            //cout << "Now for every move, creating nodes\n";
            for (int i = 0; i < arrAllMoves.size(); i++)
            {
                // make a move:
                //cout << "Making the move.. " << i << "/" << arrAllMoves.size() << "..." << arrAllMoves[i];
                std::string sSAN;
                int iScoreModifier = 0;
                int iScoreNet = 0;
                int iOldBoardScore = 0;
                iOldBoardScore = currBoard.getBoardScore(); // save the current boad score (before move)
                sSAN = currBoard.makeAIMove(arrAllMoves[i]);
                // now record the FEN, score, all that stuff:
                iScoreNet = currBoard.getBoardScore() - iOldBoardScore; // the net change of board score.

                if (sSAN.find("J+") !=std::string::npos)
                {
                    // if the current player is player 2 and the board score is positive then we need to modify the boardscore by inverting it:
                    iScoreModifier = iScoreNet * 2;
                }
                else
                {
                    iScoreModifier = iScoreNet;
                }
                // to ensure that jump moves are prioritised above normal moves.
                
                //cout << "Creating node...";
                
                // if we jumped, we can technically make another move.
                
                if (sSAN.find("J+") !=std::string::npos)
                {
                    node->nodes[i] = new AINode(currBoard.getBoardString(), arrAllMoves[i], 
                            iOldBoardScore+iScoreModifier, (node->boolMax), true);
                }
                else
                {
                    node->nodes[i] = new AINode(currBoard.getBoardString(), arrAllMoves[i], 
                            iOldBoardScore+iScoreModifier, !(node->boolMax), false);
                }
                node->numberOfNodes = node->numberOfNodes + 1;
                AITree::totalNodes = AITree::totalNodes + 1;

                // we've now recorded this move and its priority. now undo and redo for the rest.
                //cout << "Loading the original board string... " << node->strBoard << endl ;
                currBoard.loadBoardString(node->strBoard);

            }

            // sort the child nodes.
            // now perform insertion sort on nodes.
            if (node->boolMax == true)
            {
                // if we are on a max node, we want to sort highest to lowest
                for (int i = 0; i < node->numberOfNodes; i++) {
                    int j = i;
                    while (j > 0 && (node->nodes[j - 1]->priority < node->nodes[j]->priority)) {
                        AINode * temp = (node->nodes[j]);
                        (node->nodes[j]) = (node->nodes[j - 1]);
                        (node->nodes[j - 1]) = temp;
                        j = j - 1;
                    }
                }  
            }
            else
            {
                // if we are on a min node we want to sort lowest to highest.
                for (int i=0; i < node->numberOfNodes; i++)
                {
                    int j = i;
                    while (j > 0 && (node->nodes[j-1]->priority > node->nodes[j]->priority))
                    {
                        AINode * temp = node->nodes[j];
                        node->nodes[j] = node->nodes[j-1];
                        node->nodes[j-1] = temp;
                        j = j -1;
                    }
                }  
            }
            
            // this node has now been completely expanded
            node->boolExpanded = true;

        }
        //std::cout << "Node expanded, now recursively going down\n" << std::endl;
        
        // prevent the nodes being expanded for an unwanted depth. 
        for (int i = 0; i < node->numberOfNodes; i++) 
        {
            // the idea is to recursively expand each child passed as a parameter to this function and depth--.
            expandMinMax(node->nodes[i], depth - 1);
            currBoard.loadBoardString(node->strBoard); 
            // return to the root boord state after expanding children.
        }
    }
    
    
}

AINode * AITree::getRoot()
{
    return AITree::root;
}

void AITree::debug() {
    std::cout << "This tree object has a total of " << AITree::totalNodes << " nodes." << std::endl;
    std::cout << "First layer of the tree: ";
    for (int i =0; i < root->numberOfNodes; i++)
        std::cout << "[ " << root->nodes[i]->strMove << " ]" << i << ":" << root->nodes[i]->priority << ",";
    std::cout << std::endl;
}

std::string AITree::getBestMove() {
    // return the best move.
    if (totalNodes > 1)
    {
        int iBest = -9999;
        int indexBest = 0;
        
        // if the tree has been expanded.
        for (int i =0; i < AITree::root->numberOfNodes; i++)
        {
            if (AITree::root->nodes[i]->priority > iBest)
            {    
                iBest = AITree::root->nodes[i]->priority;
                indexBest = i;
            }
        }
        
        return (AITree::root->nodes[indexBest]->strMove);
    }
    else
    {
        return "xx";
    }
}

void AITree::sortChildNodes(AINode * node)
{
    // sort the child nodes of this node passed as a parameter.
    // TODO
}

int AITree::getMaxOf(int a, int b)
{
    if  (b > a)
        return b;
    else
        return a;
}

int AITree::getMinOf(int a, int b)
{
    if (a < b)
        return a;
    else
        return b;
}

int AITree::doAlphaBeta(AINode * node, int depth, int a, int b, bool isMax)
{
    // alpha beta pruning tree search
    // algorithm.
    
    if (depth < 1 || node->numberOfNodes == 0)
    {
        return (node->priority);
    }
    else
    {
        if (isMax == true)
        {
            // for a max player.
            int v = -999;
            for (int iNodes = 0; iNodes < node->numberOfNodes; iNodes++)
            {
                v = max(v, doAlphaBeta(node->nodes[iNodes], depth - 1, a, b, false));
                a = max(a,v);
                if (b <= a)
                    break; // prune. BETA cutoff.
            }
            
            return (v);
        }
        else
        {
            // min player.
            int v = 999;
            for (int iNodes = 0; iNodes < node->numberOfNodes; iNodes++)
            {
                v = min(v, doAlphaBeta(node->nodes[iNodes], depth - 1, a, b, true));
                b = min(b, v);
                if (b <= a)
                    break; // ALPHA cut off. Prune.
            }
            
            return v;
        }
    }
    
}


std::string AITree::getBestJumpAB()
{
    // ASSUME THAT A TREE ALREADY EXISTS.
    // run through the chidren running alpha beta and check for the best move.
    // at the depth of int "depth" :)
    
    // if its player 2 we need to make sure that the score comparisons are adequately compared.
    int modifier = 1;
    if (root->boolMax == false)
    {
        modifier = -1;
    }
    
    if (root->numberOfNodes > 0)
    {
        
        int bestScore = modifier*(-AI_MAX); // best score of the children.
        
        int bestScoreIndex = -1; // index of the best move child

        for (int i = 0; i < root->numberOfNodes; i++) // run for each child
        {
            // make the move and check if its a jump move, if not dont bother.
            // reload the root board.
            AITree::currBoard.loadBoardString(root->strBoard); // load the root board.
            
            // we only consider the move if its a jump.
            if (AITree::currBoard.makeMove(root->nodes[i]->strMove).find('J')  !=std::string::npos ) // make the move, get the SAN, if its jump.
            {
                
                int intResult = 0;
                intResult = doAlphaBeta(root->nodes[i], AITree::totalDepth - 1, -AI_MAX, 
                                                            AI_MAX, root->nodes[i]->boolMax) ;

                if (modifier*intResult >= modifier*bestScore)
                {
                    // we know this alpha-beta result is better.
                    bestScore = intResult;
                    bestScoreIndex = i;
                 }
            }
        }
        // at this point, we have the best move of all the children saved in the index.
        if (bestScoreIndex != -1)
            return root->nodes[bestScoreIndex]->strMove;
        else
            return "xx";
    }
    
    return "xx";
}

std::string AITree::getBestMoveAB()
{
    // ASSUME THAT A TREE ALREADY EXISTS.
    // run through the chidren running alpha beta and check for the best move.
    // at the depth of int "depth" :)
    
    // if its player 2 we need to make sure that the score comparisons are adequately compared.
    int modifier = 1;
    if (root->boolMax == false)
    {
        modifier = -1;
    }
    
    if (root->numberOfNodes > 0)
    {
        
        int bestScore = modifier*(-AI_MAX); // best score of the children.
        
        int bestScoreIndex = 0; // index of the best move child

        for (int i = 0; i < root->numberOfNodes; i++) // run for each child
        {
            // TODO prioritise jumps
            //AITree::currBoard.loadBoardString(root->strBoard); // load the root board.
            
            int intResult = 0;
            intResult = doAlphaBeta(root->nodes[i], AITree::totalDepth - 1, -AI_MAX, 
                                                        AI_MAX, root->nodes[i]->boolMax) ;
            
            /*
            if (AITree::currBoard.makeMove(root->nodes[i]->strMove).find('J')  !=std::string::npos )
            {
                // if we made a jump. multiply the result by 2 to prioritise.
                intResult = intResult * 2;
            }
            */
            std::cout << "The move " << root->nodes[i]->strMove << " yielded a score of " << intResult << std::endl;

            if (modifier*intResult >= modifier*bestScore)
            {
                // we know this alpha-beta result is better.
                bestScore = intResult;
                bestScoreIndex = i;
             }
        }
        // at this point, we have the best move of all the children saved in the index.
        return root->nodes[bestScoreIndex]->strMove;
        
    }
    
    return "xx";
}