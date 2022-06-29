#include <iostream>
#include <thread>

class Functor{
public:
    void operator() (void){
        std::cout << "Hello, thread!\n";
    }
};

int main(int argc, char **argv){
    Functor functor_obj;

    std::thread t1(std::move(Functor()));
    std::thread t2([]()
    {
        std::cout << "Hello, thread!\n";
    });
    std::thread t3(functor_obj);

    t1.join();
    t2.join();
    t3.join();

    return EXIT_SUCCESS;
}