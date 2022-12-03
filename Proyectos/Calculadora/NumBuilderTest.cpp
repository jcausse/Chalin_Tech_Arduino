#include "NumBuilder.hpp"
#include <iostream>
#include <assert.h>

using namespace std;

int main (){
    NumBuilder b  = NumBuilder();

    assert(b.addDigit('-') == 0);
    assert(b.isEmpty());
    assert(b.addDigit('-') == -1);

    b.reset();

    assert(b.addDigit('0') == 0);
    assert(b.addDigit('&') == -1);

    b.reset();

    assert(b.addDigit('-') == 0);
    assert(b.isEmpty());
    assert(b.addDigit('0') == 0);
    assert(! b.isEmpty());
    assert(b.addDigit('3') == 0);
    assert(b.addDigit('5') == 0);
    assert(b.addDigit('2') == 0);
    assert(b.addDigit('1') == 0);
    assert(b.addDigit('-') == -1);

    b.reset();

    assert(b.addDigit('-') == 0);
    assert(b.addDigit('0') == 0);
    assert(b.addDigit('3') == 0);
    assert(b.addDigit('5') == 0);
    assert(b.addDigit('2') == 0);
    assert(b.addDigit('1') == 0);
    assert(b.getNumber() == -3521);

    b.reset();

    assert(b.addDigit('1') == 0);
    assert(b.addDigit('3') == 0);
    assert(b.addDigit('9') == 0);
    assert(b.addDigit('6') == 0);
    assert(b.addDigit('8') == 0);
    assert(b.getNumber() == 13968);

    cout << "All tests passed!" << endl;
    return 0;
}
