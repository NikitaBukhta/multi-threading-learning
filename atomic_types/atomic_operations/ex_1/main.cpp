#include <iostream>
#include <string>
#include <thread>
#include <atomic>

using namespace std::literals;

std::atomic_flag lock_cout = ATOMIC_FLAG_INIT;

void print(const std::string &str){
    for (int i = 0; i < 20; ++i){
        while (lock_cout.test_and_set());

        std::cout << str[0] << str[1] << str[2] << std::endl;
        lock_cout.clear();
    }
}

int main(int argc, char **argv){
    std::thread t1(print, "abc");
    std::thread t2(print, "def");
    std::thread t3(print, "xyz");

    t1.join();
    t2.join();
    t3.join();

    return EXIT_SUCCESS;
}