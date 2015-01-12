#ifndef PROBDATA_H
#define PROBDATA_H

#include <iostream>

using namespace std;

class ProbData {
    char alpha; // the alphabet stored
    int prob; // the occurence of current character

public:
    /*
    *   The default constructor the ProbData class
    *   It is sets the defaults the values of the class variables to 0
    */
    ProbData(void);

    /*
    *   The parametrised constructor of the ProbData Class
    *   It sets the values of the private values to ones passed in as a parameter
    */
    ProbData(char alpha, int prob);

    /*
    *   The copy constructor of the ProbData class.
    *   Copies individual data from the object passed in as a parameter
    */
    ProbData(const ProbData &toCopy);

    /*
    *   Getter function of the 'prob' variable
    */
    int getProb(void);

    /*
    *   Getter function of the 'alpha' variable
    */
    char getAlpha(void);

    /*
    *   The setter function of the 'prob' variable
    */
    void setProb(int prob);

    // stream operator overloading
    /*
    *   The outstream overloaded friend function which returns the stream containing
    *   'alpha' and 'prob' variables in a stream form to be written in a file
    */
    friend ostream& operator<<(ostream &os, const ProbData &probData);

    /*
    *   The instream overloaded friend function which sets the values of the
    *   'alpha' and 'prob' variables of the current object
    */
    friend istream& operator>>(istream &is, ProbData &probData);
};

#endif // PROBDATA_H
