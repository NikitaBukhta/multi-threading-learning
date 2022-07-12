#include <iostream>
#include <future>

void hello(void);

int main(int argc, char **argv){
    std::async(hello);

    return EXIT_SUCCESS;
}

void hello(void){
    std::cout << "Hello, Async!\n";
}