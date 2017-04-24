//============================================================================
// Name        : singlyLinkedList.cpp
// Author      : Blaise Wang
// Version     :
// Copyright   : 2016
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "singlyLinkedList.h"

#include <iostream>
#include <numeric>

using namespace std;

int main() {
    circularListWithHeader<int> a, b;
    for (int i = 1; i < 11; i++) {
        b.insert(0, i);
    }
    cout << b << endl;

    cout << b.get(0) << endl;

    cout << b.indexOf(1) << endl;

    b.erase(0);
    cout << b << endl;

    b.reverse();
    cout << b << endl;

    int sum = accumulate(b.begin(), b.end(), 0);
    cout << sum << endl;

    a.insert(0, 1);
    a = b;
    cout << a << endl;

    return 0;
}
