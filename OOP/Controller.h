#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct KeyPair
{
	char openChar;
	char cipherChar;
};


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

	virtual void GlobalMM( CipherTextClass* other, ofstream& out );

	virtual void ShiftMM( ofstream& out );
	virtual void RepToCharMM( ofstream& out );
	virtual void RepToIntMM( ofstream& out );

	string vectostring(vector<KeyPair> temp);
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

	void GlobalMM( CipherTextClass* other, ofstream& out ) override;

	void ShiftMM( ofstream& out ) override;
	void RepToCharMM( ofstream& out ) override;
	void RepToIntMM( ofstream& out ) override;
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

	void GlobalMM( CipherTextClass* other, ofstream& out ) override;

	void ShiftMM( ofstream& out ) override;
	void RepToCharMM( ofstream& out ) override;
	void RepToIntMM( ofstream& out ) override;
};

class ReplacementToIntEncryptionClass : public CipherTextClass
{
private:
	vector <KeyPair> _pairs;
public:
	vector<KeyPair> GetPairs();
	void SetPairs(vector<KeyPair> value);
	void ReadCipherFromFile(ifstream& in) override;
	void WriteCipherToFile(ofstream& out) override;

	void GlobalMM( CipherTextClass* other, ofstream& out ) override;

	void ShiftMM( ofstream& out ) override;
	void RepToCharMM( ofstream& out ) override;
	void RepToIntMM( ofstream& out ) override;
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
	bool WriteCipherToFileWithMiss(ofstream& out, const type_info& missingType);
	void Sort();

	void GlobalMM( ofstream& out );

	HashArray();
	~HashArray();
};
