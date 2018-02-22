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
    //state: 0-INITIAL, 1-ACTIVE, 2-EXPANDED
    int state;
    double totalCost;
    Node *prevNode;
    int column, row;
    int pqIndex;

    Node() : FibHeapNode() { prevNode = nullptr; state = INITIAL;}

    virtual void operator =(FibHeapNode& RHS);
    virtual int  operator ==(FibHeapNode& RHS);
    virtual int  operator <(FibHeapNode& RHS);

    virtual void operator =(double NewTotalCost);
    double GetCostValue() { return totalCost; }
    void SetCostValue(double incost) { totalCost = incost; }

    void nbrOffset(int osX, int osY, int linkIndex);
    int getPQIndex() const;
    int& getPQIndex();
};
#endif // NODE_H
