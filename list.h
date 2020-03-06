//John Sullivan
//CSC212
//Instructor: Marco Alvarez
//15 November 2018

#ifndef _PROTEINHEADER_
#define _PROTEINHEADER_

#ifndef NULL
#define NULL 0x00
#endif

#include <string>

//This class creates nodes for my linked list.
class Node {
    private:
        double x;
        double y;
        double z;
        std::string chain;

        Node *next;
    public:
        Node();
        Node(double, double, double, std::string);
        ~Node();

    friend class Protein;
};

//This class handles all calculations and storing of data.
class Protein {
    private:
        Node *head;
        Node *curr;
        unsigned int size = 0;
    public:
        Protein();
        ~Protein();

        void append(double, double, double, std::string);
        void print();
        double eucDist(double, double, double, double, double, double);
        int getSize();
        void minDist();
};

#endif