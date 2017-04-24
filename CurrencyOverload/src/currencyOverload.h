// currency class with operator overloading

#ifndef currency_
#define currency_

#include <iostream>
#include <CStdlib>

using namespace std;

typedef enum {
    SignPlus, SignMinus
} SignType;

class currency {
public:
    // Constructor
    currency(SignType theSign = SignPlus, unsigned long theDollars = 0,
            unsigned int theCents = 0);

    // Destructor
    ~currency() {
    }

    void setValue(SignType, unsigned long, unsigned int);

    void setValue(double);

    SignType getSign() const {
        if (amount < 0) {
            return SignMinus;
        } else {
            return SignPlus;
        }
    }

    long getDollars() const {
        if (amount < 0) {
            return (-amount) / 100;
        } else {
            return amount / 100;
        }
    }

    long getCents() const {
        if (amount < 0) {
            return -amount - getDollars() * 100;
        } else {
            return amount - getDollars() * 100;
        }
    }

    currency operator+(const currency &) const;

    currency &operator+=(const currency &x) {
        amount += x.amount;
        return *this;
    }

    currency operator=(int);

    currency operator=(double);

    void output(ostream &) const;

private:
    long amount;
};

currency::currency(SignType theSign, unsigned long theDollars, unsigned int theCents) {
    // Create a currency object.
    setValue(theSign, theDollars, theCents);
}

void currency::setValue(SignType theSign, unsigned long theDollars, unsigned int theCents) {
    // Set currency value.

    if (theCents > 99) {                     // Too many cents
        //throw illegalParameterValue("Cents should be < 100");
        cerr << "Cents should be < 100" << endl;
        exit(EXIT_FAILURE);
    }

    amount = theDollars * 100 + theCents;
    if (theSign == SignMinus) {
        amount = -amount;
    }
}

void currency::setValue(double theAmount) {
    // Set currency value.

    if (theAmount < 0) {
        amount = (long) ((theAmount - 0.001) * 100);
    } else {
        amount = (long) ((theAmount + 0.001) * 100);
    }
    // 2 decimal digits only
}

currency currency::operator+(const currency &x) const {
    // Add x and *this.

    currency result;
    result.amount = amount + x.amount;
    return result;
}

currency currency::operator=(int x) {
    // Set currency integer value with operator=

    amount = x;
    return *this;
}

currency currency::operator=(double x) {
    // Set currency double value with operator=

    amount = (long) (x * 100);
    return *this;
}

void currency::output(ostream &out) const {
    // Insert currency value into stream out.

    long theAmount = amount;
    if (theAmount < 0) {
        out << '-';
        theAmount = -theAmount;
    }
    long dollars = theAmount / 100; // dollars
    out << '$' << dollars << '.';
    int cents = (int) (theAmount - dollars * 100); // cents
    if (cents < 10) {
        out << '0';
    }
    out << cents;
}

// Overload <<
ostream &operator<<(ostream &out, const currency &x) {
    x.output(out);
    return out;
}

#endif
