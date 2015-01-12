#ifndef HOFFMAN_H
#define HOFFMAN_H

#include <cmath>
#include <cstdint>
#include <fstream>

#include "../ProbData/ProbData.h"
#include "../HoffTree/HoffTree.h"

typedef uint8_t byte; // definig a new data type called byte equal to 8 bits

class HoffMan {
    int chSize;  // this int stores the max number of char possible ie 2^(sizeof(char) * 8)
    vector<ProbData> *probArray; // the probArray for the current HoffMan instance (Can Change)

    /*
    *   This method takes in a string of length 8 and returns the byte represented by those
    *   bits given in string eg. "00001000" passed in as a parameter will return 8.
    *   If the length of the passed string exceeds 8 the method returns 0
    */
    byte getByteRep(string toConvert); // must be provided a string of length 8

    /*
    *   This return represents the state of current passed character
    *   If it is '0' then i return false else true.
    */
    bool isON(char toConvert);

    /*
    *   This method returns a vector representing the byte representation,
    *   of the string file passed in as a parameter
    *   This method loops over the string and send part of length of size 8 to the method 'getByteRep'
    */
    vector<byte> *completeByteRepresentation(string fileContents);

    /*
    *   This method creates an array of size 2^(bits in a char) and,
    *   sets the occurence value of each index to its corresponding ascii values.
    */
    int *createOccurArray(const string fileContent);

    /*
    *   This method takes in a vector representing the hoffCode created and
    *   sets the code at the corresponding ascii value of the character
    */
    string *createCodeArray(const vector<HoffCode> *hoffCode);

    /*
    *   This method returns a vector containing the ProbData structure of each character,
    *   existing in the string toEncode.
    *   The ProbData includes a character and its occurence.
    */
    vector<ProbData> *createProbArray(string toEncode);

    /*
    *   This overloaded method takes in the toEncode string and the codeArray created in the
    *   other encode method and returns a string of bits that represent the HoffMan encoded form of the string.
    */
    string encode(string toEncode, string *codeArray);

    /*
    *   This overloaded method is called by other encodeToFile by passing in a fileLoc,
    *   and also the pointer to a vector containing the bytes to write in files,
    *   also the number of extra bits added to make number of bits completely divisible by 8
    *
    *	The content of the file will be as follows:
    *	A byte representing the number of extra bits in the end
    *	A byte representing the number of ProbData elements
    *	A int representing the number of struct of ProbData
    *	The structs of ProbData
    *	Then the number of bytes to be read
    *	Followed by the actual content of the file
    *
    */
    bool encodeToFile(string fileLoc, vector<byte> *bytesToWrite, byte extraBits);

public:
    /*
    *   The default constructor of HoffMan Module
    *   Sets the pointer of probArray to NULL
    */
    HoffMan(void);

    /*
    *   Deletes probArray if it exists
    */
    ~HoffMan(void);

    /*
    *   Encodes the given toEncode string and returns a string of bits,
    *   which is the encoded form of the string passed in as a parameter
    */
    string encode(string toEncode);

    /*
    *   Encodes the given toEncode string using the above declared method to,
    *   get the encoded form of the string and write it in the file
    *   it returns true if the file openes and the encoded info is written else it returns false
    */
    bool encodeToFile(string toEncode, string fileLoc);

    /*
    *   The method decodes the contents of a file given as a parameter
    *   and returns the string representing the actual data stored in the file.
    */
    string decodeFromFile(string fileLoc);
};
#endif // HOFFMAN_H
