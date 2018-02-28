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
void nbrOffset(int linkIndex, int* os);
void costToRGB(QImage* costGraph, int x, int y, double cost);


//initialize the nodes in the node buffer
void MainWindow::initNodeBuffer()
{
    int imgWidth = image->width();
    int imgHeight = image->height();
    int numNodes = imgWidth * imgHeight;
    qDebug()<<"total nodes: "<<numNodes;
    nodes = new Node[numNodes];

    assignCoords(nodes, imgWidth, imgHeight);
    qDebug()<<"assginCoords done";
    computeD(nodes, image, imgWidth, imgHeight);
    qDebug()<<"computeD done";
    double maxD = getMaxD(nodes, imgWidth, imgHeight);
    qDebug()<<"get maxD:"<<maxD;
    computeCost(nodes, imgWidth, imgHeight, maxD);
    qDebug()<<"computeCost done";
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
        imArray imageArray;
        imageArray.setImage(image);
        for(int x = 0; x < imgWidth;x++){
            for(int y = 0; y < imgHeight; y++){
                int nodeIndex = y * imgWidth + x;
                //compute different D for diagonal links, horizontal links, and vertical links
                double dR, dG, dB;
                if(link == 0 || link == 4){
                    //horizontal
                    int** nb = new int*[4];
                    for(int i = 0; i < 4; i++){
                        nb[i] = new int[2];
                    }

                    if(link == 0){
                        //D(link 0)=|(img(i,j-1) + img(i+1,j-1))/2 - (img(i,j+1) + img(i+1,j+1))/2|/2
                        nbrOffset(2, nb[0]);
                        nbrOffset(1, nb[1]);
                        nbrOffset(6, nb[2]);
                        nbrOffset(7, nb[3]);
                    }
                    else{
                        //D(link 4)=|(img(i,j-1) + img(i-1,j-1))/2 - (img(i,j+1) + img(i-1,j+1))/2|/2
                        nbrOffset(2, nb[0]);
                        nbrOffset(3, nb[1]);
                        nbrOffset(6, nb[2]);
                        nbrOffset(5, nb[3]);
                    }

                    dR = abs((imageArray.getRed((y+nb[0][1]) * imgWidth + (x+nb[0][0]))
                            + imageArray.getRed((y+nb[1][1]) * imgWidth + (x+nb[1][0])))/2
                         - (imageArray.getRed((y+nb[2][1]) * imgWidth + (x+nb[2][0]))
                            + imageArray.getRed((y+nb[3][1]) * imgWidth + (x+nb[3][0])))/2)/2;

                    dG = abs((imageArray.getGreen((y+nb[0][1]) * imgWidth + (x+nb[0][0]))
                            + imageArray.getGreen((y+nb[1][1]) * imgWidth + (x+nb[1][0])))/2
                         - (imageArray.getGreen((y+nb[2][1]) * imgWidth + (x+nb[2][0]))
                            + imageArray.getGreen((y+nb[3][1]) * imgWidth + (x+nb[3][0])))/2)/2;

                    dB = abs((imageArray.getBlue((y+nb[0][1]) * imgWidth + (x+nb[0][0]))
                            + imageArray.getBlue((y+nb[1][1]) * imgWidth + (x+nb[1][0])))/2
                         - (imageArray.getBlue((y+nb[2][1]) * imgWidth + (x+nb[2][0]))
                            + imageArray.getBlue((y+nb[3][1]) * imgWidth + (x+nb[3][0])))/2)/2;

                    for(int i = 0; i < 4; i++){
                        delete [] nb[i];
                    }
                    delete [] nb;
                }
                else if(link == 2 || link == 6){
                    //vertical
                    int** nb = new int*[4];
                    for(int i = 0; i < 4; i++){
                        nb[i] = new int[2];
                    }

                    if(link == 2){
                        //D(link 2)=|(img(i-1,j) + img(i-1,j-1))/2 - (img(i+1,j) + img(i+1,j-1))/2|/2
                        nbrOffset(4, nb[0]);
                        nbrOffset(3, nb[1]);
                        nbrOffset(0, nb[2]);
                        nbrOffset(1, nb[3]);
                    }
                    else{
                        //D(link 6)=|(img(i-1,j) + img(i-1,j+1))/2 - (img(i+1,j) + img(i+1,j+1))/2|/2
                        nbrOffset(4, nb[0]);
                        nbrOffset(5, nb[1]);
                        nbrOffset(0, nb[2]);
                        nbrOffset(7, nb[3]);
                    }
                    dR = abs((imageArray.getRed((y+nb[0][1]) * imgWidth + (x+nb[0][0]))
                            + imageArray.getRed((y+nb[1][1]) * imgWidth + (x+nb[1][0])))/2
                         - (imageArray.getRed((y+nb[2][1]) * imgWidth + (x+nb[2][0]))
                            + imageArray.getRed((y+nb[3][1]) * imgWidth + (x+nb[3][0])))/2)/2;

                    dG = abs((imageArray.getGreen((y+nb[0][1]) * imgWidth + (x+nb[0][0]))
                            + imageArray.getGreen((y+nb[1][1]) * imgWidth + (x+nb[1][0])))/2
                         - (imageArray.getGreen((y+nb[2][1]) * imgWidth + (x+nb[2][0]))
                            + imageArray.getGreen((y+nb[3][1]) * imgWidth + (x+nb[3][0])))/2)/2;

                    dB = abs((imageArray.getBlue((y+nb[0][1]) * imgWidth + (x+nb[0][0]))
                            + imageArray.getBlue((y+nb[1][1]) * imgWidth + (x+nb[1][0])))/2
                         - (imageArray.getBlue((y+nb[2][1]) * imgWidth + (x+nb[2][0]))
                            + imageArray.getBlue((y+nb[3][1]) * imgWidth + (x+nb[3][0])))/2)/2;

                    for(int i = 0; i < 4; i++){
                        delete [] nb[i];
                    }
                    delete [] nb;
                }
                else{
                    //diagonal
                    int** nb = new int*[2];
                    for(int i = 0; i < 2; i++){
                        nb[i] = new int[2];
                    }

                    if(link == 1){
                        //D(link 1)=|img(i+1,j) - img(i,j-1)|/sqrt(2)
                        nbrOffset(0, nb[0]);
                        nbrOffset(2, nb[1]);
                    }
                    else if(link == 3){
                        //D(link 3)=|img(i,j-1) - img(i-1,j)|/sqrt(2)
                        nbrOffset(2, nb[0]);
                        nbrOffset(4, nb[1]);

                    }
                    else if(link == 5){
                        //D(link 5)=|img(i-1,j) - img(i,j+1)|/sqrt(2)
                        nbrOffset(4, nb[0]);
                        nbrOffset(6, nb[1]);
                    }
                    else{
                        //D(link 7)=|img(i,j+1) - img(i+1,j)|/sqrt(2)
                        nbrOffset(6, nb[0]);
                        nbrOffset(0, nb[1]);
                    }
                    dR = abs(imageArray.getRed((y+nb[0][1]) * imgWidth + (x+nb[0][0]))
                            - imageArray.getRed((y+nb[1][1]) * imgWidth + (x+nb[1][0])))/sqrt(2);
                    dG = abs(imageArray.getGreen((y+nb[0][1]) * imgWidth + (x+nb[0][0]))
                            - imageArray.getGreen((y+nb[1][1]) * imgWidth + (x+nb[1][0])))/sqrt(2);
                    dB = abs(imageArray.getBlue((y+nb[0][1]) * imgWidth + (x+nb[0][0]))
                            - imageArray.getBlue((y+nb[1][1]) * imgWidth + (x+nb[1][0])))/sqrt(2);

                    for(int i = 0; i < 2; i++){
                        delete [] nb[i];
                    }
                    delete [] nb;
                }
                //D(link) = sqrt( (DR(link)*DR(link)+DG(link)*DG(link)+DB(link)*DB(link))/3 )
                nodes[nodeIndex].linkCost[link] = sqrt((dR * dR + dG * dG + dB * dB)/3);
            }
        }
    }
}

