//============================================================================
// Name        : MaxHeap.cpp
// Author      : Blaise Wang
// Version     :
// Copyright   : 2016
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "maxHeap.h"

using namespace std;

int main()
{
	maxHeap<int> a;
//	a.push(3);
//	a.push(5);
//	a.push(6);
//	a.push(7);
//	a.push(20);
//	a.push(8);
//	a.push(2);
//	a.push(9);
//	a.push(12);
//	a.push(15);
//	a.push(30);
//	a.push(17);

	int b[13] =
	{ 0, 3, 5, 6, 7, 20, 8, 2, 9, 12, 15, 30, 17 };
	a.initialize(b, 12);

	cout << a << endl;

	a.push(15);
	a.push(20);
	a.push(45);
	a.pop();
	a.pop();
	a.pop();
	a.pop();

	cout << a << endl;

	return 0;
}
