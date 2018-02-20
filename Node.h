#ifndef NODE_H
#define NODE_H

const int INITIAL = 0;
const int ACTIVE = 1;
const int EXPANDED = 2;


class Node
{
public:
    explicit Node();
    int getPQIndex() const;
    int& getPQIndex();
    void nbrOffset(int& osX, int& osY, int linkIndex);

private:
    double linkCost[8];
    //state: 0-INITIAL, 1-ACTIVE, 2-EXPANDED
    int state;
    double totalCost;
    Node *prevNode;
    int column, row;
    int pqIndex;
};

Node::Node()
{
    prevNode = NULL;
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
#endif // PIXELNODE_H
