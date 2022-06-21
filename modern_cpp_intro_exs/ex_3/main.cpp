#include <iostream>
#include <thread>

class Functor{
public:
    void operator() (int &a){
        a *= 2;
    }
};

void double_value(int &a){
    a *= 2;
}

int main(int argc, char **argv){
    int a = 4;

    std::thread t1(double_value, std::ref(a));          // 8
    std::thread t2(std::move(Functor()), std::ref(a));  // 16
    std::thread t3([](int &a)                           // 32
    {
        a *= 2;
    }, std::ref(a));

    t1.join();
    t2.join();
    t3.join();

    std::cout << a << std::endl;

    return EXIT_SUCCESS;
}