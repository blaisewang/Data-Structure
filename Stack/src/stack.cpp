#include <iostream>
#include <Cmath>
#include "stackWithArrayList.h"
#include "singlyLinkedList.h"

using namespace std;

int main(void)
{
	circularListWithHeader<int> a;
	for (int i = 1; i < 11; i++)
	{
		a.insert(0, i);
	}
	cout << a << endl;

	a.reverse();

	cout << a << endl;

//	stackWithArrayList<int> a;
//	int n, num;
//
//	cout << "输入转换的数：";
//	cin >> num;
//
//	cout << "转换的进制数：";
//	cin >> n;
//	if (n > 0)
//	{
//		int mod;
//		cout << n << "进制：";
//		while (num)
//		{
//			mod = num % n;
//			a.push(mod);
//			num = num / n;
//		}
//		while (!a.empty())
//		{
//			cout << a.top() << " ";
//			a.pop();
//		}
//	}
//	else
//	{
//		cerr << "转换的进制数不合法" << endl;
//	}

	return 0;
}
