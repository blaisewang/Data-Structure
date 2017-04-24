//============================================================================
// Name        : CurrencyOverload.cpp
// Author      : Blaise Wang
// Version     :
// Copyright   : 2016
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "currencyOverload.h"

using namespace std;

int main(int argc, const char * argv[])
{
	currency a, b;

	// Try out both forms of assignment and outPut
	a = -99;
	b = 9.72;
	cout << "Currency a result is " << a << endl;
	cout << "Currency b result is " << b << endl;

	return 0;
}
