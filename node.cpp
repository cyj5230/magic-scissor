#include "node.h"

void Node::operator =(double NewCostVal)
{
    Node Temp;
    Temp.totalCost = totalCost = NewCostVal;
    FHN_Assign(Temp);
}

void Node::operator =(FibHeapNode& RHS)
{
    FHN_Assign(RHS);
    totalCost = ((Node&) RHS).totalCost;
}

int  Node::operator ==(FibHeapNode& RHS)
{
    if (FHN_Cmp(RHS)) return 0;
    return totalCost == ((Node&) RHS).totalCost ? 1 : 0;
}

int  Node::operator <(FibHeapNode& RHS)
{
    int X;

    if ((X=FHN_Cmp(RHS)) != 0)
    return X < 0 ? 1 : 0;

    return totalCost < ((Node&) RHS).totalCost ? 1 : 0;
}

int Node::getPQIndex() const
{
    return pqIndex;
}

int& Node::getPQIndex()
{
    return pqIndex;
}
