/* 
 * File:   Node.h
 * Author: GJ Fouche
 *
 * Created on 14 September 2015, 9:23 PM
 */

#ifndef NODE_H
#define	NODE_H

#include <string>

using namespace std;


class AINode {
public:
    AINode(string boardStr, string strMove, int priority, bool ismax, bool jumpOnly);
    AINode(const AINode& orig);
    virtual ~AINode();
        
    AINode * nodes[125]; // array of child nodes. assuming 125 possible moves for each player..
    int numberOfNodes;
    int priority; // priority of THIS node.
    
    bool boolMax; // is this a min or max node?
    string strMove; // string with the move.
    string strBoard; // the board FEN string.
    bool boolExpanded; // has this node been expanded ? used for alpha-beta.
    
    bool boolJumpOnly;
private:
    

};

#endif	/* NODE_H */

