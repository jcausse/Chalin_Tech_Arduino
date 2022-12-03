#ifndef NUM_BUILDER_H
#define NUM_BUILDER_H

#define ASCII_ZERO 0x30                                                       //Valor del cero ASCII para conversion de char a int
#define MAX_DIGITS 14                                                         //Maximo numero de digitos permitidos por numero

class NumBuilder{
public:
    NumBuilder();

    int addDigit(char d);
    long getNumber();
    bool isEmpty();

    void reset();

private:
    char digits[MAX_DIGITS];
    long number;
    unsigned int index;
    bool negative;
}

#endif //NUM_BUILDER_H