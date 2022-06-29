#include <iostream>
#include <thread>
#include <string>
#include <chrono>

using namespace std::chrono_literals;

void print_with_sleep(const std::string &msg){
    std::this_thread::sleep_for(2s);

    std::cout << msg;
}

int main(int argc, char **argv){
    std::thread t(print_with_sleep, "Hello thread!\n");

    t.join();

    return EXIT_SUCCESS;
}