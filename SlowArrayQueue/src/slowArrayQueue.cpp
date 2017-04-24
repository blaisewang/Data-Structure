//============================================================================
// Name        : slowArrayQueue.cpp
// Author      : Blaise Wang
// Version     :
// Copyright   : 2016
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "slowArrayQueue.h"

using namespace std;

int main() {
    slowArrayQueue<int> a(4);
    a.push(1);
    a.push(2);
    a.push(3);
    a.push(4);
    a.push(5);

    while (!a.empty()) {
        cout << "Queue front is " << a.front() << endl;
        a.pop();
        cout << "Popped front element" << endl;
    }

    return 0;
}
