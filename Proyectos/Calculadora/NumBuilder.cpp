#include "NumBuilder.hpp"

NumBuilder::NumBuilder(){
    this->reset();
}

int NumBuilder::addDigit(char d){
    if (this->index >= MAX_DIGITS){
        return -1;
    }
    if (d == '-'){
        if(this->index > 0 || this->negative){
            return -1;
        }
        this->negative = true;
    }
    else if(! isdigit(d)){
        return -1;
    }
    else{
        if(this->index == 0){
            this->negative = false;
        }
        this->digits[this->index] = d;
        (this->index)++;
    }
    return 0;
}

long NumBuilder::getNumber(){
    unsigned int i;
    long int num = 0;
    for (i = 0; i < this->index; i++){
        num += (this->digits[i] - ASCII_ZERO) * powOf10(this-> index - i - 1);
    }
    return this->negative ? -num : num; 
}

bool NumBuilder::isEmpty(){
    return (this->digits[0] == 0);
}

void NumBuilder::reset(){
    this->number = 0;
    this->index = 0;
    this->negative = false;
    unsigned int i;
    for (i = 0; i < MAX_DIGITS; i++){
        this->digits[i] = 0;
    }
}

long powOf10(unsigned int n){
    long p = 1;
    while(n > 0){
        p *= 10;
        n--;
    }
    return p;
}
