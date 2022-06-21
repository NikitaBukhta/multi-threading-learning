#include <iostream>
#include <thread>

class Functor{
public:
    void operator() (int a, int b){
        std::cout << a << " + " << b << " = " << a + b << std::endl;
    }
};

void print_sum(int a, int b){
    std::cout << a << " + " << b << " = " << a + b << std::endl;
}

int main(int argc, char **argv){
    Functor functor_obj;
    int a = 10;
    int b = 20;

    std::thread t1(print_sum, a, b);
    std::thread t2(std::move(Functor()), a, b);
    std::thread t3([](int a, int b)
    {
        std::cout << a << " + " << b << " = " << a + b << std::endl;
    }, a, b);

    t1.join();
    t2.join();
    t3.join();

    return EXIT_SUCCESS;
}