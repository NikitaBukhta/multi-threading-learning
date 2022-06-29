#include <iostream>
#include <thread>
#include <string>
#include <chrono>

using namespace std::chrono_literals;

void print(const std::string &msg){
    std::cout << msg;
}

void print_thread_id(std::thread current_thread){
    std::cout << "Current thread id: " << current_thread.get_id() 
              << std::endl;

    current_thread.join();
}

int main(int argc, char **argv){
    std::thread temp_t(print, "Hello thread!\n");
    std::thread t(print_thread_id, 
                  std::move(temp_t));

    t.join();

    return EXIT_SUCCESS;
}