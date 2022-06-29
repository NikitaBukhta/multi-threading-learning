#include "fizz_buzz.h"

using namespace game;

int FizzBuzz::start(void){
    bool divisible_by_3 = false;
    bool divisible_by_5 = false;

    while(++_current_number <= _end){
        divisible_by_3 = _current_number % 3 == 0;
        divisible_by_5 = _current_number % 5 == 0;

        if (divisible_by_3 && divisible_by_5){
            std::cout << "Fizz Buzz, ";
        }
        else if (divisible_by_3){
            std::cout << "Fizz, ";
        }
        else if (divisible_by_5){
            std::cout << "Buzz, ";
        }
        else{
            std::cout << _current_number << ", ";
        }
    }

    return EXIT_SUCCESS;
}

void FizzBuzz::set_end(unsigned int new_end){
    this->_end = new_end;
}