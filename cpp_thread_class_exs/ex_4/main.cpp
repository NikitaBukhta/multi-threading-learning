#include <iostream>
#include <thread>
#include <string>
#include <chrono>

using namespace std::chrono_literals;

void print(const std::string &msg){
    std::cout << msg;
}

std::thread get_new_thread(void){
    return std::thread(print, "msg from new thread\n");
}

int main(int argc, char **argv){
    std::thread t (get_new_thread());
    std::cout << "Thread id: " << t.get_id() << std::endl;

    t.join();

    return EXIT_SUCCESS;
}