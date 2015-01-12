#include "HoffTree.h"

HoffTree::HoffTree(vector<ProbData> *probArray) {
    this->root = NULL;

    for (int i = 0, n = probArray->size(); i < n; i++) {
        this->addToLinkedList(probArray[0][i]); // adding the probability data to the linked list
    }
    this->completeEncodeTree();// completing the tree untill only there is only one element in the linked list
}

HoffTree::~HoffTree(void) {
    this->recDel(this->root);
    this->root = NULL;
}

vector<HoffCode> *HoffTree::codeArray(void) {
    vector<HoffCode> *toReturn = new vector<HoffCode>;
    this->recCodeArray("", this->root, toReturn);
    return toReturn;
}

string HoffTree::decode(vector<byte> *bytesToDecode, int extraBits) {
    string toReturn;
    vector<bool> *bitRep = this->makeArrayOfBits(bytesToDecode);
    int len = bitRep->size() - extraBits;
    HoffNode *ptr = this->root;

    for (int i = 0; i < len; i++) {
        ptr = ptr->child[bitRep[0][i]];
        if (!ptr->child[0] || !ptr->child[1]) { // if we reach the final element in the structure
            toReturn += ptr->getProbData().getAlpha();
            ptr = this->root;
        }
    }
    delete bitRep;
    return toReturn;
}

void HoffTree::completeEncodeTree(void) {
    HoffNode *ptr[2] = { NULL };
    while (this->root->next) {
        ptr[0] = this->root;
        ptr[1] = this->root->next;
        this->root = ptr[1]->next;

        // the ProbData structure to add;
        ProbData newProb;
        newProb.setProb(ptr[0]->getProbData().getProb() + ptr[1]->getProbData().getProb());

        // setting the next of child nodes to NULL
        ptr[0]->next = NULL;
        ptr[1]->next = NULL;

        HoffNode *toEnter = new HoffNode(newProb, ptr[0], ptr[1]);
        this->addToLinkedList(toEnter);
    }
}

void HoffTree::recDel(HoffNode *ptr) {
    if (!ptr) {
        return;
    }
    this->recDel(ptr->next);
    this->recDel(ptr->child[0]);
    this->recDel(ptr->child[1]);
    delete ptr;
}

void HoffTree::addToLinkedList(ProbData dataToEnter) {
    HoffNode *toAdd = new HoffNode(dataToEnter);
    this->addToLinkedList(toAdd);
}

void HoffTree::addToLinkedList(HoffNode *toAdd) {
    int probToCheck = toAdd->getProbData().getProb();

    if (!this->root) { // if no data exists
        this->root = toAdd;
    } else {
        HoffNode *ptr = this->root;
        HoffNode *prev = NULL;

        while (ptr && (ptr->getProbData().getProb() < probToCheck)) { // if the pointer exists and the data we want to enter is less than the pointer data
            prev = ptr;
            ptr = ptr->next;
        }
        toAdd->next = ptr;
        if (prev) {
            prev->next = toAdd;
        } else {
            this->root = toAdd;
        }
    }
}

void HoffTree::recCodeArray(string preCode, HoffNode *ptr, vector<HoffCode> *toReturn) {
    if (!ptr->child[0] && !ptr->child[1]) {
        HoffCode toAdd(ptr->getProbData().getAlpha(), preCode);
        toReturn->push_back(toAdd);
    }
    else {
        this->recCodeArray(preCode + "0", ptr->child[0], toReturn);
        this->recCodeArray(preCode + "1", ptr->child[1], toReturn);
    }
}

bool *HoffTree::makeArrayOfBits(byte toConvert) {
    bool *toReturn = new bool[8];
    for (int i = 7; i >= 0; i--) {
        toReturn[i] = toConvert % 2;
        toConvert /= 2;
    }
    return toReturn;
}

vector<bool> *HoffTree::makeArrayOfBits(vector<byte> *bytesToDecode) {
    vector<bool> *toReturn = new vector <bool>;
    for (int i = 0, n = bytesToDecode->size(); i < n; i++) {
        bool *temp = this->makeArrayOfBits(bytesToDecode[0][i]);
        for (int i = 0; i < 8; i++) {
            toReturn->push_back(temp[i]);
        }
        delete temp;
    }
    return toReturn;
}
