#include	<iostream>
#include	<random>
#include	<string>
#include	"ExRange.hpp"


using namespace std;

const unsigned int	kSyntaxNum = 100;

int main()
{
	/*ExRange<int>	val1("91352366968985015887710493978205273543227469308829234536203379295");
	ExRange<int>	val2("54985079145921092175062507376281");
	ExRange<int>	result;

	result = val1 + val2;

	cout << ExRange<int>::decode(result) << endl;*/

	/*string	strVals[100];
	ExRange<int>	vals[kSyntaxNum * 2];
	ExRange<int>	results[kSyntaxNum];*/

	random_device rd1, rd2;

	mt19937_64 gen1(rd1()), gen2(rd2());

	uniform_int_distribution<int> disRange(8, 100), disVal(0, 9);

	for (int i = 0; i < kSyntaxNum; i++)
	{
		string	valStr[2];
		int jMax = disRange(gen1);
		for (int j = 0; j < jMax; j++)
			valStr[0] += disVal(gen2) + '0';
		jMax = disRange(gen1);
		for (int j = 0; j < jMax; j++)
			valStr[1] += disVal(gen2) + '0';
		ExRange<int>	val1(valStr[0]), val2(valStr[1]);
		ExRange<int>	result;

		cout << valStr[0] << " + " << valStr[1] << " = ";
		result = val1 + val2;
		cout << ExRange<int>::decode(result) << endl;
	}

	return	0;
}