#ifndef NODE_H
#define NODE_H

#include "fibheap.h"
const int INITIAL = 0;
const int ACTIVE = 1;
const int EXPANDED = 2;


class Node : public FibHeapNode
{
public:
    double linkCost[8];

    int state;//state: 0-INITIAL, 1-ACTIVE, 2-EXPANDED
    double totalCost;
    Node *prevNode;

    int prevNodeLink;//prevNode's link index to this node
    int column, row;
    int pqIndex;

    Node() : FibHeapNode() { prevNode = nullptr; prevNodeLink = -1;state = INITIAL; totalCost = -1;}

    virtual void operator =(FibHeapNode& RHS);
    virtual int  operator ==(FibHeapNode& RHS);
    virtual int  operator <(FibHeapNode& RHS);

    virtual void operator =(double NewTotalCost);
    double GetCostValue() { return totalCost; }
    void SetCostValue(double incost) { totalCost = incost; }

    int getPQIndex() const;
    int& getPQIndex();
};
#endif // NODE_H
