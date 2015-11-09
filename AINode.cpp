/* 
 * File:   Node.cpp
 * Author: GJ Fouche
 * 
 * Created on 14 September 2015, 9:23 PM
 */

#include "AINode.h"

AINode::AINode(string boardStr, string strMove, int priority, bool ismax, bool jumpOnly)
{
    AINode::strBoard = boardStr;
    AINode::strMove = strMove;
    AINode::priority = priority;
    AINode::boolMax = ismax;
    AINode::numberOfNodes = 0;
    AINode::boolJumpOnly = jumpOnly;
    //for (int i=0; i < 6; i++)
    //    Node::nodes[i] = 0;
    AINode::boolExpanded = false;
}

AINode::AINode(const AINode& orig) {
}

AINode::~AINode() {
}

