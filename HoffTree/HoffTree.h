#ifndef HOFFTREE_H
#define HOFFTREE_H

#include <iostream>
#include <vector>
#include <string>
#include <cstdint>

using namespace std;

#include "../ProbData/ProbData.h"
#include "../HoffNode/HoffNode.h"

typedef uint8_t byte;

class HoffTree{
    HoffNode *root; // the root of the HoffTree

    /*
    *   Recursively deletes Nodes of the tree passed in as a parameter
    */
    void recDel(HoffNode *ptr);

    /*
    *   This overloaded method makes a HoffNode with the given parameter
    *   and then calls the other overloaded function passing in this newly formed HoffNode pointer.
    */
    void addToLinkedList(ProbData dataToEnter);

    /*
    *   This overloaded method takes in a pointer of HoffNode,
    *   and adds in the Link List in increasing order of probability
    */
    void addToLinkedList(HoffNode *toAdd);

    /*
    *   This private method completly makes the HoffTree.
    *   After the linked list of probabilty of character has been made
    *   It selectes two Nodes from the begining and adds their probability and creates a new Node
    *   with these two Nodes as its children and adds in the linked list untill only one element;
    *   remains in the linked list
    */
    void completeEncodeTree(void);

    /*
    *   This method recursively finds the code of all the alphabets by traversing all the paths of
    *   the HoffTree and when a leaf is encountered it adds the currently traveresed code and alphabet,
    *   in a HofCode struct and its to the vector pointer passed in as a parameter
    *   Here 'preCode' is code traversed uptill now
    *   'ptr' the node to traverse
    *   'toReturn' the vector of codes to return
    */
    void recCodeArray(string preCode, HoffNode *ptr, vector<HoffCode> *toReturn);

    //////////////////// The Below two functions are used for decoding bytes ////////////////////
    /*
    *   It returns an array of size 8 containing bit representation of the byte passed in as a parameter
    */
    bool *makeArrayOfBits(byte toConvert);

    /*
    *   This method makes an vector of bits from the vector of bytes passed in as a parameter
    */
    vector<bool> *makeArrayOfBits(vector<byte> *bytesToDecode);

public:
    /*
    *   Only constructor of HoffTree class takes in a vector containing ProbDatas
    *   The method further calls helper function like completeEncodeTree() to complete the
    *   HoffTree which is a binary tree with nodes conatining alphabets
    */
    HoffTree(vector<ProbData> *probArray);

    /*
    *   Destructor of the HoffTree Class.
    *   Recursively deletes all the HoffNodes in the tree
    */
    ~HoffTree(void);

    /*
    *   Returns a vector of HoffCode containing the Codes of alphabets,
    *   which were passed in as a parameter in Constructor
    */
    vector<HoffCode> *codeArray(void);

    /*
    *   Decodes a given vector of Bytes to returns a string representation.
    *   It is used in Decoding of HoffMan Module where the bytes collected in the file,
    *   are passed in as a parameter along with the number of extra bits padded at the end,
    *   to make number of bits divisible by 8.
    */
    string decode(vector<byte> *bytesToDecode, int extraBits);
};

#endif // HOFFTREE_H
