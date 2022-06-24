#include <iostream>
#include <random>
#include <thread>

using namespace std::literals;

//std::mt19937 mt;              // result is different
thread_local std::mt19937 mt;   // result is the same for all threads;

void func(void){
    // Doubles in the range o to 1
    std::uniform_real_distribution<double> dist(0, 1);

    for (int i = 0; i < 10; ++i){
        std::cout << dist(mt) << ", ";
    }
    std::cout << std::endl;
}

int main(int argc, char **argv){
    std::cout << "Thread 1's random values: " << std::endl;
    std::thread t1 (func);
    t1.join();
    std::this_thread::sleep_for(100ms);

    std::cout << "Thread 2's random values: " << std::endl;
    std::thread t2 (func);
    t2.join();

    return EXIT_SUCCESS;
}