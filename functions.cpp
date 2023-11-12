#include "functions.h"
#include <cstdlib>
#include <random>
#include <iostream>
//function for generating either a negative or positive float value
float randomMultiplication(float input) {
    //generate a random number between 0 and 1. 
    int number1 = rand() % 2;

    //if the number generated is 0, multiply the float input by -1. 
    if (number1 == 0) {
        input = input * -1.f;
    }
    //else keep the float input the same
    else {
        input = input * 1.f;
    }
    //print statement for debugging purposes
    std::cout << "The number generated randomly is " << number1 << "\n";
    return input;
}

//function for reversing both the x and y offset of the ball 
void reverseDirection(float& offset) {
    offset = -offset;
}
