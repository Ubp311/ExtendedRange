#include	<iostream>
#include	"ExRange.hpp"


using namespace std;

int main()
{
	ExRange<int>	val1("-4257845295728459275849257489527");
	ExRange<int>	val2("5424398295829045820958290458295");
	ExRange<int>	result;

	result = val1 + val2;
	cout << result.decode(result) << endl;

	return	0;
}