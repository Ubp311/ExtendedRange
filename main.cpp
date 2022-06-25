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
	/*while(true)
	{
		string	val1Str;
		int	val2;
		char	op;

		cout << "Input the first value string : ";
		cin >> val1Str;
		if(!val1Str.compare("exit"))
			break;
		cout << "Input the second value : ";
		cin >> val2;
		if(!val1Str.compare("exit"))
			break;
		cout << "Input the operator : ";
		cin >> op;
		if(!val1Str.compare("exit"))
			break;
		switch (op)
		{
		case '+':
			cout << ExRange<int>::decode(ExRange<int>(val1Str) + val2) << endl;
			break;
		case '-':

			cout << ExRange<int>::decode(ExRange<int>(val1Str) - val2) << endl;
			break;
		case '*':
			cout << ExRange<int>::decode(ExRange<int>(val1Str) * val2) << endl;
			break;
		case '/':
			cout << ExRange<int>::decode(ExRange<int>(val1Str) / val2) << endl;
			break;
		case '%':
			cout << "Implementing.." << endl;
			break;6
		default:
			cout << "Error : Unknown operator" << endl;
			break;
		}
	}*/

	ExRange<int>	val1("42384239482948234928429348");
	int	val2 = 23423492;
	// ExRange<int>	val2("43289483242394823942");
	ExRange<int>	result;

	result = val1 + val2;

	cout << ExRange<int>::decode(val1) << endl;

	//cout << ExRange<int>::decode(result) << endl;

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
	/*ifstream	iFileOpen, iFile;
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

	//unsigned int	iter = 1U;
	while (!iFileOpen.eof())
	{
		string	str;
		string* valStrs;
		string	resultStr;

		getline(iFileOpen, str);

		valStrs = parse(str);
		ExRange<int>	val1(valStrs[0]), val2(valStrs[1]);
		ExRange<int>	result;

		result = val1 + val2;
		resultStr = ExRange<int>::decode(result) + '\n';
		//oFile.write(resultStr.c_str(), resultStr.size());
		// cout << resultStr;

		delete[]	valStrs;
		
		//cout << iter++ << endl;
	}
	//cout << "Complete!" << endl;

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