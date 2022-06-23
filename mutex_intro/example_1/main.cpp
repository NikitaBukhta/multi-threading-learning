#include <iostream>
#include <mutex>
#include <thread>
#include <string>
#include <array>

using namespace std::literals;

std::mutex print_mutex;

void print(std::string str){
    for (int i = 0; i < 5; ++i){
        print_mutex.lock();                                     // Lock mutex before critical region;
        std::cout << str[0] << str[1] << str[2] << std::endl;   // critical region has exclusive access to str;
        print_mutex.unlock();                                   // unclock the mutex afterwards;
        std::this_thread::sleep_for(50ms);
    }
}

int main(int argc, char **argv){
    std::thread t1 (print, "abc");
    std::thread t2 (print, "def");
    std::thread t3 (print, "xyz");

    t1.join();
    t2.join();
    t3.join();

    return EXIT_SUCCESS;
}