//============================================================================
// Name        : Queue.cpp
// Author      : Blaise Wang
// Version     :
// Copyright   : 2016
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "arrayQueue.h"

using namespace std;

int main()
{
	arrayQueue<int> a(4), b(5), c(10);

	a.push(1);
	a.push(3);
	a.push(1);
	a.push(3);
	a.push(1);
	a.push(3);
	a.push(1);
	a.push(3);
	a.push(1);
	a.push(3);
	a.push(1);
	a.push(3);
	a.push(1);
	a.push(3);
	a.push(1);
	a.push(3);

	b.push(2);
	b.push(4);


	//c.merge(a, b);

	while (!a.empty())
	{
		cout << "Queue front is " << a.front() << endl;
		a.pop();
		cout << "Popped front element" << endl;
	}

	return 0;
}
