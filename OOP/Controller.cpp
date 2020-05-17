#include "Controller.h"

#pragma region CipherTextClass

void CipherTextClass::ReadCipherFromFile(ifstream& in)
{
	string line;

	getline(in, line);

	openText = line;

	getline(in, line);

	cipherText = line;
}

void CipherTextClass::WriteCipherToFile(ofstream& out)
{
	out << "Open text is  " << openText << endl;
	out << "Cipher text is  " << cipherText << endl;
	out << endl;
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

void CipherTextClass::GlobalMM( CipherTextClass* other, ofstream& out )
{
	out << "Unknown cipher method" << endl;
}

void CipherTextClass::ShiftMM( ofstream& out )
{
	out << "Unknown cipher method" << endl;
}

void CipherTextClass::RepToCharMM( ofstream& out )
{
	out << "Unknown cipher method" << endl;
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
	out << "Shift is " << _shift << endl;

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
		out << item.openChar << " " << item.cipherChar << " ";
	}
	out << endl;
	ReplacementToCharEcnryptionClass::WriteCipherToFile(out);
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

#pragma endregion



#pragma region HashArray

int HashArray::getHash(CipherTextClass* cipherText)
{
	int sum = 0;
	string _cipherText;
	string _openText;
	_cipherText = cipherText->GetCipherText();
	_openText = cipherText->GetOpenText();
	sum += _cipherText.length();
	sum += _openText.length() * 10;

	return sum % MAXHASH;
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

	for (int i = 0; i < MAXHASH; i++)
	{
		for (int j = 0; j < (int)Conteiner[i].size(); j++)
		{
			CipherTextClass* current = Conteiner[i][j];
			current->WriteCipherToFile(out);
		}
		count += (int)Conteiner[i].size();
	}

	out << "There are " << count << " transports" << endl;

	return false;
}

void HashArray::GlobalMM( ofstream& out )
{
	out << "Multimethod result" << endl;
	vector<CipherTextClass*> united;
	for ( int i = 0; i < MAXHASH; i++ )
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

HashArray::HashArray()
{
	Conteiner = new vector<CipherTextClass*>[MAXHASH];

}

HashArray::~HashArray()
{
	for (int i = 0; i < MAXHASH; i++)
	{
		for (int j = 0; j < (int)Conteiner[i].size(); j++)
		{
			delete Conteiner[i][j];
		}
	}
	delete Conteiner;

}

#pragma endregion