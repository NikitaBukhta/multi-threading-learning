#include "thread_quard.h"

#include <iostream>
#include <chrono>

using namespace std::chrono_literals;

void say_hello(void){
    std::this_thread::sleep_for(1s);
    std::cout << "Hello thread!\n";
}

void try_catch(void){
    std::thread t {say_hello};
    try{
        throw std::exception();
        t.join();
    }
    catch(std::exception &e){
        std::cerr << e.what() << std::endl;
        t.join();
    }
}

void raii_class(void){
    ThreadQuard(std::thread(say_hello));
    throw std::exception();
}

// C++20;
// do not support in clang++ compiler;
/*
void using_jthread(void){
    std::jthread(say_hello);
    throw std::exception();
}*/

int main(int argc, char **argv){
    try_catch();
    //raii_class();

    return 0;
}