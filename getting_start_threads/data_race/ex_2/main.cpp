// There is data rase is free;

#include <iostream>
#include <thread>

const int X (5);

int double_X(void){
    return 2 * X;
}

int triple_X(void){
    return 3 * X;
}

int main(int argc, char **argv){
    std::thread t1 (double_X);
    std::thread t2 (triple_X);

    t1.join();
    t2.join();

    return 0;
}