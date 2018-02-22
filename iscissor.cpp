// This file should be accessed from mainwindow.cpp
#ifndef MAINWINDOW
#include "mainwindow.cpp"
#endif

#include <QVector>
#include <QImage>
#include "node.h"
#include "fibheap.h"
#include "math.h"
#include "imagearray.h"
#include <assert.h>

//define the length of 8 links
const double linkLength[8] = {1.0, sqrt(2), 1.0, sqrt(2), 1.0, sqrt(2), 1.0, sqrt(2)};

void assignCoords (Node* nodes, int imgWidth, int imgHeight);
void computeD (Node* nodes, QImage* image, int imgWidth, int imgHeight);
double getMaxD (Node* nodes, int imgWidth, int imgHeight);
void computeCost (Node* nodes, int imgWidth, int imgHeight, double maxD);
void initNodeState(Node* nodes, int width, int height);
int* nbrOffset(int linkIndex);

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
    for(int link = 0; link < 8; link++){
        imArray imageArray(image);
        for(int x = 0; x < imgWidth;x++){
            for(int y = 0; y < imgHeight; y++){
                int nodeIndex = y * imgWidth + x;
                //compute different D for diagonal links, horizontal links, and vertical links
                double dR, dG, dB;
                if(link == 0 || link == 4){
                    //horizontal
                    int *nb0 = new int;
                    int *nb1 = new int;
                    int *nb2 = new int;
                    int *nb3 = new int;

                    if(link == 0){
                        //D(link 0)=|(img(i,j-1) + img(i+1,j-1))/2 - (img(i,j+1) + img(i+1,j+1))/2|/2
                        nb0 = nbrOffset(2);
                        nb1 = nbrOffset(1);
                        nb2 = nbrOffset(6);
                        nb3 = nbrOffset(7);
                    }
                    else{
                        //D(link 4)=|(img(i,j-1) + img(i-1,j-1))/2 - (img(i,j+1) + img(i-1,j+1))/2|/2
                        nb0 = nbrOffset(2);
                        nb1 = nbrOffset(3);
                        nb2 = nbrOffset(6);
                        nb3 = nbrOffset(5);
                    }
                    dR = abs((imageArray.getRed((y+nb0[1]) * imgWidth + (x+nb0[0]))
                            + imageArray.getRed((y+nb1[1]) * imgWidth + (x+nb1[0])))/2
                         - (imageArray.getRed((y+nb2[1]) * imgWidth + (x+nb2[0]))
                            + imageArray.getRed((y+nb3[1]) * imgWidth + (x+nb3[0])))/2)/2;

                    dG = abs((imageArray.getGreen((y+nb0[1]) * imgWidth + (x+nb0[0]))
                            + imageArray.getGreen((y+nb1[1]) * imgWidth + (x+nb1[0])))/2
                         - (imageArray.getGreen((y+nb2[1]) * imgWidth + (x+nb2[0]))
                            + imageArray.getGreen((y+nb3[1]) * imgWidth + (x+nb3[0])))/2)/2;

                    dB = abs((imageArray.getBlue((y+nb0[1]) * imgWidth + (x+nb0[0]))
                            + imageArray.getBlue((y+nb1[1]) * imgWidth + (x+nb1[0])))/2
                         - (imageArray.getBlue((y+nb2[1]) * imgWidth + (x+nb2[0]))
                            + imageArray.getBlue((y+nb3[1]) * imgWidth + (x+nb3[0])))/2)/2;

                    delete[] nb0;
                    delete[] nb1;
                    delete[] nb2;
                    delete[] nb3;
                }
                else if(link == 2 || link == 6){
                    //vertical
                    int *nb0 = new int;
                    int *nb1 = new int;
                    int *nb2 = new int;
                    int *nb3 = new int;

                    if(link == 2){
                        //D(link 2)=|(img(i-1,j) + img(i-1,j-1))/2 - (img(i+1,j) + img(i+1,j-1))/2|/2
                        nb0 = nbrOffset(4);
                        nb1 = nbrOffset(3);
                        nb2 = nbrOffset(0);
                        nb3 = nbrOffset(1);
                    }
                    else{
                        //D(link 6)=|(img(i-1,j) + img(i-1,j+1))/2 - (img(i+1,j) + img(i+1,j+1))/2|/2
                        nb0 = nbrOffset(4);
                        nb1 = nbrOffset(5);
                        nb2 = nbrOffset(0);
                        nb3 = nbrOffset(7);
                    }
                    dR = abs((imageArray.getRed((y+nb0[1]) * imgWidth + (x+nb0[0]))
                            + imageArray.getRed((y+nb1[1]) * imgWidth + (x+nb1[0])))/2
                         - (imageArray.getRed((y+nb2[1]) * imgWidth + (x+nb2[0]))
                            + imageArray.getRed((y+nb3[1]) * imgWidth + (x+nb3[0])))/2)/2;

                    dG = abs((imageArray.getGreen((y+nb0[1]) * imgWidth + (x+nb0[0]))
                            + imageArray.getGreen((y+nb1[1]) * imgWidth + (x+nb1[0])))/2
                         - (imageArray.getGreen((y+nb2[1]) * imgWidth + (x+nb2[0]))
                            + imageArray.getGreen((y+nb3[1]) * imgWidth + (x+nb3[0])))/2)/2;

                    dB = abs((imageArray.getBlue((y+nb0[1]) * imgWidth + (x+nb0[0]))
                            + imageArray.getBlue((y+nb1[1]) * imgWidth + (x+nb1[0])))/2
                         - (imageArray.getBlue((y+nb2[1]) * imgWidth + (x+nb2[0]))
                            + imageArray.getBlue((y+nb3[1]) * imgWidth + (x+nb3[0])))/2)/2;

                    delete[] nb0;
                    delete[] nb1;
                    delete[] nb2;
                    delete[] nb3;
                }
                else{
                    //diagonal
                    int *nb0 = new int;
                    int *nb1 = new int;
                    if(link == 1){
                        //D(link 1)=|img(i+1,j) - img(i,j-1)|/sqrt(2)
                        nb0 = nbrOffset(0);
                        nb1 = nbrOffset(2);
                    }
                    else if(link == 3){
                        //D(link 3)=|img(i,j-1) - img(i-1,j)|/sqrt(2)
                        nb0 = nbrOffset(2);
                        nb1 = nbrOffset(4);

                    }
                    else if(link == 5){
                        //D(link 5)=|img(i-1,j) - img(i,j+1)|/sqrt(2)
                        nb0 = nbrOffset(4);
                        nb1 = nbrOffset(6);
                    }
                    else{
                        //D(link 7)=|img(i,j+1) - img(i+1,j)|/sqrt(2)
                        nb0 = nbrOffset(6);
                        nb1 = nbrOffset(0);
                    }
                    dR = abs(imageArray.getRed((y+nb0[1]) * imgWidth + (x+nb0[0]))
                            - imageArray.getRed((y+nb1[1]) * imgWidth + (x+nb1[0])))/sqrt(2);
                    dG = abs(imageArray.getGreen((y+nb0[1]) * imgWidth + (x+nb0[0]))
                            - imageArray.getGreen((y+nb1[1]) * imgWidth + (x+nb1[0])))/sqrt(2);
                    dB = abs(imageArray.getBlue((y+nb0[1]) * imgWidth + (x+nb0[0]))
                            - imageArray.getBlue((y+nb1[1]) * imgWidth + (x+nb1[0])))/sqrt(2);

                    delete[] nb0;
                    delete[] nb1;
                }
                //D(link) = sqrt( (DR(link)*DR(link)+DG(link)*DG(link)+DB(link)*DB(link))/3 )
                nodes[nodeIndex].linkCost[link] = sqrt((dR * dR + dG * dG + dB * dB)/3);
            }
        }
    }
}