void nbrOffset(int linkIndex, int* os)
{
    //to locate the offset of neighbors
    /*
     * 3 2 1
     * 4   0
     * 5 6 7
    */
//    static int os[2];

    if(linkIndex == 0){
        os[0] = 1;
        os[1] = 0;
    }
    else if(linkIndex == 1){
        os[0] = 1;
        os[1] = -1;
    }
    else if(linkIndex == 2){
        os[0] = 0;
        os[1] = -1;
    }
    else if(linkIndex == 3){
        os[0] = -1;
        os[1] = -1;
    }
    else if(linkIndex == 4){
        os[0] = -1;
        os[1] = 0;
    }
    else if(linkIndex == 5){
        os[0] = -1;
        os[1] = 1;
    }
    else if(linkIndex == 6){
        os[0] = 0;
        os[1] = 1;
    }
    else if(linkIndex == 7){
        os[0] = 1;
        os[1] = 1;
    }

//    return os;
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

void MainWindow::liveWireDP(int seedX, int seedY)
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
            int osX = 0;
            int osY = 0;
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

                            //Update(DecreaseKey)
                            pq.DecreaseKey(nbNode, *nbNode);
                        }
                    }
                }
            }
    }

    }
}

std::list<std::pair<int, int>> MainWindow::minPath(int inputX, int inputY)
{
    //insert a list of nodes along the minimum cost path from the seed node to the input node
    int inputNodeIndex = inputY * this->image->width() + inputX;
    Node* node = &(nodes[inputNodeIndex]);
    std::list<std::pair<int, int>> minPathList;
    while(node->prevNode){
        int col = node->column;
        int row = node->row;
        std::pair<int, int> coords = std::make_pair(col, row);
        minPathList.push_front(coords);
        node = node->prevNode;
    }

    return minPathList;
}

