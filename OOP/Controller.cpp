#include "Controller.h"

#pragma region CipherTextClass

string CipherTextClass::vectostring(vector<KeyPair> temp)
{
	vector<char> vec;

	for (auto const& item : temp) {
		vec.push_back(item.openChar);
		vec.push_back(item.cipherChar);
	}
	string str(vec.begin(), vec.end());
	return str;
}

void CipherTextClass::ReadCipherFromFile(ifstream& in)
{
	string line;

	getline(in, line);

	openText = line;

	getline(in, line);

	cipherText = line;

	getline(in, line);

	owner = line;
}

void CipherTextClass::WriteCipherToFile(ofstream& out)
{
	out << "Owner is: " << owner << endl;
	out << "Open text is: " << openText << endl;
	out << "Cipher text is: " << cipherText << endl;
}

string CipherTextClass::GetOpenText()
{
	return openText;
}

void CipherTextClass::SetOpenText(string value)
{
	openText = value;
}

string CipherTextClass::GetCipherText()
{
	return cipherText;
}

void CipherTextClass::SetCipherText(string value)
{
	cipherText = value;
}

int CipherTextClass::GetOwnerLength()
{
	return owner.length();
}

string CipherTextClass::GetOwner()
{
	return owner;
}

void CipherTextClass::SetOwner(string value)
{
	owner = value;
}

bool CipherTextClass::Compare(CipherTextClass* value)
{
	return this->GetOwnerLength() > value->GetOwnerLength();
}


#pragma endregion

#pragma region ShiftEncryptionClass

int ShiftEncryptionClass::GetShift()
{
	return _shift;
}
void ShiftEncryptionClass::SetShift(int value)
{
	_shift = value;
}

void ShiftEncryptionClass::ReadCipherFromFile(ifstream& in)
{
	CipherTextClass::ReadCipherFromFile(in);

	string line;

	getline(in, line);

	_shift = atoi(line.c_str());
}

void ShiftEncryptionClass::WriteCipherToFile(ofstream& out)
{
	out << "Type of cipher: Shift Cipher\n";
	out << "Shift is: " << _shift << endl;

	CipherTextClass::WriteCipherToFile(out);
}

#pragma endregion

#pragma region ReplacementToCharEcnryptionClass

vector<KeyPair> ReplacementToCharEcnryptionClass::GetPairs()
{
	return _pairs;
}
void ReplacementToCharEcnryptionClass::SetPairs(vector<KeyPair> value)
{
	_pairs = value;
}
void ReplacementToCharEcnryptionClass::ReadCipherFromFile(ifstream& in)
{
	CipherTextClass::ReadCipherFromFile(in);

	string line;

	getline(in, line);

	KeyPair temp;

	for (unsigned int i = 0; i < line.length() - 1; i += 2) {
		temp.openChar = line[i];
		temp.cipherChar = line[i + 1];
		_pairs.push_back(temp);
	}
}

void ReplacementToCharEcnryptionClass::WriteCipherToFile(ofstream& out)
{
	out << "Type of cipher: Replacement to Char" << endl;
	out << "Key pairs are: ";
	for (auto const& item : _pairs) {
		out << item.openChar << item.cipherChar;
	}
	out << endl;
	CipherTextClass::WriteCipherToFile(out);
}

#pragma endregion

#pragma region ReplacementToIntEncryptionClass

vector<KeyPair> ReplacementToIntEncryptionClass::GetPairs()
{
	return _pairs;
}
void ReplacementToIntEncryptionClass::SetPairs(vector<KeyPair> value)
{
	_pairs = value;
}

void ReplacementToIntEncryptionClass::ReadCipherFromFile(ifstream& in)
{
	CipherTextClass::ReadCipherFromFile(in);

	string line;

	getline(in, line);

	KeyPair temp;

	for (unsigned int i = 0; i < line.length() - 1; i += 2) {
		temp.openChar = line[i];
		temp.cipherChar = line[i + 1];
		_pairs.push_back(temp);
	}
}

