#include <iostream>
#include <mutex>
#include <thread>
#include <string>
#include <array>

using namespace std::literals;

std::mutex mut;

void task_1(void){
    std::cout << "Task1 trying to get lock" << std::endl;
    mut.lock();
    std::cout << "Task 1 has lock" << std::endl;
    std::this_thread::sleep_for(500ms);
    std::cout << "Task1 releasing lock" << std::endl;
    mut.unlock();
}

void task_2(void){
    std::this_thread::sleep_for(100ms);
    std::cout << "Task2 trying to get lock" << std::endl;

    while (!mut.try_lock()){
        std::cout << "Task2 could not get lock" << std::endl;
        std::this_thread::sleep_for(100ms);
    }
    std::cout << "Task2 has lock" << std::endl;
    mut.unlock();
}

int main(int argc, char **argv){
    std::thread t1 (task_1);
    std::thread t2 (task_2);

    t1.join();
    t2.join();

    return EXIT_SUCCESS;
}