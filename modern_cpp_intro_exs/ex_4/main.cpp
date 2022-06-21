#include <iostream>
#include <thread>
#include <string>

class Functor{
public:
    template<typename T>
    void operator() (T &&a){
        std::cout << a << std::endl;
    }
};

template<typename T>
void double_value(T &&a){
    std::cout << a << std::endl;
}

int main(int argc, char **argv){
    int a = 4;

    std::thread t1(double_value<int>, std::move(a));         
    std::thread t2(std::move(Functor()), std::move(a));
    std::thread t3([](auto &&a)                          
    {
        std::cout << a << std::endl;
    }, std::move(a));

    t1.join();
    t2.join();
    t3.join();

    std::string b = "abc";

    std::thread t4(double_value<std::string>, std::move(b));         
    std::thread t5(std::move(Functor()), std::move(b));
    std::thread t6([](auto &&a)                          
    {
        std::cout << a << std::endl;
    }, std::move(b));

    t4.join();
    t5.join();
    t6.join();

    return EXIT_SUCCESS;
}