#include "HoffNode.h"

HoffNode::HoffNode(ProbData data):data(data) {
    this->next = NULL;
    this->child[0] = NULL;
    this->child[1] = NULL;
}

HoffNode::HoffNode(ProbData data, HoffNode *left, HoffNode *right):data(data) {
    this->next = NULL;
    this->child[0] = left;
    this->child[1] = right;
}

ProbData HoffNode::getProbData(void) {
    return this->data;
}
