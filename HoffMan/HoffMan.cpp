#include "HoffMan.h"

HoffMan::HoffMan(void) {
    this->chSize = pow(2, sizeof(char)* 8);
    this->probArray = NULL;
}

HoffMan::~HoffMan(void) {
    if (this->probArray) {
        delete this->probArray;
    }
}

string HoffMan::encode(string toEncode) {
    if (this->probArray) {
        delete this->probArray;
        this->probArray = NULL;
    }

    this->probArray = this->createProbArray(toEncode);

    HoffTree tree(this->probArray);// the main HoffMan tree
    vector<HoffCode> *hoffCode = tree.codeArray(); // the vector containg the hoffCode of each character
    string *codeArray = this->createCodeArray(hoffCode); // makes an array of string containg the code of each character corresponding to its ascii location

    string toReturn = this->encode(toEncode, codeArray);

    delete hoffCode;
    delete[] codeArray;

    return toReturn;
}

string HoffMan::encode(string toEncode, string *codeArray) {
    string toReturn;

    for (int i = 0, n = toEncode.size(); i < n; i++) {
        toReturn += codeArray[toEncode[i]];
    }
    return toReturn;
}

int *HoffMan::createOccurArray(const string fileContent) {
    int *toReturn = new int[this->chSize];

    // setting the default values of the int array
    for (int i = 0; i < this->chSize; i++) {
        toReturn[i] = 0;
    }

    for (int i = 0, n = fileContent.size(); i < n; i++) {
        toReturn[fileContent[i]]++;
        toReturn[0]++; // to find the total number of alphabets in the file '0' will mark the end of string and will never occur
    }

    return toReturn;
}

string *HoffMan::createCodeArray(const vector<HoffCode> *hoffCode) {
    string *toReturn = new string[this->chSize];

    for (int i = 0, n = hoffCode->size(); i < n; i++) {
        toReturn[hoffCode[0][i].alpha] = hoffCode[0][i].code;
    }

    return toReturn;
}

vector<ProbData> *HoffMan::createProbArray(string toEncode) {
    vector<ProbData> *toReturn = new vector<ProbData>;
    int *occurArray = this->createOccurArray(toEncode);

    for (int i = 1; i < this->chSize; i++) { // from 1 because 0 stores the total occurence
        int occur = occurArray[i];

        if (occur > 0) {
            ProbData toAdd((char)i, occurArray[i]);
            toReturn->push_back(toAdd);
        }
    }
    delete[] occurArray;
    return toReturn;
}

bool HoffMan::encodeToFile(string toEncode, string fileLoc) {
    //  this function encodes the given file contents to the file
    string toWrite = this->encode(toEncode);

    byte extraBits = 8 - toWrite.length() % 8; // the number of remaining bits that need to fill so that fileContent have complete bytes

    // adding the required bits
    for (int i = 0; i < extraBits; i++) {
        toWrite += "0";
    }
    vector<byte> *bytesToWrite = this->completeByteRepresentation(toWrite);
    return this->encodeToFile(fileLoc, bytesToWrite, extraBits);
}

bool HoffMan::encodeToFile(string fileLoc, vector<byte> *bytesToWrite, byte extraBits) {
    // The actual function that write to the file
    /*
    *	The content of the file will be as follows:
    *	A byte representing the number of extra bits in the end
    *	A byte representing the number of ProbData elements
    *	A int representing the number of struct of ProbData
    *	The structs of ProbData
    *	Then the number of bytes to be read
    *	Followed by the actual content of the file
    *
    */
    ofstream out;
    out.open(fileLoc, ios::binary);

    if (!out.is_open()) {
        return false;
    }

    byte probArraySize = (byte) this->probArray->size();
    int numOfBytesToWrite = bytesToWrite->size();

    out.write(reinterpret_cast<const char*>(&extraBits), sizeof(byte));
    out.write(reinterpret_cast<const char*>(&probArraySize), sizeof(byte));
    out.write(reinterpret_cast<const char*>(&numOfBytesToWrite), sizeof(int));

    // now writing the probArray
    for (int i = 0; i < probArraySize; i++) {
        out.write(reinterpret_cast<const char*>(&this->probArray[0][i]), sizeof(ProbData));
    }

    // now writing the bytes
    for (int i = 0; i < numOfBytesToWrite; i++) {
        out.write(reinterpret_cast<const char*>(&bytesToWrite[0][i]), sizeof(byte));
    }

    out.close();
    delete bytesToWrite;
    return true;
}

byte HoffMan::getByteRep(string toConvert) {
    int n = toConvert.length();
    byte toReturn = 0;
    if (n > 8) {
        return 0;
    }

    for (int i = 0; i < 8; i++) {
        if (this->isON(toConvert[i])) {
            toReturn += pow(2, 8 - i - 1);
        }
    }
    return toReturn;
}

bool HoffMan::isON(char toConvert) {
    if (toConvert == '0') {
        return 0;
    }
    return 1;
}

vector<byte> *HoffMan::completeByteRepresentation(string fileContents) { // returns a vector representing the bytes to write in the file
    vector<byte> *toReturn = new vector<byte>;
    for (int i = 0, n = fileContents.length(); i < n; i += 8) {
        toReturn->push_back(this->getByteRep(fileContents.substr(i, 8)));
    }

    return toReturn;
}

string HoffMan::decodeFromFile(string fileLoc) {
    ifstream in;
    in.open(fileLoc, ios::binary);

    if (!in.is_open()) {
        return "";
    }

    byte probArraySize;
    byte extraBits;
    int numOfBytesToRead;
    vector<byte> *bytesStoredInFile = new vector<byte>;

    if (this->probArray) { //  the probArray for storing the prob information
        delete this->probArray;
        this->probArray = NULL;
    }
    this->probArray = new vector<ProbData>;

    in.read(reinterpret_cast<char*>(&extraBits), sizeof(byte));
    in.read(reinterpret_cast<char*>(&probArraySize), sizeof(byte));
    in.read(reinterpret_cast<char*>(&numOfBytesToRead), sizeof(int));

    for (int i = 0; i < probArraySize; i++) {
        ProbData temp;
        in.read(reinterpret_cast<char*>(&temp), sizeof(ProbData));
        this->probArray->push_back(temp);
    }

    for (int i = 0; i < numOfBytesToRead; i++) {
        // now the bits stored in the files need to be extracted
        byte toRead;
        in.read(reinterpret_cast<char*>(&toRead), sizeof(byte));
        bytesStoredInFile->push_back(toRead);
    }

    HoffTree decodeTree(this->probArray);
    in.close();
    string toReturn = decodeTree.decode(bytesStoredInFile, extraBits);
    delete bytesStoredInFile;
    return toReturn;
}
