#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class CipherTextClass
{
private:
	string openText;
	string cipherText;
	string owner;
public:
	virtual void ReadCipherFromFile(ifstream& in);
	virtual void WriteCipherToFile(ofstream& out);

	void SetOpenText(string value);
	string GetOpenText();
	bool Compare(CipherTextClass* value);
	string GetCipherText();
	void SetCipherText(string value);

	void SetOwner(string value);
	string GetOwner();
	int GetOwnerLength();
};

class ShiftEncryptionClass : public CipherTextClass
{
private:
	int _shift;
public:
	int GetShift();
	void SetShift(int value);

	void ReadCipherFromFile(ifstream& in) override;
	void WriteCipherToFile(ofstream& out) override;
};

struct KeyPair
{
	char openChar;
	char cipherChar;
};

class ReplacementToCharEcnryptionClass : public CipherTextClass
{
private:
	vector <KeyPair> _pairs;
public:
	vector<KeyPair> GetPairs();
	void SetPairs(vector<KeyPair> value);
	void ReadCipherFromFile(ifstream& in) override;
	void WriteCipherToFile(ofstream& out) override;
};

class HashArray
{
private:
	int getHash(CipherTextClass* cipher);
public:
	vector<CipherTextClass*>* Conteiner;

	const int maxhash = 128;
	bool ReadFile(ifstream& in);
	bool WriteFile(ofstream& out);
	void Sort();

	HashArray();
	~HashArray();
};
