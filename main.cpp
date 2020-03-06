//John Sullivan
//CSC212
//Instructor: Marco Alvarez
//15 November 2018

#include "list.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <sstream>

int main(int argc, char* argv[]){
    //Error checking.
    if(argc < 2){
        std::cout << "Must provide a valid PDB file name." << std::endl;
    }
    //Create a variable to hold the input PDB file.
    std::ifstream inFile(argv[1]);

    //These variables will be used to read lines in the input file.
    std::string str;
    std::string word;

    //To be able to use my class, I created this variable p.
    Protein p;

    int i = 0;
    double x = 0;
    double y = 0;
    double z = 0;
    std::string chain;
    bool isATOM = false;
    bool isCA = false;

    //This loop will skip over anything thats not an ATOM and only checks ...
    //... certain words, such as the CA types only, and then stores them in linked list.
    while(getline(inFile, str)){
        i = 0;
        std::istringstream read(str);
        while(read >> word){
            if(i == 0){
                if(word == "ATOM") isATOM = true;
                else break;
            }
            if(isATOM){
                if(i == 2){
                    if(word == "CA"){
                        isCA = true;
                    }
                    else break;
                }
                if(isCA){
                    if(i == 4){
                        chain = word;
                    }
                    else if(i == 6){
                        x = atof(word.c_str());
                    }
                    else if(i == 7){
                        y = atof(word.c_str());
                    }
                    else if(i == 8){
                        z = atof(word.c_str());
                        i = 0;
                        isCA = false;
                        isATOM = false;
                        //Here is where I store my atom nodes in the linekd list.
                        p.append(x, y, z, chain);
                    }
                }
            }
            i++;
        }
    }
    inFile.close();

    //This was for testing.
    //p.print();

    //OUTPUT
    int size = p.getSize();

    //Calls my function to do all calculations and store data in files.
    p.minDist();

    return 0;
}

