#include <iostream>
#include <thread>
#include <future>

using namespace std::literals;

int produce(void);

int main(int argc, char **argv){
    auto f = std::async(std::launch::async, produce);

    std::cout << "Future calling get()..." << std::endl;
    try{
        int x(f.get());     // get th result;
        std::cout << "Future returns from callling get()"
                  << std::endl;
                
        std::cout << "The answer is " << x << std::endl;
    }
    catch(const std::exception &e){
        std::cerr << e.what() << std::endl;
    }

    return EXIT_SUCCESS;
}

int produce(void){
    int x(42);
    std::this_thread::sleep_for(3s);

    throw std::out_of_range("Opps");
    std::cout << "Produce returning " << x
              << std::endl;

    return x;
}