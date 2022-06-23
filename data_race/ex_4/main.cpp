// There is data rase is not free;

#include <iostream>
#include <thread>

int x {0};
int y {0};

void func_1(void){
    x = 1;
    int r1 = y;
    
    std::cout << "r1 = " << r1 << std::endl;
}

void func_2(void){
    y = 1;
    int r2 = x;

    std::cout << "r2 = " << r2 << std::endl;
}

int main(int argc, char **argv){
    std::thread t1 (func_1);
    std::thread t2 (func_2);

    t1.join();
    t2.join();

    return 0;
}