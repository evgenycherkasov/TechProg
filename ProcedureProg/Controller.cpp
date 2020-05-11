#include "Controller.h"
#include <iostream>
#include <fstream>
#include <vector>

int getHash(CipherTexts cipher)
{
    int sum = 0;
    sum += cipher.shift;
    sum += cipher.text.length() * 10;

    return sum % 128;
}

bool readFile(ifstream& in, vector<CipherTexts> hasharray[])
{
    int count = 0;

    if (!in.is_open())
    {
        return false;
    }

    string line;
    getline(in, line);
    count = atoi(line.c_str());
    for (int i = 0; i < count; i++)
    {
        CipherTexts* tempCipher = new CipherTexts();

        getline(in, line);
        tempCipher->text = line.c_str();

        getline(in, line);
        tempCipher->type = atoi(line.c_str());

        getline(in, line);
        if (tempCipher->type == ShtEnc) {
            getline(in, line);
            tempCipher->shift = atoi(line.c_str());
        }

        if (tempCipher->type == RepEnc || tempCipher->type == RepEncToInt) {
            getline(in, line);
            KeyPair temp;
            KeyPairs keyPairsTemp;
            vector <KeyPair> keypairs;
            for (unsigned int i = 0; i < line.length() - 1; i += 2) {
                temp.openChar = line[i];
                temp.cipherChar = line[i + 1];
                keypairs.push_back(temp);
            }
            keyPairsTemp.pairs = keypairs;
            tempCipher->keyPairs = keyPairsTemp;
        }

        getline(in, line);
        tempCipher->cipherText = line.c_str();

        int index = getHash(*tempCipher);
        hasharray[index].push_back(*tempCipher);
        delete tempCipher;
    }
    return true;
}

bool writeToFile(ofstream& out, vector<CipherTexts> hasharray[])
{
    if (!out.is_open())
    {
        return false;
    }
    int count = 0;

    for (int i = 0; i < maxhash; i++)
    {
        for (int j = 0; j < (int)hasharray[i].size(); j++)
        {
            CipherTexts current = hasharray[i][j];
            if (current.type == RepEnc)
            {
                out << "Type of cipher: Replacement Cipher\n";
                out << "Open text is: " << current.text << endl;
                out << "Key pairs are: ";
                for (auto const& item : current.keyPairs.pairs) {
                    out << item.openChar << " " << item.cipherChar << " ";
                }
                out << endl;
                out << "Cipher text is: " << current.cipherText << endl;
            }
            else if (current.type == ShtEnc)
            {
                out << "Type of cipher: Shift Cipher\n";
                out << "Open text is: " << current.text << endl;
                out << "Shift is: " << current.shift << endl;
                out << "Cipher text is: " << current.cipherText << endl;
            }
            else if (current.type == RepEncToInt)
            {
                out << "Type of cipher: Replacement to int Cipher\n";
                out << "Open text is: " << current.text << endl;
                out << "Key pairs are: ";
                for (auto const& item : current.keyPairs.pairs) {
                    out << item.openChar << " " << item.cipherChar << " ";
                }
                out << endl;
                out << "Cipher text is: " << current.cipherText << endl;
            }
        }
        count += (int)hasharray[i].size();
    }

    out << "There are " << count << " ciphers" << endl;
    return true;
}
