// This file should be accessed from mainwindow.cpp
#ifndef MAINWINDOW
#include "mainwindow.cpp"
#endif

#include <QVector>
#include <QImage>
#include "node.h"
#include "fibheap.h"
#include "math.h"
#include <assert.h>

//define the length of 8 links
const double linkLength[8] = {1.0, sqrt(2), 1.0, sqrt(2), 1.0, sqrt(2), 1.0, sqrt(2)};

void assignCoords (Node* nodes, int imgWidth, int imgHeight);
void computeD (Node* nodes, QImage* image, int imgWidth, int imgHeight);
double getMaxD (Node* nodes, int imgWidth, int imgHeight);
void computeCost (Node* nodes, int imgWidth, int imgHeight, double maxD);
void initNodeState(Node* nodes, int width, int height);

//initialize the nodes in the node buffer
void MainWindow::initNodeBuffer(Node* nodes, QImage* image)
{
    int imgWidth = image->width();
    int imgHeight = image->height();

    assignCoords(nodes, imgWidth, imgHeight);
    computeD(nodes, image, imgWidth, imgHeight);
    double maxD = getMaxD(nodes, imgWidth, imgHeight);
    computeCost(nodes, imgWidth, imgHeight, maxD);
}

//return the row and column values of each node
void assignCoords(Node *nodes, int imgWidth, int imgHeight)
{
    for (int x = 0; x < imgWidth; ++x) {
            for (int y = 0; y < imgHeight; ++y) {
                int nodeIndex = y*imgWidth + x;
                nodes[nodeIndex].column = x;
                nodes[nodeIndex].row = y;
            }
        }
}

void computeD(Node *nodes, QImage *image, int imgWidth, int imgHeight)
{

}

double getMaxD(Node *nodes, int imgWidth, int imgHeight)
{

}

void computeCost(Node *nodes, int imgWidth, int imgHeight, double maxD)
{

}

static int offsetToLinkIndex(int dx, int dy)
{
    int indices[9] = { 3, 2, 1, 4, -1, 0, 5, 6, 7 };
    int tmp_idx = (dy + 1) * 3 + (dx + 1);
    assert(tmp_idx >= 0 && tmp_idx < 9 && tmp_idx != 4);
    return indices[tmp_idx];
}

inline Node& NODE(Node* n, int i, int j, int width)
{
    return *(n + j * width + i);
}

void MainWindow::liveWireDP(int seedX, int seedY, Node *nodes, int expanded)
{
    int width = image->width();
    int height = image->height();

    FibHeap pq;
    Node* seed = &(NODE(nodes, seedX, seedY, width));
    //set the total cost of seed to be zero
    //make seed the root of the minimum path tree ( pointing to NULL )
    seed->SetCostValue(0);
    seed->prevNode = NULL;

    pq.Insert(seed);

    //while pq is not empty
    while (pq.GetNumNodes()!=0) {
        Node* minCostNode;
        minCostNode = (Node*)pq.ExtractMin();
        minCostNode->state = EXPANDED;

        for(int link = 0; link < 8; link++){
            int osX, osY;
            minCostNode->nbrOffset(osX, osY, link);

            int nbX = minCostNode->column + osX;
            int nbY = minCostNode->row + osY;

            if((nbX >= 0 && nbX < width) && (nbY >= 0 && nbY < height)){
                Node* nbNode = &(NODE(nodes, nbX, nbY, width));

                if(nbNode->state != EXPANDED){
                    if(nbNode->state == INITIAL){
                        //make q be the predecessor of r ( for the the minimum path tree )
                        nbNode->prevNode = minCostNode;

                        //set the total cost of r to be the sum of the total cost of q and link cost from q to r as its total cost
                        nbNode->SetCostValue(minCostNode->totalCost + minCostNode->linkCost[link]);

                        pq.Insert(nbNode);
                        nbNode->state = ACTIVE;
                    }
                    else{
                        double tmpCost = minCostNode->totalCost + minCostNode->linkCost[link];
                        if(tmpCost < nbNode->totalCost){

                            //update q to be the predecessor of r ( for the minimum path tree )
                            nbNode->prevNode = minCostNode;

                            //update the total cost of r in pq                            
                            nbNode->SetCostValue(tmpCost);
                            //not match here
                            pq.DecreaseKey(minCostNode, *nbNode);
                        }
                    }
                }
            }
    }

    }
}
