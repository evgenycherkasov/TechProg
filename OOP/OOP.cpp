#include "Controller.h"

using std::cout;


int main(int argc, char* argv[])
{
	string inputPath = "input.txt";
	string outputPath = "output.txt";

	if (argc != 3)
	{
		cout << "Type input and output files\n";
		return 1;
	}
	inputPath = argv[1];
	outputPath = argv[2];

	ifstream infile(inputPath);
	if (!infile.is_open())
	{
		return 1;
	}
	ofstream outfile(outputPath);
	if (!outfile.is_open())
	{
		return 1;
	}

	HashArray* hashArray = new HashArray();

	hashArray->ReadFile(infile);
	hashArray->WriteFile(outfile);
	hashArray->GlobalMM( outfile );


	return 0;
}