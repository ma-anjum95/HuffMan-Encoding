#include "ProbData.h"

ProbData::ProbData(void) {
    this->alpha = 0;
    this->prob = 0;
}

ProbData::ProbData(char alpha, int prob) {
    this->alpha = alpha;
    this->prob = prob;
}

ProbData::ProbData(const ProbData &toCopy) {
    this->alpha = toCopy.alpha;
    this->prob = toCopy.prob;
}

int ProbData::getProb(void) {
    return this->prob;
}

char ProbData::getAlpha(void) {
    return this->alpha;
}

void ProbData::setProb(int prob) {
    this->prob = prob;
}

ostream& operator<<(ostream &os, const ProbData &probData) {
    os << probData.alpha << probData.prob;
    return os;
}

istream& operator>>(istream &is, ProbData &probData) {
    is >> probData.alpha >> probData.prob;
    return is;
}
