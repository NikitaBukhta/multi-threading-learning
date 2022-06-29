#include <iostream>
#include <thread>
#include <string>
#include <chrono>

using namespace std::chrono_literals;

void print(const std::string &msg){
    std::cout << "Thread id: " << std::this_thread::get_id() 
              << ")\t" << msg;
}

int main(int argc, char **argv){
    std::thread t(print, "Hello thread!\n");
    
    std::cout << "Main thread: " << std::this_thread::get_id() 
              << std::endl;
    std::cout << "Daughter thread id before join: : " 
              << t.get_id() << std::endl;

    t.join();

    std::cout << "Daughter thread id after join: : " 
              << t.get_id() << std::endl;

    return EXIT_SUCCESS;
}