int* nbrOffset(int linkIndex)
{
    //to locate the offset of neighbors
    /*
     * 3 2 1
     * 4   0
     * 5 6 7
    */
    int os[2];
    switch (linkIndex) {
    case 0:
        os[0] = 1;
        os[1] = 0;
        break;
    case 1:
        os[0] = 1;
        os[1] = -1;
        break;
    case 2:
        os[0] = 0;
        os[1] = -1;
        break;
    case 3:
        os[0] = -1;
        os[1] = -1;
        break;
    case 4:
        os[0] = -1;
        os[1] = 0;
        break;
    case 5:
        os[0] = -1;
        os[1] = 1;
        break;
    case 6:
        os[0] = 0;
        os[1] = 1;
        break;
    case 7:
        os[0] = 1;
        os[1] = 1;
        break;
    default:
        break;
    }
}

double getMaxD(Node *nodes, int imgWidth, int imgHeight)
{
    double maxD = 0.0000;
    for(int x = 0; x < imgWidth; x++){
        for(int y = 0; y < imgHeight; y++){
            int nodeIndex = y * imgWidth + x;
            for(int link = 0; link < 8; link++){
                if(nodes[nodeIndex].linkCost[link] > maxD){
                    maxD = nodes[nodeIndex].linkCost[link];
                }
            }
        }
    }
    return maxD;
}

