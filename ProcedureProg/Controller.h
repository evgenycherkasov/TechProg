#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int maxhash = 128;

struct KeyPair
{
	char openChar;
	char cipherChar;
};

struct KeyPairs
{
	vector <KeyPair> pairs;
};

enum CipherType
{
	RepEnc = 0,
	ShtEnc = 1,
	RepEncToInt = 2
};

struct CipherTexts
{
	string text;

	string owner;

	int type;

	//shiftEncryption
	int shift;

	//ReplacementEcnryption
	KeyPairs keyPairs;

	string cipherText;
};

int getHash( CipherTexts cipher );

bool readFile( ifstream& in, vector<CipherTexts> hasharray[] );
bool writeToFile( ofstream& out, vector<CipherTexts> hasharray[] );
bool compare( CipherTexts& a, CipherTexts& b );
void sort( vector<CipherTexts> array[] );
int GetOwnerLength( CipherTexts obj );
bool WriteCipherToFileWithMiss( ofstream& out, vector<CipherTexts> hasharray[], int missingType );
string vector_to_string( CipherTexts obj );
