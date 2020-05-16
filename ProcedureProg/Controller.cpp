#include "Controller.h"
#include <iostream>
#include <fstream>
#include <vector>

int getHash(CipherTexts cipher)
{
    int sum = 0;
    sum += cipher.cipherText.length();
    sum += cipher.text.length() * 10;

    return sum % 128;
}

bool readFile(ifstream& in, vector<CipherTexts> hasharray[])
{
    int count = 0;

    if (!in.is_open())
    {
        throw std::invalid_argument("Bad input file. Can not read file!");
    }

    string line;
    getline(in, line);
    count = atoi(line.c_str());
    if (count <= 0)
    {
        throw std::invalid_argument("Bad input count. Its can not be <= 0");
    }
    for (int i = 0; i < count; i++)
    {
        CipherTexts* tempCipher = new CipherTexts();

        getline(in, line);
        tempCipher->text = line.c_str();

        if (tempCipher->text.length() == 0)
        {
            throw std::invalid_argument("Bad input open text. Its can not be empty");
        }

        getline(in, line);

        tempCipher->type = atoi(line.c_str());

        if (tempCipher->type > 2 || tempCipher->type < 0)
        {
            throw std::invalid_argument("Bad input type. Its can not be more then 2 or less then 0");
        }

        getline(in, line);

        tempCipher->owner = line.c_str();

        if (tempCipher->owner.length() == 0)
        {
            throw std::invalid_argument("Bad input owner. Its can not be empty");
        }

        getline(in, line);

        if (tempCipher->type == ShtEnc) {

            tempCipher->shift = atoi(line.c_str());

            if (tempCipher->shift < 0)
            {
                throw std::invalid_argument("Bad input shift. Its can not be less then 0");
            }
        }

        if (tempCipher->type == RepEnc || tempCipher->type == RepEncToInt) {

            if (line.length() == 0)
            {
                throw std::invalid_argument("Bad input kepairs. Its can not be empty");
            }

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

        if (tempCipher->cipherText.length() == 0)
        {
            throw std::invalid_argument("Bad input cipher text. Its can not be empty");
        }

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
        throw std::invalid_argument("Bad output file. Can not read file!");
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
                out << "Owner is: " << current.owner << endl;
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
                out << "Owner is: " << current.owner << endl;
                out << "Open text is: " << current.text << endl;
                out << "Shift is: " << current.shift << endl;
                out << "Cipher text is: " << current.cipherText << endl;
            }
            else if (current.type == RepEncToInt)
            {
                out << "Type of cipher: Replacement to int Cipher\n";
                out << "Owner is: " << current.owner << endl;
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

string vector_to_string(CipherTexts obj)
{
    vector<char> vec;

    for (auto const& item : obj.keyPairs.pairs) {
        vec.push_back(item.openChar);
        vec.push_back(item.cipherChar);
    }
    string str(vec.begin(), vec.end());
    return str;
}

bool WriteCipherToFileWithMiss(ofstream& out, vector<CipherTexts> hasharray[], int missingType)
{
    if (!out.is_open() || missingType < 0 || missingType > 2)
    {
        throw std::invalid_argument("Bad output file. Can not read file! Or missing type invalid!");
    }

    int count = 0;
    bool isAdd = false;
    int missed = 0;
    for (int i = 0; i < maxhash; i++)
    {
        for (int j = 0; j < (int)hasharray[i].size(); j++)
        {
            CipherTexts current = hasharray[i][j];
            if (current.type == RepEnc && missingType != RepEnc)
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
            else if (current.type == ShtEnc && missingType != ShtEnc)
            {
                out << "Type of cipher: Shift Cipher\n";
                out << "Owner is: " << current.owner << endl;
                out << "Open text is: " << current.text << endl;
                out << "Shift is: " << current.shift << endl;
                out << "Cipher text is: " << current.cipherText << endl;
            }
            else if (current.type == RepEncToInt && missingType != RepEncToInt)
            {
                out << "Type of cipher: Replacement to int Cipher\n";
                out << "Owner is: " << current.owner << endl;
                out << "Open text is: " << current.text << endl;
                out << "Key pairs are: ";
                for (auto const& item : current.keyPairs.pairs) {
                    out << item.openChar << " " << item.cipherChar << " ";
                }
                out << endl;
                out << "Cipher text is: " << current.cipherText << endl;
            }
            if (current.type == missingType)
            {
                missed += 1;
            }
        }
        count += (int)hasharray[i].size();
    }
    count -= missed;
    out << "There are " << count << " ciphers" << endl;
    return true;
}

int GetOwnerLength(CipherTexts obj)
{
    return obj.owner.length();
}

bool compare(CipherTexts& a, CipherTexts& b)
{
    return GetOwnerLength(a) > GetOwnerLength(b);
}

void sort(vector<CipherTexts> array[])
{
    for (int hashIndex = 0; hashIndex < maxhash; hashIndex++)
    {
        int size = array[hashIndex].size();
        for (int i = 0; i < (size - 1); i++)
        {
            for (int j = 0; j < (size - i - 1); j++)
            {
                if (compare(array[hashIndex][j], array[hashIndex][j + 1]))
                {
                    CipherTexts temp = array[hashIndex][j];
                    array[hashIndex][j] = array[hashIndex][j + 1];
                    array[hashIndex][j + 1] = temp;
                }
            }
        }

    }
}