//John Sullivan
//CSC212
//Instructor: Marco Alvarez
//15 November 2018

#include "list.h"
#include <iostream>
#include <string>
#include <cmath>
#include <fstream>

//Node default constructor
Node::Node(){
    x = 0;
    y = 0;
    z = 0;
    chain = " ";
}

//Node constructor to build atoms with given xyz coordinates and a chain ID.
Node::Node(double _x, double _y, double _z, std::string chainID){
    x = _x;
    y = _y;
    z = _z;
    chain = chainID;
}

//Destructor that isn't used. (For deleting allocated memory, but I'm not doing that)
Node::~Node(){

}

//Function to append nodes, given some data.
void Protein::append(double x, double y, double z, std::string chain) {
    Node *n = new Node(x, y, z, chain);
    if(head == NULL){
        head = curr = n;
        n->next = head;
    }
    else
    {
        curr->next = n;
        curr = n;
    }
    //This size variable isn't necessary, but I implemented it because I thought it might be useful at some point.
    size++;
}

//Default constructor for a protein node.
Protein::Protein(){
    head = NULL;
    curr = NULL;
}

//Destructor for protein nodes. Never used.
Protein::~Protein(){

}

//This function was to just make sure that I was getting the correct data in my linked list.
//This is a local testing method.
void Protein::print(){
    Node *n = head;
    for (int i = 0; i < size; i++) {
        std::cout << n->x << ',' << n->y << ',' << n->z << ',' << n->chain <<std::endl;
        n = n->next;
    }
}

//This function calculates the Euclidian Distance between two given points.
//distance(point1, point2) = square root ((p1X - p2X)^2 + (p1Y - p2Y)^2 + (p1Z - p2Z)^2)
double Protein::eucDist(double x1, double y1, double z1, double x2, double y2, double z2){
    double eucX = x1 - x2;
    double eucY = y1 - y2;
    double eucZ = z1 - z2;
    double distance = pow(eucX, 2) + pow(eucY, 2) + pow(eucZ, 2);
    distance = sqrt(distance);
    return distance;
}

//This function calculates ALL nearest neighbors and puts them in order next to eachother, along with their
//  .. colors in the files "coords.js" and "colors.js"
void Protein::minDist(){

    //I open the files here because it would have been more complicated to pass them as parameters.
    std::ofstream outFile;
    std::ofstream outFile2;
    outFile.open("coords.js");
    outFile2.open("colors.js");
    outFile << "var coords = [\n";
    outFile2 << "var colors =[\n";

    //I initialize two pointers for indexing in the linked list, because I want to be able to compare ...
    // ... the first idx (node) with the rest of the linked list (idx2), and then increment idx each time to ...
    // ... find the nearest neighbors.
    Node *idx = head;
    Node *idx2 = head;

    //This will keep track of each compared distance
    double dist = 0;

    //This will store the node that has the minimum euclidian distance for printing
    Node *nearest = idx2->next;

    //Nested while loop to find the minimum euclidian distance for each point...
    // ... and also store both the compared node and the nearest neighbor in a file.
    while(idx!=NULL){
        idx2 = head;
        //This is so I don't compare the same node.
        if(idx == idx2){
            idx2 = idx2->next;
        }
        //initializer for the minimum distance variable.
        double minDist = eucDist(idx->x, idx->y, idx->z, idx2->x, idx2->y, idx2->z);
        //Prints the first point to the file.
        outFile << '\t' << idx->x << ',' << idx->y << ',' << idx->z << ',';
        //Determine the color of the node, and store it in a seperate file
        switch(idx->chain[0]){
            case 'A': outFile2 << "\t0, 0, 1, ";
            break;
            case 'B': outFile2 << "\t0, 1, 0, ";
            break;
            case 'C': outFile2 << "\t1, 0, 0, ";
            break;
            case 'D': outFile2 << "\t1, 1, 0, ";
            break;
            case 'E': outFile2 << "\t1, 1, 1, ";
            break;
            default: outFile2 << "\t1, 0.5, 0, ";
        }
        while(idx2->next!=NULL){
            if(idx == idx2 && idx2->next != NULL){
                //don't compare, move index2 first
                idx2 = idx2->next;
            }
            //Calculates every single node to check for nearest neighbor.
            dist = eucDist(idx->x, idx->y, idx->z, idx2->x, idx2->y, idx2->z);
            if(dist <= minDist){
                minDist = dist;
                nearest = idx2;
            }
            if(idx2->next != NULL) idx2 = idx2->next;
        }
        //Prints the second (nearest neighbor) node to file, along with the color
        outFile << nearest->x << ',' << nearest->y << ',' << nearest->z << ',' << std::endl;
        switch(nearest->chain[0]){
            case 'A': outFile2 << "0, 0, 1,\n";
            break;
            case 'B': outFile2 << "0, 1, 0,\n";
            break;
            case 'C': outFile2 << "1, 0, 0,\n";
            break;
            case 'D': outFile2 << "1, 1, 0,\n";
            break;
            case 'E': outFile2 << "1, 1, 1,\n";
            break;
            default: outFile2 << "1, 0.5, 0,\n";
        }
        //Move the pointer to be compared.
        idx = idx->next;
    }
    outFile << "];";
    outFile2 << "];";
    outFile.close();
    outFile2.close();
}

//This was just for testing purposes.
int Protein::getSize(){
    return this->size;
}

