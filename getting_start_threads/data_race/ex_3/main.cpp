// There is data rase is free;

#include <iostream>
#include <thread>

int x {0};
int y {0};

void func_1(void){
    if (x){
        y = 1;      // never execute;
        std::cout << "Y set by " << y << std::endl;
    }
}

void func_2(void){
    if (y){
        x = 1;      // never execute;
        std::cout << "X set by " << x << std::endl;
    }
}

int main(int argc, char **argv){
    std::thread t1 (func_1);
    std::thread t2 (func_2);

    t1.join();
    t2.join();

    return 0;
}