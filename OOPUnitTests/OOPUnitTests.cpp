#include "pch.h"
#include "CppUnitTest.h"
#include "../OOP/Controller.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OOPUnitTests
{
	TEST_CLASS(CipherTextUnitTests)
	{
	public:
		TEST_METHOD(ReadFromFileTest)
		{
			string inputPath = "../OOPUnitTests/Files/input_for_read_test.txt";
			ifstream infile(inputPath);

			CipherTextClass temp;
			temp.ReadCipherFromFile(infile);
			infile.close();

			Assert::IsTrue(temp.GetOpenText() == "Hello my friend");
			Assert::IsTrue(temp.GetOwner() == "Jenya");
			Assert::IsTrue(temp.GetCipherText() == "Fdsse yt pormef");

		}

		TEST_METHOD(WriteFileTest)
		{
			string outputPath = "../OOPUnitTests/Files/output_for_write_test.txt";

			ofstream output(outputPath);

			CipherTextClass temp;

			temp.SetCipherText("gsdgfdsfs");
			temp.SetOpenText("gfdgfdgg");
			temp.SetOwner("Ddddd");

			temp.WriteCipherToFile(output);
			output.close();

			ifstream infile(outputPath);
			std::stringstream buffer;
			buffer << infile.rdbuf();
			string resultInBuffer = buffer.str();

			string waitingResult = "Owner is: Ddddd\nOpen text is: gfdgfdgg\nCipher text is: gsdgfdsfs\n";

			Assert::AreEqual(waitingResult, resultInBuffer);
		}

		TEST_METHOD(GetOwnerLengthTest)
		{
			CipherTextClass temp;
			temp.SetOwner("Heya");
			Assert::IsTrue(temp.GetOwnerLength() == 4);

		}

		TEST_METHOD(CompareTest)
		{
			CipherTextClass temp1;
			CipherTextClass temp2;

			temp1.SetOwner("Hey");

			temp2.SetOwner("Geee");


			Assert::IsTrue(temp1.Compare(&temp2));
		}
	};

	TEST_CLASS(ShiftEncryptionClassTest)
	{
	public:
		TEST_METHOD(ReadTransportFromFileTest)
		{
			string inputPath = "../OOPUnitTests/Files/inputShift_for_read_text.txt";
			ifstream infile(inputPath);

			ShiftEncryptionClass temp;
			temp.ReadCipherFromFile(infile);
			infile.close();

			Assert::IsTrue(temp.GetOpenText() == "Hello my friend");
			Assert::IsTrue(temp.GetOwner() == "Jenya");
			Assert::IsTrue(temp.GetCipherText() == "Fdsse yt pormef");
			Assert::IsTrue(temp.GetShift() == 3);
		}

		TEST_METHOD(WriteFileTestShift)
		{
			string outputPath = "../OOPUnitTests/Files/output_for_write_test.txt";

			ofstream output(outputPath);

			ShiftEncryptionClass temp;

			temp.SetCipherText("gsdgfdsfs");
			temp.SetOpenText("gfdgfdgg");
			temp.SetOwner("Ddddd");
			temp.SetShift(5);

			temp.WriteCipherToFile(output);
			output.close();

			ifstream infile(outputPath);
			std::stringstream buffer;
			buffer << infile.rdbuf();
			string resultInBuffer = buffer.str();

			string waitingResult = "Type of cipher: Shift Cipher\nShift is: 5\nOwner is: Ddddd\nOpen text is: gfdgfdgg\nCipher text is: gsdgfdsfs\nThere are 1 ciphers\n";

			Assert::AreEqual(waitingResult, resultInBuffer);
		}
	};

	TEST_CLASS(ReplacementToCharEcnryptionClassTest)
	{
	public:
		TEST_METHOD(ReadTransportFromFileTestRepChar)
		{
			string inputPath = "../OOPUnitTests/Files/inputRepChar_for_read_text.txt";
			ifstream infile(inputPath);

			ReplacementToCharEcnryptionClass temp;
			temp.ReadCipherFromFile(infile);
			infile.close();

			vector<KeyPair> checkingVector;

			KeyPair tKp;
			tKp.openChar = 'a';
			tKp.cipherChar = 'b';
			checkingVector.push_back(tKp);

			tKp.openChar = 'c';
			tKp.cipherChar = 'd';
			checkingVector.push_back(tKp);

			Assert::IsTrue(temp.GetOpenText() == "Hello my friend");
			Assert::IsTrue(temp.GetOwner() == "Jenya");
			Assert::IsTrue(temp.GetCipherText() == "aaa");
			Assert::IsTrue(temp.GetPairs() == checkingVector);
		}

		TEST_METHOD(WriteTransportToFileTestRepChar)
		{
			string outputPath = "../OOPUnitTests/Files/output_for_write_test.txt";

			ofstream output(outputPath);

			ReplacementToCharEcnryptionClass temp;

			temp.SetCipherText("aaa");
			temp.SetOpenText("Hello my friend");
			temp.SetOwner("Jenya");

			vector<KeyPair> checkingVector;

			KeyPair tKp;
			tKp.openChar = 'a';
			tKp.cipherChar = 'b';
			checkingVector.push_back(tKp);

			tKp.openChar = 'c';
			tKp.cipherChar = 'd';
			checkingVector.push_back(tKp);

			temp.SetPairs(checkingVector);

			temp.WriteCipherToFile(output);
			output.close();

			ifstream infile(outputPath);
			std::stringstream buffer;
			buffer << infile.rdbuf();
			string resultInBuffer = buffer.str();

			string waitingResult = "Type of cipher: Replacement to Char\nKey pairs are: abcd\nOwner is: Jenya\nOpen text is: Hello my friend\nCipher text is: aaa\nThere are 1 ciphers\n";

			Assert::AreEqual(waitingResult, resultInBuffer);
		}
	};

	TEST_CLASS(ReplacementToIntEncryptionClassTest)
	{
	public:
		TEST_METHOD(ReadTransportFromFileTestRepInt)
		{
			string inputPath = "../OOPUnitTests/Files/inputRepInt_for_read_text.txt";
			ifstream infile(inputPath);

			ReplacementToIntEncryptionClass temp;
			temp.ReadCipherFromFile(infile);
			infile.close();

			vector<KeyPair> checkingVector;

			KeyPair tKp;
			tKp.openChar = 'a';
			tKp.cipherChar = '1';
			checkingVector.push_back(tKp);

			tKp.openChar = 'c';
			tKp.cipherChar = '2';
			checkingVector.push_back(tKp);

			Assert::IsTrue(temp.GetOpenText() == "Hello my friend");
			Assert::IsTrue(temp.GetOwner() == "Jenya");
			Assert::IsTrue(temp.GetCipherText() == "aaa");
			Assert::IsTrue(temp.GetPairs() == checkingVector);
		}

		TEST_METHOD(WriteTransportToFileTestRepInt)
		{
			string outputPath = "../OOPUnitTests/Files/output_for_write_test.txt";

			ofstream output(outputPath);

			ReplacementToCharEcnryptionClass temp;

			temp.SetCipherText("aaa");
			temp.SetOpenText("Hello my friend");
			temp.SetOwner("Jenya");

			vector<KeyPair> checkingVector;

			KeyPair tKp;
			tKp.openChar = 'a';
			tKp.cipherChar = '1';
			checkingVector.push_back(tKp);

			tKp.openChar = 'c';
			tKp.cipherChar = '2';
			checkingVector.push_back(tKp);

			temp.SetPairs(checkingVector);

			temp.WriteCipherToFile(output);
			output.close();

			ifstream infile(outputPath);
			std::stringstream buffer;
			buffer << infile.rdbuf();
			string resultInBuffer = buffer.str();

			string waitingResult = "Type of cipher: Replacement to Char\nKey pairs are: a1c2\nOwner is: Jenya\nOpen text is: Hello my friend\nCipher text is: aaa\nThere are 1 ciphers\n";

			Assert::AreEqual(waitingResult, resultInBuffer);
		}
	};

	TEST_CLASS(HashArrayUnitTests)
	{
	public:

		TEST_METHOD(WriteFileWithMissingTypeTest)
		{
			string inputPath = "../OOPUnitTests/Files/input_for_writewithmiss_text.txt";
			string outPath = "../OOPUnitTests/Files/output_for_write_test.txt";

			ifstream infile(inputPath);
			ofstream output(outPath);


			HashArray* arr = new HashArray();
			arr->ReadFile(infile);
			infile.close();

			arr->WriteCipherToFileWithMiss(output, typeid(ReplacementToCharEcnryptionClass));
			output.close();
			ifstream checkfile(outPath);
			std::stringstream buffer;
			buffer << checkfile.rdbuf();
			string result = buffer.str();
			string ideal = "Type of cipher: Shift Cipher\nShift is: 3\nOwner is: Jenya\nOpen text is: Hello my friend\nCipher text is: Fdsse yt pormef\nThere are 1 ciphers\n";

			Assert::AreEqual(ideal, result);



		}

		TEST_METHOD(SortTest)
		{
			string inputPath = "../OOPUnitTests/Files/input_for_writewithmiss_text.txt";
			ifstream infile(inputPath);
			HashArray* arr = new HashArray();
			arr->ReadFile(infile);
			infile.close();
			arr->Sort();
			Assert::IsTrue(arr->Conteiner[37][0]->GetOwnerLength() == 4, L"Assert 1");
			Assert::IsTrue(arr->Conteiner[37][1]->GetOwnerLength() == 5, L"Assert 2");
		}
	};
}