void ReplacementToIntEncryptionClass::WriteCipherToFile(ofstream& out)
{
	out << "Type of cipher: Replacement to Int" << endl;
	out << "Key pairs are: ";
	for (auto const& item : _pairs) {
		out << item.openChar << item.cipherChar;
	}
	out << endl;
	CipherTextClass::WriteCipherToFile(out);
}

#pragma endregion

#pragma region HashArray

void HashArray::Sort()
{
	for (int hashIndex = 0; hashIndex < maxhash; hashIndex++)
	{
		int size = Conteiner[hashIndex].size();
		for (int i = 0; i < (size - 1); i++)
		{
			for (int j = 0; j < (size - i - 1); j++)
			{
				if (Conteiner[hashIndex][j]->Compare(Conteiner[hashIndex][j + 1]))
				{
					CipherTextClass* temp = Conteiner[hashIndex][j];
					Conteiner[hashIndex][j] = Conteiner[hashIndex][j + 1];
					Conteiner[hashIndex][j + 1] = temp;
				}
			}
		}

	}
}

int HashArray::getHash(CipherTextClass* cipherText)
{
	int sum = 0;
	string _cipherText;
	string _openText;
	_cipherText = cipherText->GetCipherText();
	_openText = cipherText->GetOpenText();
	sum += _cipherText.length();
	sum += _openText.length() * 10;

	return sum % maxhash;
}

bool HashArray::ReadFile(ifstream& in)
{
	int count = 0;

	string line;
	getline(in, line);
	count = atoi(line.c_str());

	for (int i = 0; i < count; i++)
	{
		CipherTextClass* tempCipher = nullptr;

		getline(in, line);
		int type = atoi(line.c_str());

		if (type == 0)
		{
			ShiftEncryptionClass* tempShiftEncObj = new ShiftEncryptionClass();
			tempShiftEncObj->ReadCipherFromFile(in);
			tempCipher = tempShiftEncObj;
		}
		else if (type == 1)
		{
			ReplacementToCharEcnryptionClass* tempRepToCharEncObj = new ReplacementToCharEcnryptionClass();
			tempRepToCharEncObj->ReadCipherFromFile(in);
			tempCipher = tempRepToCharEncObj;
		}
		else if (type == 2)
		{
			ReplacementToIntEncryptionClass* tempRepToIntEncObj = new ReplacementToIntEncryptionClass();
			tempRepToIntEncObj->ReadCipherFromFile(in);
			tempCipher = tempRepToIntEncObj;
		}
		else
		{
			tempCipher = new CipherTextClass();
			tempCipher->ReadCipherFromFile(in);
		}

		int hash = getHash(tempCipher);

		Conteiner[hash].push_back(tempCipher);
	}

	return true;
}

bool HashArray::WriteFile(ofstream& out)
{
	int count = 0;

	for (int i = 0; i < maxhash; i++)
	{
		for (int j = 0; j < (int)Conteiner[i].size(); j++)
		{
			CipherTextClass* current = Conteiner[i][j];
			current->WriteCipherToFile(out);
		}
		count += (int)Conteiner[i].size();
	}

	out << "There are " << count << " ciphers" << endl;

	return false;
}


bool HashArray::WriteCipherToFileWithMiss(ofstream& out, const type_info& missingType)
{
	int count = 0;

	for (int i = 0; i < maxhash; i++)
	{
		for (int j = 0; j < (int)Conteiner[i].size(); j++)
		{
			CipherTextClass* current = Conteiner[i][j];
			if (missingType == typeid(*current))
			{
				count--;
				continue;
			}
			current->WriteCipherToFile(out);
		}
		count += (int)Conteiner[i].size();
	}

	out << "There are " << count << " ciphers" << endl;

	return false;
}

HashArray::HashArray()
{
	Conteiner = new vector<CipherTextClass*>[maxhash];

}

HashArray::~HashArray()
{
	for (int i = 0; i < maxhash; i++)
	{
		for (int j = 0; j < (int)Conteiner[i].size(); j++)
		{
			delete Conteiner[i][j];
		}
	}
	delete Conteiner;

}

#pragma endregion