void computeCost(Node *nodes, int imgWidth, int imgHeight, double maxD)
{    
    double length = 1.0000;
    for(int x = 0; x < imgWidth; x++){
        for(int y = 0; y < imgHeight; y++){
            int nodeIndex = y * imgWidth + x;
            for(int link = 0; link < 8; link++){
                //for link with index 1, 3, 5, 7
                if(link%2 == 1){
                    length = sqrt(2);
                }
                //cost(link) = (maxD - D(link)) * length(link)
                nodes[nodeIndex].linkCost[link] = (maxD - nodes[nodeIndex].linkCost[link]) * length;
            }
        }
    }
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

                        //insert r in pq and mark it as ACTIVE
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

                            //still not sure how to use
                            //Update(DecreaseKey)
                            pq.DecreaseKey(nbNode, *nbNode);
                        }
                    }
                }
            }
    }

    }
}

void MainWindow::minPath(FibHeap* path, int inputX, int inputY, Node* nodes, int width, int height)
{
    int inputNodeIndex = inputY * width + inputX;
    Node* currentNode = &(nodes[inputNodeIndex]);
    while(currentNode != nullptr){
        //the input node should be the tail
        //not sure here
        //path->AddHead(currentNode);
        currentNode = currentNode->prevNode;
    }
}

void initNodeState(Node* nodes, int width, int height)
{
    for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                NODE(nodes, x, y, width).state = INITIAL;
            }
        }
}

void MainWindow::MakeCostGraph(QImage *costGraph, const Node* nodes, const QImage *image, int width, int height)
{
    int graphWidth = width * 3;
    int graphHeight = height * 3;
    int dgX = 3;
    int dgY = 3 * graphWidth;

    for (int x = 0; x < width; ++x) {
            for (int y = 0; y < height; ++y) {
                int nodeIndex = y*width + x;
//                int imgIndex = 3 * nodeIndex;
//                int costIndex = 3 * ((3 * j + 1) * graphWidth + (3 * i + 1));

//                const Node* node = nodes + nodeIndex;
//                const unsigned char* pxl = img + imgIndex;
//                unsigned char* cst = costGraph + costIndex;

//                cst[0] = pxl[0];
//                cst[1] = pxl[1];
//                cst[2] = pxl[2];

//                //r,g,b channels are grad info in seperate channels;
//                DigitizeCost(cst	   + dgX, node->linkCost[0]);
//                DigitizeCost(cst - dgY + dgX, node->linkCost[1]);
//                DigitizeCost(cst - dgY      , node->linkCost[2]);
//                DigitizeCost(cst - dgY - dgX, node->linkCost[3]);
//                DigitizeCost(cst	   - dgX, node->linkCost[4]);
//                DigitizeCost(cst + dgY - dgX, node->linkCost[5]);
//                DigitizeCost(cst + dgY	   ,  node->linkCost[6]);
//                DigitizeCost(cst + dgY + dgX, node->linkCost[7]);
            }
    }
}
