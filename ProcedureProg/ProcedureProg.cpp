#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "Controller.h"

using namespace std;


int main( int argc, char* argv[] )
{
	string inputPath = "input.txt";
	string outputPath = "output.txt";

	if ( argc != 3 )
	{
		cout << "Type files" << endl;
		return 1;
	}

	inputPath = argv[1];
	outputPath = argv[2];

	vector<CipherTexts> hasharray[maxhash];

	ifstream infile( inputPath );

	bool result = readFile( infile, hasharray );
	cout << result;
	if ( !result )
	{
		cout << "Bad input file!\n";
		return 1;
	}
	else
	{
		infile.close();
	}

	ofstream out( outputPath );

	result = writeToFile( out, hasharray );
	if ( !result )
	{
		cout << "Bad output file!\n";
		return 1;
	}
	else
	{
		out.close();
	}

	return 0;
}
