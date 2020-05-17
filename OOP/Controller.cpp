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
	if (!in.is_open())
	{
		throw std::invalid_argument("Bad input file. Can not read from file.");
	}
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
	if (!out.is_open())
	{
		throw std::invalid_argument("Bad output file. Can not write to file.");
	}
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
	if (value.length() == 0)
	{
		throw std::invalid_argument("Bad input open text, its can not be empty");
	}
	openText = value;
}

string CipherTextClass::GetCipherText()
{
	return cipherText;
}

void CipherTextClass::SetCipherText(string value)
{
	if (value.length() == 0)
	{
		throw std::invalid_argument("Bad input cipher text, its can not be empty");
	}
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
	if (value.length() == 0)
	{
		throw std::invalid_argument("Bad input owner, its can not be empty");
	}
	owner = value;
}

bool CipherTextClass::Compare(CipherTextClass* value)
{
	if (value == nullptr)
	{
		throw std::invalid_argument("Object is null");
	}
	return this->GetOwnerLength() > value->GetOwnerLength();
}

void CipherTextClass::GlobalMM( CipherTextClass* other, ofstream& out )
{
	out << "Unknown transport" << endl;
}

void CipherTextClass::ShiftMM( ofstream& out )
{
	out << "Unknown transport" << endl;
}

void CipherTextClass::RepToCharMM( ofstream& out )
{
	out << "Unknown transport" << endl;
}

void CipherTextClass::RepToIntMM( ofstream& out )
{
	out << "Unknown transport" << endl;
}

#pragma endregion

#pragma region ShiftEncryptionClass

int ShiftEncryptionClass::GetShift()
{
	return _shift;
}
void ShiftEncryptionClass::SetShift(int value)
{
	if (value <= 0)
	{
		throw std::invalid_argument("Shift can not be <= 0.");
	}
	_shift = value;
}

void ShiftEncryptionClass::ReadCipherFromFile(ifstream& in)
{
	if (!in.is_open())
	{
		throw std::invalid_argument("Bad input file. Can not read from file.");
	}

	CipherTextClass::ReadCipherFromFile(in);

	string line;

	getline(in, line);

	_shift = atoi(line.c_str());
}

void ShiftEncryptionClass::WriteCipherToFile(ofstream& out)
{
	if (!out.is_open())
	{
		throw std::invalid_argument("Bad output file. Can not write to file.");
	}

	out << "Type of cipher: Shift Cipher\n";
	out << "Shift is: " << _shift << endl;

	CipherTextClass::WriteCipherToFile(out);
}

void ShiftEncryptionClass::GlobalMM( CipherTextClass* other, ofstream& out )
{
	other->ShiftMM( out );
}

void ShiftEncryptionClass::ShiftMM( ofstream& out )
{
	out << "Shift and Shift" << endl;
}

void ShiftEncryptionClass::RepToCharMM( ofstream& out )
{
	out << "RepToChar and Shift" << endl;
}

void ShiftEncryptionClass::RepToIntMM( ofstream& out )
{
	out << "RepToInt and Shift" << endl;
}

#pragma endregion

#pragma region ReplacementToCharEcnryptionClass

vector<KeyPair> ReplacementToCharEcnryptionClass::GetPairs()
{
	return _pairs;
}
void ReplacementToCharEcnryptionClass::SetPairs(vector<KeyPair> value)
{
	if (value.size() == 0)
	{
		throw std::invalid_argument("Bad input keypairs, its can not be empty");

	}
	_pairs = value;
}
void ReplacementToCharEcnryptionClass::ReadCipherFromFile(ifstream& in)
{
	if (!in.is_open())
	{
		throw std::invalid_argument("Bad input file. Can not read from file!");
	}

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
	if (!out.is_open())
	{
		throw std::invalid_argument("Bad output file. Can not write to file.");
	}

	out << "Type of cipher: Replacement to Char" << endl;
	out << "Key pairs are: ";
	for (auto const& item : _pairs) {
		out << item.openChar << item.cipherChar;
	}
	out << endl;
	CipherTextClass::WriteCipherToFile(out);
}

void ReplacementToCharEcnryptionClass::GlobalMM( CipherTextClass* other, ofstream& out )
{
	other->RepToCharMM( out );
}

void ReplacementToCharEcnryptionClass::ShiftMM( ofstream& out )
{
	out << "Shift and RepToChar" << endl;
}

void ReplacementToCharEcnryptionClass::RepToCharMM( ofstream& out )
{
	out << "RepToChar and RepToChar" << endl;
}

void ReplacementToCharEcnryptionClass::RepToIntMM( ofstream& out )
{
	out << "RepToInt and RepToChar" << endl;
}

#pragma endregion

#pragma region ReplacementToIntEncryptionClass

vector<KeyPair> ReplacementToIntEncryptionClass::GetPairs()
{
	return _pairs;
}
void ReplacementToIntEncryptionClass::SetPairs(vector<KeyPair> value)
{
	if (value.size() == 0)
	{
		throw std::invalid_argument("Bad input keypairs, its can not be empty");

	}
	_pairs = value;
}

void ReplacementToIntEncryptionClass::ReadCipherFromFile(ifstream& in)
{
	if (!in.is_open())
	{
		throw std::invalid_argument("Bad input file. Can not read from file!");
	}

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
	if (!out.is_open())
	{
		throw std::invalid_argument("Bad output file. Can not write to file.");
	}

	out << "Type of cipher: Replacement to Int" << endl;
	out << "Key pairs are: ";
	for (auto const& item : _pairs) {
		out << item.openChar << item.cipherChar;
	}
	out << endl;
	CipherTextClass::WriteCipherToFile(out);
}

void ReplacementToIntEncryptionClass::GlobalMM( CipherTextClass* other, ofstream& out )
{
	other->RepToIntMM( out );
}

void ReplacementToIntEncryptionClass::ShiftMM( ofstream& out )
{
	out << "Shift and RepToInt" << endl;
}

void ReplacementToIntEncryptionClass::RepToCharMM( ofstream& out )
{
	out << "RepToChar and RepToInt" << endl;
}

void ReplacementToIntEncryptionClass::RepToIntMM( ofstream& out )
{
	out << "RepToInt and RepToInt" << endl;
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
	if (cipherText == nullptr)
	{
		throw std::invalid_argument("Object is null!");
	}
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
	if (!in.is_open())
	{
		throw std::invalid_argument("Bad input file. Can not read from file!");
	}

	int count = 0;

	string line;
	getline(in, line);
	count = atoi(line.c_str());

	if (count <= 0)
	{
		throw std::invalid_argument("Bad input count. Its can not be <= 0");
	}

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
	if (!out.is_open())
	{
		throw std::invalid_argument("Bad output file. Can not write to file.");
	}

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
	if (!out.is_open() || missingType != typeid(ShiftEncryptionClass) || missingType != typeid(ReplacementToCharEcnryptionClass) || missingType != typeid(ReplacementToIntEncryptionClass))
	{
		throw std::invalid_argument("Bad output file. Can not write to file.");
	}
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

void HashArray::GlobalMM( ofstream& out )
{
	out << "Multimethod result" << endl;
	vector<CipherTextClass*> united;
	for ( int i = 0; i < maxhash; i++ )
	{
		if ( Conteiner[i].size() == 0 )
		{
			continue;
		}
		united.insert( united.end(), Conteiner[i].begin(), Conteiner[i].end() );
	}

	for ( int i = 0; i < united.size() - 1; i++ )
	{
		for ( int j = i + 1; j < united.size(); j++ )
		{
			united[i]->GlobalMM( united[j], out );
		}
	}
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