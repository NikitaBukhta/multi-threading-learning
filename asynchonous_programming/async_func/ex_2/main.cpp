#include <iostream>
#include <future>

using namespace std::literals;

unsigned long long fibonacci(unsigned long long n);

int main(int argc, char **argv){
    std::cout << "Calling fibonacci 40" << std::endl;

    auto result = std::async(fibonacci, 40);
    //auto result = std::async(std::launch::deferred, fibonacci, 40);
    //auto result = std::async(std::launch::async, fibonacci, 40);
    //auto result = std::async(std::launch::any, fibonacci, 40);

    std::cout << "Calculating result..." << std::endl;
    std::this_thread::sleep_for(2s);
    std::cout << result.get() << std::endl;

    return EXIT_SUCCESS;
}

unsigned long long fibonacci(unsigned long long n){
    thread_local bool first_start = true;

    if (first_start){
        std::cout << "Started!" << std::endl;
        first_start = false;
    }

    if (n <= 1){
        return 1;
    }

    return fibonacci(n - 1) + fibonacci(n - 2);
}