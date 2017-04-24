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
	currency g, h;

	// Try out both forms of assignment and outPut
	g = -99;
	h = 9.72;
	cout << "Currency g result is " << g << endl;
	cout << "Currency h result is " << h << endl;

	return 0;
}
