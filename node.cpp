#include "Node.h"

Node::Node()
{
    prevNode = nullptr;
}

void Node::nbrOffset(int& osX, int& osY, int linkIndex)
{
    //to locate the offset of neighbors
    /*
     * 3 2 1
     * 4   0
     * 5 6 7
    */
    switch (linkIndex) {
    case 0:
        osX = 1;
        osY = 0;
        break;
    case 1:
        osX = 1;
        osY = -1;
        break;
    case 2:
        osX = 0;
        osY = -1;
        break;
    case 3:
        osX = -1;
        osY = -1;
        break;
    case 4:
        osX = -1;
        osY = 0;
        break;
    case 5:
        osX = -1;
        osY = 1;
        break;
    case 6:
        osX = 0;
        osY = 1;
        break;
    case 7:
        osX = 1;
        osY = 1;
        break;
    default:
        break;
    }
}

int Node::getPQIndex() const
{
    return pqIndex;
}

int& Node::getPQIndex()
{
    return pqIndex;
}