void initNodeState(Node* nodes, int width, int height)
{
    for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                NODE(nodes, x, y, width).state = INITIAL;
            }
        }
}

/*
 * Debug Mode:
 * (a) pixel node
 * (b) cost graph
 * (c) path tree
 * (d) min path
*/

//(a) pixel node
void MainWindow::makePixelNodes(QImage *pixelNodes, int width, int height)
{
    //set all pixels to black
    for (int i = 0; i < pixelNodes->width(); i++) {
        for (int j = 0; j < pixelNodes->height(); j++) {
            pixelNodes->setPixel(i, j, qRgb(0, 0, 0));
        }
    }

    //Draw a cost graph with original image pixel colors at the center of each 3by3 window
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            int newX = 3 * x + 1;
            int newY = 3 * y + 1;

            int pixelIndex = imgarray.vecloc(x, y);
            int pixelR = imgarray.getRed(pixelIndex);
            int pixelG = imgarray.getGreen(pixelIndex);
            int pixelB = imgarray.getBlue(pixelIndex);

            pixelNodes->setPixel(newX, newY, qRgb(pixelR, pixelG, pixelB));
        }
    }
}

//(b) cost graph
void MainWindow::makeCostGraph(QImage *costGraph, int width, int height)
{
    //generate a cost graph from original image and node buffer with all the link costs
    for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                int newX = 3 * x + 1;
                int newY = 3 * y + 1;
                int pixelIndex = imgarray.vecloc(x, y);
                int pixelR = imgarray.getRed(pixelIndex);
                int pixelG = imgarray.getGreen(pixelIndex);
                int pixelB = imgarray.getBlue(pixelIndex);

                costGraph->setPixel(newX, newY, qRgb(pixelR, pixelG, pixelB));

                int** nb = new int*[8];
                for(int i = 0; i < 8; i++){
                    nb[i] = new int[2];

                    nbrOffset(i, nb[i]);

                    //set the RGB value of the neighbors to the cost level
                    costToRGB(costGraph, newX + nb[i][0], newY + nb[i][1], nodes[pixelIndex].linkCost[i]);

                    delete [] nb[i];
                }
                delete [] nb;
            }
    }
}


void costToRGB(QImage* costGraph, int x, int y, double cost)
{
    //set the rgb value of the pixel from 0 to 255
    //based on the given cost
    int costRGB = (int)(floor(__max(0.0, __min(255.0, cost))));
    costGraph->setPixel(x, y, qRgb(costRGB, costRGB, costRGB));
}
