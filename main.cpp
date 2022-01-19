#include	<iostream>
#include	<fstream>
#include	<random>
#include	<string>
#include	"ExRange.hpp"


using namespace std;

const unsigned int	kSyntaxNum = 100;

string	itos(int val)
{
	string	resultStr;

	int	tempVal = val;
	int	mul = 1;

	if (val == 0)
		return	"0";
	if (val < 0)
	{
		val *= -1;
		resultStr += '-';
	}
	while (tempVal != 0)
	{
		tempVal /= 10;
		mul *= 10;
	}
	mul /= 10;
	while (mul != 0)
	{
		resultStr += val / mul + '0';
		val -= val / mul * mul;
		mul /= 10;
	}

	return	resultStr;
};

string* parse(const string& str)
{
	size_t	i = 0;
	string* vals = new string[2];

	if (str[0] == '-')
	{
		vals[0] += '-';
		i++;
	}
	for (; i < str.size(); i++)
	{
		if (str[i] == '*' || str[i] == '/' || str[i] == '%' || str[i] == '+' || str[i] == '-')
			break;
		if (str[i] >= '0' && str[i] <= '9')
			vals[0] += str[i];
	}
	i++;
	if (str[++i] == '-')
		vals[1] += '-';
	for (; i < str.size(); i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
			vals[1] += str[i];
	}

	return	vals;
};

string	parse(const string& str, int* val2Ptr)
{
	size_t	i = 0;

	string	vals[2];

	if (str[0] == '-')
	{
		vals[0] += '-';
		i++;
	}
	for (; i < str.size(); i++)
	{
		if (str[i] == '*' || str[i] == '/' || str[i] == '%' || str[i] == '+' || str[i] == '-')
			break;
		if (str[i] >= '0' && str[i] <= '9')
			vals[0] += str[i];
	}
	i++;
	if (str[++i] == '-')
		vals[1] += '-';
	for (; i < str.size(); i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
			vals[1] += str[i];
	}
	*val2Ptr = atoi(vals[1].c_str());

	return	vals[0];
};

int main(int argc, char* argv[])
{
	/*ExRange<int>	val1("-239089348398016723861817124424181060870327751887526772462589533015402653459369");
	ExRange<int>	val2("-9322618723883548375472698183752266061003163");
	ExRange<int>	result;

	result = val1 + val2;

	cout << ExRange<int>::decode(result) << endl;*/

	/*random_device rd1, rd2;

	mt19937_64 gen1(rd1()), gen2(rd2());

	uniform_int_distribution<int> disRange(8, 100), disVal(0, 9);

	string	str;

	while (str.compare("exit"))
	{
		//string	*vals;

		// ExRange<int>	val1(vals[0]), val2(vals[1]);
		ExRange<int>	val1;
		int	val2;
		ExRange<int>	result;

		cout << ">>> ";
		getline(cin, str);
		val1 = parse(str, &val2);
		// vals = parse(str);

		result = val1 * val2;
		cout << ExRange<int>::decode(result) << endl;

		// delete[] vals;
	}*/
	ifstream	iFileOpen, iFile;
	ofstream	oFile;

	string	fileName;

	int	index = 1;

	if (argc == 1)
	{
		cout << "Input the file location : ";
		cin >> fileName;
		iFileOpen.open(fileName);
		fileName.clear();
	}
	else if (argc == 2)
		iFileOpen.open(argv[1]);
	if (iFileOpen.fail())
	{
		cout << "Error : Can't open file." << endl;
		return	0;
	}
	fileName = itos(index++);
	iFile.open(fileName + ".txt");

	while (!iFile.fail() && index != 2147483648)
	{
		iFile.close();
		fileName = itos(index++);

		iFile.open(fileName + ".txt");
	}
	oFile.open(fileName + ".txt");

	while (!iFileOpen.eof())
	{
		string	str;
		string* valStrs;
		string	resultStr;

		getline(iFileOpen, str);

		valStrs = parse(str);
		//ExRange<int>	val1(valStrs[0]), val2(valStrs[1]);
		ExRange<int>	val1(valStrs[0]);
		ExRange<int>	val2(valStrs[1]);
		//int	val2 = atoi(valStrs[1].c_str());
		ExRange<int>	result;

		result = val1 + val2;
		resultStr = ExRange<int>::decode(result) + '\n';
		oFile.write(resultStr.c_str(), resultStr.size());
		cout << resultStr;

		delete[]	valStrs;
	}

	iFile.close();
	iFileOpen.close();
	oFile.close();

	/*ExRange<int>	val(1);

	for(int i = 1; i <= 300; i++)
		val = val * i;
	for(int i = 0; i < val.getSize(); i++)
		cout << val[i] << ", ";
	cout << endl;*/

	return	0;

}