#ifndef HOFFNODE_H
#define HOFFNODE_H

#include <iostream>

#include "../ProbData/ProbData.h"

/*
*   The struct representing the HoffCode of a given alphabet
*   The code generated for a alphabet is stored in this structure.
*/
struct HoffCode {
    char alpha = 0;
    std::string code = "";

    HoffCode(char alpha, std::string code) {
        this->alpha = alpha;
        this->code = code;
    }
};

class HoffNode {
    ProbData data; // the probability data stored in this hoffNode
public:
    HoffNode *next; // the next HoffNode in the Linked List
    HoffNode *child[2]; // the two children of this HoffNode

    /*
    *   Constructor of the HoffNode with one parameter
    *   Sets the values of data variable to given parameter
    *   Sets NULL to the given pointers
    */
    HoffNode(ProbData data);

    /*
    *   Overloaded Constructor of HoffNode with three parameters
    *   Sets the values of all the variables to the given parameters
    */
    HoffNode(ProbData data, HoffNode *left, HoffNode *right);

    /*
    *   Getter function of 'data' variable
    */
    ProbData getProbData(void);
};
#endif // HOFFNODE_H
