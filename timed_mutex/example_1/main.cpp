#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>

using namespace std::literals;

std::timed_mutex tm_mut;

void task_1(){
    std::cout << "Task 1 trying to get lock" << std::endl;

    tm_mut.lock();

    std::cout << "Task 1 has locked" << std::endl;

    std::this_thread::sleep_for(500ms);
    std::cout << "Task 1 releasing lock" << std::endl;

    tm_mut.unlock();
}

void task_2(){
    std::this_thread::sleep_for(100ms);
    std::cout << "Task 2 trying to get lock" << std::endl;

    while(!tm_mut.try_lock_for(100ms)){
        std::cout << "Task 2 could not get lock" << std::endl;
    }

    std::cout << "Task 2 has lock" << std::endl;

    tm_mut.unlock();
}

int main(int argc, char **argv){
    std::thread t1 (task_1);
    std::thread t2 (task_2);

    t1.join();
    t2.join();
}