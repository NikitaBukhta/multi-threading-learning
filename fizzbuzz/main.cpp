#include "fizz_buzz.h"

#include <iostream>
#include <thread>

int main(int argc, char **argv){
    game::FizzBuzz fizz_buzz(100);

    std::thread game_thread(&game::FizzBuzz::start, &fizz_buzz);
    game_thread.join();

    return EXIT_SUCCESS;
}