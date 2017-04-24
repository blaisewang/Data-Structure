#include <iostream>
#include <cmath>
#include "stackWithArrayList.h"
#include "singlyLinkedList.h"

using namespace std;

int main(void) {
    circularListWithHeader<int> a;
    for (int i = 1; i < 11; i++) {
        a.insert(0, i);
    }
    cout << a << endl;

    a.reverse();

    cout << a << endl;

    stackWithArrayList<int> b;
    int n, num;

    cout << "Number：";
    cin >> num;

    cout << " hexadecimal：";
    cin >> n;
    if (n > 0) {
        int mod;
        cout << n << "hexadecimal：";
        while (num) {
            mod = num % n;
            b.push(mod);
            num = num / n;
        }
        while (!b.empty()) {
            cout << b.top() << " ";
            b.pop();
        }
    }

    return 0;
}
