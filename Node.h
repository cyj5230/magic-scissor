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
#endif // PIXELNODE_H
