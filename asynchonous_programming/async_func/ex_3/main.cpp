#include <iostream>
#include <future>
#include <thread>

using namespace std::literals;

int func(void);

int main(int argc, char **argv){
    std::cout << "In main thread with ID: "
              << std::this_thread::get_id()
              << std::endl;
    
    std::cout << "Calling func..." << std::endl;
    auto result = std::async(std::launch::async, func);
    //auto result = std::async(std::launch::deferred, func);
    //auto result = std::async(func);

    std::this_thread::sleep_for(2s);
    std::cout << "Calling get()" << std::endl;
    std::cout << result.get() << std::endl;

    return EXIT_SUCCESS;
}

int func(void){
    std::cout << "Executing func in thread with ID: "
              << std::this_thread::get_id() << std::endl;

    std::this_thread::sleep_for(5s);
    return 42;
}