#include "pch.h"
#include "CppUnitTest.h"
#include <iostream>
#include <vector>
#include <fstream>
#include "../ProcedureProg/Controller.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ProcedureProgUnitTests
{
	TEST_CLASS(ProcedureProgUnitTests)
	{
	public:
		TEST_METHOD(GetHashTest)
		{
			CipherTexts t;
			t.cipherText = "olleH";
			t.text = "Hello";
			Assert::IsTrue(getHash(t) == 55);
		}

		TEST_METHOD(GetOwnerLengthTest)
		{
			CipherTexts t;
			t.owner = "Mike";
			Assert::IsTrue(GetOwnerLength(t) == 4);
		}

		TEST_METHOD(CompareTest)
		{
			CipherTexts first;
			CipherTexts second;

			first.type = ShtEnc;
			second.type = RepEnc;

			first.owner = "Mike";
			second.owner = "Jacob";
			
			Assert::IsTrue(compare(second, first) == true);
		}

		TEST_METHOD(VectorToStringTest)
		{
			CipherTexts obj;
			KeyPair tempKeyPair;
			tempKeyPair.openChar = 'a';
			tempKeyPair.cipherChar = 'b';
			std::vector<KeyPair> keyPairsVector;
			keyPairsVector.push_back(tempKeyPair);
			obj.keyPairs.pairs = keyPairsVector;
			Assert::IsTrue(vector_to_string(obj) == "ab");
		}

		TEST_METHOD(ReadFromFileTest)
		{
			string inputFilePath = "../ProcedureProgUnitTests/Files/input_for_read_test.txt";

			ifstream in(inputFilePath);

			vector<CipherTexts> hasharray[maxhash];

			readFile(in, hasharray);

			in.close();

			CipherTexts first = hasharray[37][0];

			#pragma region AssertsForFirstObject

			Assert::IsTrue(first.text == "Hello my friend", L"assert for text 1");
			Assert::IsTrue(first.type == ShtEnc, L"assert for type 1");
			Assert::IsTrue(first.owner == "Jenya", L"assert for owner 1");
			Assert::IsTrue(first.shift == 3, L"assert for shift 1");
			Assert::IsTrue(first.cipherText == "Fdsse yt pormef", L"assert for ciphertext 1");

			#pragma endregion

			CipherTexts second = hasharray[54][0];

			#pragma region AssertsForSecondObject

			Assert::IsTrue(second.text == "yollo", L"assert for text 2");
			Assert::IsTrue(second.type == RepEnc, L"assert for type 2");
			Assert::IsTrue(second.owner == "Oleg", L"assert for owner 2");
			
			string keyPairsString = vector_to_string(second);

			Assert::IsTrue(keyPairsString == "abcdef", L"assert for keypair 2");
			Assert::IsTrue(second.cipherText == "Olfg", L"assert for ciphertext 2");

			#pragma endregion
		}

		TEST_METHOD(SortTest)
		{
			string inputPath = "../ProcedureProgUnitTests/Files/input_for_sort_test.txt";

			ifstream infile(inputPath);

			vector<CipherTexts> hasharray[maxhash];

			readFile(infile, hasharray);

			infile.close();

			sort(hasharray);

			Assert::IsTrue(GetOwnerLength(hasharray[37][0]) == 4, L"Assert 1");
			Assert::IsTrue(GetOwnerLength(hasharray[37][1]) == 5, L"Assert 2");
		}

		TEST_METHOD(WriteFileWithMissTest)
		{
			string inputPath = "../ProcedureProgUnitTests/Files/input_for_read_test.txt";
			string outputPath = "../ProcedureProgUnitTests/Files/output_for_write_test.txt";

			ifstream infile(inputPath);
			ofstream output(outputPath);


			vector<CipherTexts> hasharray[maxhash];
			readFile(infile, hasharray);
			infile.close();
			WriteCipherToFileWithMiss(output, hasharray, RepEnc);
			output.close();

			ifstream resultIn(outputPath);
			std::stringstream buffer;
			buffer << resultIn.rdbuf();
			string resultInBuffer = buffer.str();

			string waitingResult = "Type of cipher: Shift Cipher\nOwner is: Jenya\nOpen text is: Hello my friend\nShift is: 3\nCipher text is: Fdsse yt pormef\nThere are 1 ciphers\n";

			Assert::AreEqual(waitingResult, resultInBuffer);
		}

	};
	
}
